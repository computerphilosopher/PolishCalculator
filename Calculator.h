/* ��� �ߺ� ���� ���� */
#ifndef CALCULATOR_H

#include <string>
#include <queue>
#include <stack>

using namespace std;

/*������ ������ ��Ÿ���� ���
  ��ȣ�� �����ڴ� �ƴ����� �켱������ ��Ÿ���� ���� �ʿ�*/
enum Operation
{

	ADD,
	SUB,
	MUL,
	DIV,
	LEFT_PAREN,
	RIGHT_PAREN,

};

/*element�� ����� Ÿ���� �����ϴ� �Լ�.
  ������, ��ȣ, �ǿ����ڸ� ��Ÿ��*/
enum DataType
{

	OPERATOR,
	PARENTHESES,
	NUMBER,

};


/* ������ ���� �� �ִ� ���� ����. ���� �и��� ���� �ʾ� ����� ���Խ�Ŵ
   ���ø����� �����Ͽ��� ������ ����, �Ǽ�, Ŭ���� ���� ��� ���� ����
*/
template <class T>
class Stack {

private:

	// ������ ž�� ��Ÿ���� ����
	int top;

	//���� �����Ͱ� ���� ����
	T stack[1000];

public:

	/*�ʱ� top�� ���°��� -1.
	  push�� �� top�� ���� 1 ������Ű�� ������ �迭�� ù ĭ���� �����ϰ� ��*/
	Stack()
	{
		top = -1;
	}

	void push(T e)
	{	

		top++;

		stack[top] = e;

	}
	
	/*������ top�� �����ϸ� ����*/
	T pop()
	{

		T ret = stack[top];

		top--;

		return ret;

	}

	/*������ top�� ����(���������� ����*/
	T tos()
	{
		return stack[top];
	}

	/*������ ������� Ȯ�� */
	bool empty()
	{
		if (top == -1) {

			return true;

		}

		else {

			return false;

		}
	}

	/*������ ũ�� Ȯ�� */
	int size()
	{
		return top + 1;
	}
};


/* ���ÿ� ���� �ڷᱸ��. ���� �ڸ����� ���� ������ �� �ֵ��� ������*/

class element {

private:

	//������, �ǿ�����, ��ȣ�� ����
	int dataType;

	//�ǿ����ڸ� ������ ��, �����ڳ� ��ȣ�� ��� ������ ����j
	int value;

public:

	element(int dataType, int value);

	element();

	~element();

	int GetType();

	int GetValue();

	int GetPriority();
};

class PolishCalculator{

private:

	/*����ڰ� �Է��� ��Ʈ���� �ؼ��ؼ� element�� �����ϴ� ť */
	queue <element> parser;

	/*����ڰ� �Է��� ������ ���� */
	string expression;

	/*���������� ��ȯ�� ����� ����*/
	queue <element> postfix;

	/*������ ��꿡 ���̴� ����*/
	Stack <element> stack;

public:

	PolishCalculator(string expression);
	
	PolishCalculator();
	
	~PolishCalculator();

	void ParsingExpression();

	int ParsingNum(int i);

	void printQueue();

	void ToPostfix();

	int StackToInt(Stack<int> &number);
	
	void Calculate();
	
	void PrintPostfix();

};



/* ��� �ߺ� ���� ���� */
#endif