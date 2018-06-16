#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Operation {
	ADD, 
	SUB, 
	MUL, 
	DIV
};

enum DataType{
	OPERATOR,
	NUMBER,
	LEFT_PAREN,
	RIGHT_PAREN,
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
	Stack(){
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

};


class PolishCalculator{
private:
	queue<element> parser;
	string expression;

public:
	
	PolishCalculator(string expression) {
		this->expression = expression;
	}

	void ParsingExpression() {
		int i = 0;
		while((unsigned)i < expression.length()){
			if (isdigit(expression[i])){
				i = ParsingNum(i);
			}
			else if (expression[i++] == '+') {
				parser.push(element(OPERATOR, ADD));
			}
			else if (expression[i++] == '-') {
				parser.push(element(OPERATOR, SUB));
				cout << i << endl;
			}
			else if (expression[i++] == '*') {
				parser.push(element(OPERATOR, SUB));
				cout << i << endl;
			}
			else if (expression[i++] == '/') {
				parser.push(element(OPERATOR, DIV));
				cout << i << endl;
			}
			else if (expression[i++] == ' ') {
				cout << i << endl;
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

	void Calculate() {
		Stack <double> stack;
		while (!parser.empty()) {
			element e = parser.front();
			parser.pop();

			if (e.GetType() == NUMBER) {
				stack.push(e.GetValue());
			}
			else if(e.GetType() == OPERATOR){
				double num1 = stack.pop();
				double num2 = stack.pop();
				cout << num1 << num2 << endl;
				switch (e.GetValue()) {
				case ADD:
					stack.push(num1 + num2);
					break;
				case SUB:
					stack.push(num1 - num2);
					break;
				case MUL:
					stack.push(num1 * num2);
					break;
				case DIV:
					stack.push(num1 / num2);
					break;
					
				}
			}
		}
		double result = stack.pop();
		cout << result << endl;
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


};

int main() {

	string exp = "100 23+";
	PolishCalculator cal(exp);
	cal.ParsingExpression();

	cal.printQueue();
	getchar();


}