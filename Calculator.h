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

/* 제네릭한 변수를 담을 수 있는 스택 구현. 파일 분리가 쉽지 않아 헤더에 포함시킴*/
template <class T>
class Stack {

private:

	// 스택의 탑을 나타내는 변수
	int top;

	//실제 데이터가 담기는 공간
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