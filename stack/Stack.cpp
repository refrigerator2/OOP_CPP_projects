#include "Stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Stack::Stack()
{
	this->top = 0;
	this->dane = (int *)malloc(STACKSIZE*sizeof(int));
  assert(this->dane);
  this->size = STACKSIZE;
}

Stack::~Stack()
{
  free(this->dane);
}

void Stack::push(int a)
{
  if(this->top >= this->size){
    this->size *= 2;
    int *temp = (int *)realloc(this->dane, this->size*sizeof(int));
    assert(temp); 
    this->dane = temp;
  }
	this->dane[this->top++] = a;
}

int Stack::pop()
{
	assert(this->top > 0);
	return this->dane[--this->top];
}

void Stack::clear()
{
	this->top = 0;
}
void Stack::display()
{
  for(int i = 0; i < this->top; i++) printf("%d ", this->dane[i]);
  printf("\n");
}
void Stack::test_push(unsigned int pushes){
    for(unsigned int i = 0;i < pushes;i++){
      this->push(i);
      this->display();
    }  
}

void Stack::test_pop(unsigned int pops){
    for(unsigned int i = 0;i < pops;i++){
      printf("%d ",this->pop());  
    }  
}
