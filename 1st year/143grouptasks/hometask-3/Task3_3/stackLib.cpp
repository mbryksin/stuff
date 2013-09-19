#include "stackLib.h"
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

void push(Stack *stack, char value, int privilege)
{
	StackElement *temp = new StackElement;
	temp->value = value;
	temp->next = stack->head;
	temp->priority = privilege;
	stack->head = temp;
}

char top(Stack *stack)
{
	if (isEmpty(stack))
		{
			cout << "Stack is empty :(" << endl;
			return INT_MAX;
	}
	else
		return stack->head->value;
}

int showTopPriority(Stack *stack)
{
	if (isEmpty(stack))
		{
			cout << "Stack is empty :(" << endl;
			return INT_MAX;
	}
	else
		return stack->head->priority;
}

char pop(Stack *stack)
{
	if (isEmpty(stack))
	{
		cout << "Warning! Stack is empty!!!\n";
		return 0;
	}
	char result = top(stack);
	StackElement *tmp = stack->head;
	stack->head = stack->head->next;
	delete tmp;
	return result;
}
