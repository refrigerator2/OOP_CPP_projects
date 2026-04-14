#include <vector>
#define STACKSIZE 20

class Stack
{
public:
	Stack();
	~Stack();
	void push(int a);
	int pop();
	void clear();
  void display();
  void test_push(unsigned int pushes);
  void test_pop(unsigned int pops);
private:
	int top;
  int *dane;
  unsigned int size;
};
