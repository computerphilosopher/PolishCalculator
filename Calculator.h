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

/* ���׸��� ������ ���� �� �ִ� ���� ����. ���� �и��� ���� �ʾ� ����� ���Խ�Ŵ*/
template <class T>
class Stack {

private:

	// ������ ž�� ��Ÿ���� ����
	int top;

	//���� �����Ͱ� ���� ����
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

	element(int dataType, int value);

	element();

	int GetType();

	int GetValue();

	int GetPriority();
};

class PolishCalculator{

private:

	queue <element> parser;
	string expression;
	queue <element> postfix;
	Stack <element> stack;

public:

	PolishCalculator(string expression);

	void ParsingExpression();

	int ParsingNum(int i);

	void printQueue();

	void ToPostfix();

	int StackToInt(Stack<int> &number);
	
	void Calculate();
	
	void PrintPostfix();
};