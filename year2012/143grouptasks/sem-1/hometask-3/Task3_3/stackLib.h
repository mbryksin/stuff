#pragma once
struct StackElement;

struct Stack
{
	StackElement* head;
};

struct StackElement
{
	char value;
	int priority;
	StackElement *next;
};

Stack *createStack();
void destroy(Stack *stack);
bool isEmpty(Stack *stack);
void push(Stack *stack, char value, int privilege);
char top(Stack *stack);
char pop(Stack *stack);
int showTopPriority(Stack *stack);
