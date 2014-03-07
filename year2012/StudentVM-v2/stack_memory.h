#ifndef STACK_MEMORY_H
#define STACK_MEMORY_H

typedef struct StackElement
{
    int value;
    struct StackElement *next;
} StackElement;

typedef struct Stack
{
    StackElement *head;
} Stack;

typedef struct Memory
{
    int *array;
} Memory;

Stack *create_stack();
void destroy(Stack *stack);
int stack_is_empty(Stack *stack);
void push(Stack *stack, int value);
int top(Stack *stack);
int pop(Stack *stack);

Memory *create_memory();
void clean_memory(Memory *memory);

#endif // STACK_MEMORY_H

