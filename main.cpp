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

	/* 화면이 바로 꺼지는 것을 방지하기 위해 넣음. 없애도 무방*/
	getchar();

	getchar();

}

/*element의 생성자.*/
element::element(int dataType, int value)
{

	this->dataType = dataType;

	this->value = value;

}

/*기본 생성자. 만약을 대비해 넣음*/
element::element()
{

}

/*기본 소멸자. 만약을 대비해 넣음*/
element::~element()
{

}


/* 연산자, 피연산자, 괄호 등의 타입 리턴*/
int element::GetType()
{
	return dataType;
}

/* 피연산자일 경우 값, 연산자일 경우 종류 리턴, 괄호일 경우 왼쪽인지 오른쪽인지 리턴*/
int element::GetValue()
{
	return value;
}

/*후위식 변환을 위해 우선순위 리턴*/
int element::GetPriority()
{
	switch (value) {

		/* 우선 순위는 숫자가 높을수록 높음*/

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
	
	//아무 연산자도 아닐 경우 리턴
	return -1;
}


PolishCalculator::PolishCalculator(string expression)
{
	this->expression = expression;
}

/*기본 생성자. 만약을 대비해 넣음*/
PolishCalculator::PolishCalculator() {

}

/*기본 소멸자. 만약을 대비해 넣음*/
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

/*숫자를 파싱하는 함수. 
  파싱한 뒤 다음에 볼 문자의 인덱스를 리턴함*/
int PolishCalculator::ParsingNum(int i)
{
	Stack<int> number;

	/*문자의 아스키코드 - '0'을 하면 문자로 표현된 숫자를 정수로 바꾸어주는 효과가 있음*/
	while (isdigit(expression[i])) {
		number.push(expression[i++] - '0');
	}

	int num = StackToInt(number);

	parser.push(element(NUMBER, num));

	return i;
}

/* 디버깅용 함수. 문자열을 파싱한 큐를 출력*/
void PolishCalculator::printQueue()
{
	queue<element> temp = parser;

	while (!temp.empty()) {

		cout << temp.front().GetValue() << endl;
		temp.pop();

	}
}

/*중위식을 파싱한 뒤, 후위식으로 바꾸어주는 함수*/
void PolishCalculator::ToPostfix()
{

	while (!parser.empty()) {

		element e = parser.front();

		switch (e.GetType()) {

	    /*피연산자는 바로 출력함*/
		case NUMBER:

			postfix.push(e);
			break;

		/*왼쪽 괄호는 바로 출력함*/
		case PARENTHESES:

			if (e.GetValue() == LEFT_PAREN) {
				stack.push(e);
			}

			//오른쪽 괄호일 때
			else {

				element temp = stack.tos();

				/*왼쪽 괄호가 나올때까지 계속 pop한다*/

				while (temp.GetValue() != LEFT_PAREN) {

					temp = stack.pop();

					postfix.push(temp);

				}

			}

			break;

		case OPERATOR:

			element temp = stack.tos();

			/* 우선 순위 낮은 연산자가 나올때까지 계속 pop한다*/
			while (temp.GetPriority() > e.GetPriority()) {

				temp = stack.pop();

				postfix.push(temp);

			}

			/*pop이 끝나면 해당 연산자를 스택에 넣음*/
			stack.push(e);

			break;
		}

		parser.pop();

	}

	/* 나머지 남아있는 연산자를 푸쉬함*/
	while (!stack.empty()) {

		postfix.push(stack.pop());

	}
}

/*1의 자리부터 순서대로 푸쉬한 스택을 int형으로 바꾸어주는 메소드*/
int PolishCalculator::StackToInt(Stack<int> &number)
{
	int digit = 1;

	int ret = 0;

	/*1의 자리 * 1, 10의 자리 * 10, 100자리 * 100 ....을 반복하면서 더함*/
	while (!number.empty()) {

		ret += number.pop() * digit;

		digit *= 10;

	}

	return ret;

}

void PolishCalculator::Calculate()
{
	Stack <double> stack;

	/* 후위식 큐가 끝날때까지 루프 반복*/
	while (!postfix.empty()) {

		element e = postfix.front();

		int type = e.GetType();

		int value = e.GetValue();

		double result = 0.0;

		/*피연산자가 나오면 바로 푸쉬*/
		if (type == NUMBER) {

			stack.push(value);

		}

		/*연산자가 나오면 두 숫자를 차례로 pop해서 연산한 뒤 결과를 스택에 넣음*/
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

/*디버깅용 출력 함수. 후위식으로 바꾼 결과를 출력함*/
void PolishCalculator::PrintPostfix()
{
	queue <element> temp = postfix;

	cout << "postfix:";

	while (!temp.empty()) {

		element e = temp.front();

		int type = e.GetType();

		int value = e.GetValue();

		/* 연산자가 나올 경우 따로 출력으로 지정해주어야 함
		큐에 담겨 있는 값은 enum을 이용한 정수값이기 때문*/

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

		/*피연산자일 경우 그냥 숫자를 출력함.
		  후위식에는 괄호가 등장하지 않기 때문에 연산자와 피연산자만 고려하면 됨.*/

		else {
			cout << value;
		}

		temp.pop();

		cout << " ";

	}

	cout << endl;

}
