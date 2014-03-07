#include "stack.h"
#include <stdlib.h>
#include <limits.h>
#include <iostream>

using namespace std;

Stack *createStack()
{
	Stack *stack = new Stack;
	stack->head = NULL;
	return stack;
}

void destroy(Stack *stack)
{
	while (! isEmpty(stack))
	{
		StackElement *tmp = stack->head;
		stack->head = stack->head->next;
		delete tmp;
	}
}

bool isEmpty(Stack *stack)
{
	return stack->head == NULL;
}

void push(Stack *stack, int value)
{
	StackElement *temp = new StackElement;
	temp->value = value;
	temp->next = stack->head;
	stack->head = temp;
}

int top(Stack *stack)
{
	if (isEmpty(stack))
	{
		return INT_MAX;
	}
	return stack->head->value;
}

int pop(Stack *stack)
{
	if (isEmpty(stack))
	{
		return INT_MAX;
	}
	StackElement *tmp = stack->head;
	stack->head = stack->head->next;
	int result = tmp->value;
	delete tmp;
	return result;
}


