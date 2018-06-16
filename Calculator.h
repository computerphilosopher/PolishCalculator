#include <string>
#include <queue>
#include <stack>

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
		return stack[top--];
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
			return false;;
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