#include <iostream>
#include <vector>

using namespace std;

enum Operation {
	ADD, 
	SUB, 
	MUL, 
	DIV
};

enum DataType{
	OPERATOR,
	INTEGER,
	DOUBLE,
	LEFT_PAREN,
	RIGHT_PAREN,
};

enum Symbol {
	NUM,
	DOT,
	OTHERS
};

enum Count {
	STATE_COUNT = 5,
	SYMBOL_COUNT = 3
};

enum STATE {
	START,
	INPUT_INT,
	INPUT_DECIMAL,
	END,
	ERROR
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
	double value;

public:
	element(int dataType, double value) {
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
	Stack <element> stack;
	string expression;

public:
	
	PolishCalculator(string expression) {
		this->expression = expression;
		cout << ParsingNum(0).GetValue() << endl;
	}

	element ParsingNum(int i) {
		Stack<int> integerPart;
	}


	void Calculate() {

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

	string exp = "123.23";
	Stack<element> p;
	p.push(element(INTEGER, 5.0));

	cout << p.pop().GetValue() << endl;
	getchar();
}