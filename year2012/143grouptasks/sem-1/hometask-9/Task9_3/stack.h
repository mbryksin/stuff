#pragma once
struct StackElement;

struct Stack
{
	StackElement* head;
};

struct StackElement
{
	int value;
	StackElement *next;
};

Stack *createStack();
void destroy(Stack *stack);
bool isEmpty(Stack *stack);
void push(Stack *stack, int value);
int top(Stack *stack);
int pop(Stack *stack);
