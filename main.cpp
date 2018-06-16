#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "Calculator.h"

using namespace std;

int main() {

	string exp;
	cout << "input expression>>";

	cin >> exp;

	PolishCalculator cal(exp);
	cal.ParsingExpression();

	cal.ToPostfix();

	cal.Calculate();

	getchar();
	getchar();

}

element::element(int dataType, int value) {
	this->dataType = dataType;
	this->value = value;
}

element::element() {

}
int element::GetType() {
	return dataType;
}

int element::GetValue() {
	return value;
}
int element::GetPriority() {
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


PolishCalculator::PolishCalculator(string expression) {
	this->expression = expression;
}

void PolishCalculator::ParsingExpression() {
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

int PolishCalculator::ParsingNum(int i) {
	Stack<int> number;

	while (isdigit(expression[i])) {
		number.push(expression[i++] - '0');
	}

	int num = StackToInt(number);
	parser.push(element(NUMBER, num));

	return i;
}

void PolishCalculator::printQueue() {
	queue<element> temp = parser;
	while (!temp.empty()) {
		cout << temp.front().GetValue() << endl;
		temp.pop();
	}
}

void PolishCalculator::ToPostfix() {

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

int PolishCalculator::StackToInt(Stack<int> &number) {
	int digit = 1;
	int ret = 0;

	while (!number.empty()) {
		ret += number.pop() * digit;
		digit *= 10;
	}
	return ret;
}

void PolishCalculator::Calculate() {
	Stack <double> stack;

	while (!postfix.empty()) {
		element e = postfix.front();

		int type = e.GetType();
		int value = e.GetValue();

		double result = 0.0;
		if (type == NUMBER) {
			stack.push(value);
		}

		else if (type == OPERATOR) {
			double num1 = stack.pop();
			double num2 = stack.pop();

			switch (value) {
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
				stack.push(num1 * num2);
				break;
			}
		}
		postfix.pop();
	}
	cout << stack.tos();
}

void PolishCalculator::PrintPostfix() {
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





