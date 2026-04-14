#include "Stack.h"
#include <stdio.h>




int main()
{
	Stack s1;
  s1.test_push(41);
  s1.test_pop(29);
  //pop_test(28, s1);
  s1.display();
  s1.clear();
  //s1.pop();
	return 0;
}
