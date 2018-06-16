#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "Calculator.h"

using namespace std;

int main()
{

	string exp;

	cout << "input expression>>";

	cin >> exp;

	PolishCalculator cal(exp);

	cal.ParsingExpression();

	cal.ToPostfix();

	cal.Calculate();

	/* ȭ���� �ٷ� ������ ���� �����ϱ� ���� ����. ���ֵ� ����*/
	getchar();

	getchar();

}

/*element�� ������.*/
element::element(int dataType, int value)
{

	this->dataType = dataType;

	this->value = value;

}

/*�⺻ ������. ������ ����� ����*/
element::element()
{

}

/*�⺻ �Ҹ���. ������ ����� ����*/
element::~element()
{

}


/* ������, �ǿ�����, ��ȣ ���� Ÿ�� ����*/
int element::GetType()
{
	return dataType;
}

/* �ǿ������� ��� ��, �������� ��� ���� ����, ��ȣ�� ��� �������� ���������� ����*/
int element::GetValue()
{
	return value;
}

/*������ ��ȯ�� ���� �켱���� ����*/
int element::GetPriority()
{
	switch (value) {

		/* �켱 ������ ���ڰ� �������� ����*/

	case LEFT_PAREN:

		return 0;
		break;

	case ADD:

		return 1;
		break;

	case SUB:

		return 2;
		break;

	case MUL:

		return 3;
		break;

	case DIV:

		return 4;
		break;

	}
	
	//�ƹ� �����ڵ� �ƴ� ��� ����
	return -1;
}


PolishCalculator::PolishCalculator(string expression)
{
	this->expression = expression;
}

/*�⺻ ������. ������ ����� ����*/
PolishCalculator::PolishCalculator() {

}

/*�⺻ �Ҹ���. ������ ����� ����*/
PolishCalculator::~PolishCalculator() {

}

void PolishCalculator::ParsingExpression()
{
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

/*���ڸ� �Ľ��ϴ� �Լ�. 
  �Ľ��� �� ������ �� ������ �ε����� ������*/
int PolishCalculator::ParsingNum(int i)
{
	Stack<int> number;

	/*������ �ƽ�Ű�ڵ� - '0'�� �ϸ� ���ڷ� ǥ���� ���ڸ� ������ �ٲپ��ִ� ȿ���� ����*/
	while (isdigit(expression[i])) {
		number.push(expression[i++] - '0');
	}

	int num = StackToInt(number);

	parser.push(element(NUMBER, num));

	return i;
}

/* ������ �Լ�. ���ڿ��� �Ľ��� ť�� ���*/
void PolishCalculator::printQueue()
{
	queue<element> temp = parser;

	while (!temp.empty()) {

		cout << temp.front().GetValue() << endl;
		temp.pop();

	}
}

/*�������� �Ľ��� ��, ���������� �ٲپ��ִ� �Լ�*/
void PolishCalculator::ToPostfix()
{

	while (!parser.empty()) {

		element e = parser.front();

		switch (e.GetType()) {

	    /*�ǿ����ڴ� �ٷ� �����*/
		case NUMBER:

			postfix.push(e);
			break;

		/*���� ��ȣ�� �ٷ� �����*/
		case PARENTHESES:

			if (e.GetValue() == LEFT_PAREN) {
				stack.push(e);
			}

			//������ ��ȣ�� ��
			else {

				element temp = stack.tos();

				/*���� ��ȣ�� ���ö����� ��� pop�Ѵ�*/

				while (temp.GetValue() != LEFT_PAREN) {

					temp = stack.pop();

					postfix.push(temp);

				}

			}

			break;

		case OPERATOR:

			element temp = stack.tos();

			/* �켱 ���� ���� �����ڰ� ���ö����� ��� pop�Ѵ�*/
			while (temp.GetPriority() > e.GetPriority()) {

				temp = stack.pop();

				postfix.push(temp);

			}

			/*pop�� ������ �ش� �����ڸ� ���ÿ� ����*/
			stack.push(e);

			break;
		}

		parser.pop();

	}

	/* ������ �����ִ� �����ڸ� Ǫ����*/
	while (!stack.empty()) {

		postfix.push(stack.pop());

	}
}

/*1�� �ڸ����� ������� Ǫ���� ������ int������ �ٲپ��ִ� �޼ҵ�*/
int PolishCalculator::StackToInt(Stack<int> &number)
{
	int digit = 1;

	int ret = 0;

	/*1�� �ڸ� * 1, 10�� �ڸ� * 10, 100�ڸ� * 100 ....�� �ݺ��ϸ鼭 ����*/
	while (!number.empty()) {

		ret += number.pop() * digit;

		digit *= 10;

	}

	return ret;

}

void PolishCalculator::Calculate()
{
	Stack <double> stack;

	/* ������ ť�� ���������� ���� �ݺ�*/
	while (!postfix.empty()) {

		element e = postfix.front();

		int type = e.GetType();

		int value = e.GetValue();

		double result = 0.0;

		/*�ǿ����ڰ� ������ �ٷ� Ǫ��*/
		if (type == NUMBER) {

			stack.push(value);

		}

		/*�����ڰ� ������ �� ���ڸ� ���ʷ� pop�ؼ� ������ �� ����� ���ÿ� ����*/
		else if (type == OPERATOR) {

			double num1 = stack.pop();

			double num2 = stack.pop();

			switch (value) {

			case ADD:

				stack.push(num1 + num2);
				break;

			case SUB:

				stack.push(num2 - num1);
				break;

			case MUL:

				stack.push(num1 * num2);
				break;

			case DIV:

				stack.push(num2 / num1);
				break;

			}
		}

		postfix.pop();

	}

	cout << stack.tos();

}

/*������ ��� �Լ�. ���������� �ٲ� ����� �����*/
void PolishCalculator::PrintPostfix()
{
	queue <element> temp = postfix;

	cout << "postfix:";

	while (!temp.empty()) {

		element e = temp.front();

		int type = e.GetType();

		int value = e.GetValue();

		/* �����ڰ� ���� ��� ���� ������� �������־�� ��
		ť�� ��� �ִ� ���� enum�� �̿��� �������̱� ����*/

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

		/*�ǿ������� ��� �׳� ���ڸ� �����.
		  �����Ŀ��� ��ȣ�� �������� �ʱ� ������ �����ڿ� �ǿ����ڸ� ����ϸ� ��.*/

		else {
			cout << value;
		}

		temp.pop();

		cout << " ";

	}

	cout << endl;

}
