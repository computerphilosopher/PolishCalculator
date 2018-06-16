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

/* 변수를 담을 수 있는 스택 구현. 파일 분리가 쉽지 않아 헤더에 포함시킴
   템플릿으로 구현하였기 때문에 정수, 실수, 클래스 등을 모두 저장 가능

*/
template <class T>
class Stack {

private:

	// 스택의 탑을 나타내는 변수
	int top;

	//실제 데이터가 담기는 공간
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
	
	/*스택의 top을 제거하며 리턴*/
	T pop()
	{
		return stack[top--];
	}

	/*스택의 top을 리턴(제거하지는 않음*/
	T tos()
	{
		return stack[top];
	}

	/*스택이 비었는지 확인 */
	bool empty()
	{
		if (top == -1) {
			return true;
		}
		else {
			return false;;
		}
	}

	/*스택의 크기 확인 */
	int size()
	{
		return top + 1;
	}
};


/* 스택에 담을 자료구조. 여러 자릿수의 수를 저장할 수 있도록 구현함*/

class element {

private:

	//연산자, 피연산자, 괄호를 구분
	int dataType;

	//피연산자면 숫자의 값, 연산자나 괄호일 경우 종류를 저장j
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

	/*사용자가 입력한 스트링을 해석해서 element로 저장하는 큐 */
	queue <element> parser;

	/*사용자가 입력한 수식을 저장 */
	string expression;

	/*후위식으로 변환한 결과를 저장*/
	queue <element> postfix;

	/*후위식 계산에 쓰이는 스택*/
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