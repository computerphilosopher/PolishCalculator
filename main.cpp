#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Operation {
	ADD,
	SUB,
	MUL,
	DIV,
	LEFT_PAREN,
	RIGHT_PAREN,
};

enum DataType {
	OPERATOR,
	PARENTHESES,
	NUMBER,
};


enum Count {
	STATE_COUNT = 5,
	SYMBOL_COUNT = 3
};

template <class T>
class Stack {
private:
	int top;
	T stack[1000];
public:
	Stack() {
		top = -1;
	}
	void push(T e) {
		stack[++top] = e;
	}
	T pop() {
		return stack[top--];
	}
	T tos() {
		return stack[top];
	}
	bool empty() {
		return top == -1;
	}
	int size() {
		return top + 1;
	}
};

class element {
private:
	int dataType;
	int value;

public:
	element(int dataType, int value) {
		this->dataType = dataType;
		this->value = value;
	}
	element() {

	}
	int GetType() {
		return dataType;
	}

	int GetValue() {
		return value;
	}
	int GetPriority() {
		switch (value) {
		case LEFT_PAREN:
			return 0;
			break;
		case ADD:
			return 1;
			break;
		case SUB:
			return 1;
			break;
		case MUL:
			return 2;
			break;
		case DIV:
			return 2;
			break;
		}
		return -1;
	}

};


class PolishCalculator {
private:
	queue<element> parser;
	string expression;
	queue<element> postfix;
	Stack<element> stack;

public:

	PolishCalculator(string expression) {
		this->expression = expression;
	}

	void ParsingExpression() {
		int i = 0;
		while ((unsigned)i < expression.size()) {
			if (isdigit(expression[i])) {
				i = ParsingNum(i);
			}
			else {
				switch (expression[i++]) {
				case '+':
					parser.push(element(OPERATOR, ADD));
					break;
				case '-':
					parser.push(element(OPERATOR, SUB));
					break;
				case '*':
					parser.push(element(OPERATOR, MUL));
					break;
				case '/':
					parser.push(element(OPERATOR, DIV));
					break;
				case '(':
					parser.push(element(PARENTHESES, LEFT_PAREN));
					break;
				case ')':
					parser.push(element(PARENTHESES, RIGHT_PAREN));
					break;
				}

			}
		}

	}

	int ParsingNum(int i) {
		Stack<int> number;

		while (isdigit(expression[i])) {
			number.push(expression[i++] - '0');
		}

		int num = StackToInt(number);
		parser.push(element(NUMBER, num));

		return i;
	}

	void printQueue() {
		queue<element> temp = parser;
		while (!temp.empty()) {
			cout << temp.front().GetValue() << endl;
			temp.pop();
		}
	}

	void ToPostfix() {
		while (!parser.empty()) {
			element e = parser.front();

			switch (e.GetType()) {
			case NUMBER:
				postfix.push(e);
				break;
			case PARENTHESES:
				if (e.GetValue() == LEFT_PAREN) {
					stack.push(e);
				}

				//오른쪽 괄호일 때
				else {
					element temp = stack.tos();
					while (temp.GetValue() != LEFT_PAREN) {
						temp = stack.pop();
						postfix.push(temp);
					}
				}
				break;
			case OPERATOR:
				element temp = stack.tos();
				while (temp.GetPriority() > e.GetPriority()) {
					temp = stack.pop();
					postfix.push(temp);
				}
				stack.push(e);
				break;
			}
			parser.pop();
		}

		while (!stack.empty()) {
			postfix.push(stack.pop());
		}
	}

	int StackToInt(Stack<int> &number) {
		int digit = 1;
		int ret = 0;

		while (!number.empty()) {
			ret += number.pop() * digit;
			digit *= 10;
		}
		return ret;
	}

	void PrintPostfix() {
		queue <element> temp = postfix;

			cout << "postfix:";
		while (!temp.empty()) {
			element e = temp.front();
			
			int type = e.GetType();
			int value = e.GetValue();

			if (type == OPERATOR) {
				switch (value) {
				case ADD:
					cout << "+";
					break;
				case SUB:
					cout << "-";
					break;
				case MUL:
					cout << "*";
					break;
				case DIV:
					cout << "/";
					break;
				}
			}

			else {
				cout << value;
			}
			temp.pop();
				cout << " ";

		}
			cout << endl;
	}


};




int main() {

	string exp = "100+23*(25-23)";
	PolishCalculator cal(exp);
	cal.ParsingExpression();

	//cal.printQueue();
	cal.ToPostfix();


	cal.PrintPostfix();

	getchar();


}