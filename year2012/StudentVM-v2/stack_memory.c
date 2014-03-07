#include "stack_memory.h"

#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include <limits.h>
#include <memory.h>

Stack *create_stack()
{
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->head = NULL;
    return stack;
}

int stack_is_empty(Stack *stack)
{
    return (stack->head == NULL ? 1 : 0);
}

void destroy(Stack *stack)
{
    while (!stack_is_empty(stack))
    {
        StackElement *tmp = stack->head;
        stack->head = stack->head->next;
        free(tmp);
    }
}

void push(Stack *stack, int value)
{
    StackElement *temp = (StackElement *) malloc(sizeof(StackElement));
    temp->value = value;
    temp->next = stack->head;
    stack->head = temp;
}

int top(Stack *stack)
{
    return stack->head->value;
}

int pop(Stack *stack)
{
    int result = top(stack);
    StackElement *tmp = stack->head;
    stack->head = stack->head->next;
    free(tmp);
    return result;
}

Memory *create_memory()
{
    Memory *memory = (Memory *) malloc(sizeof(Memory));
    memory->array = (int *) malloc(2097152 * sizeof(int)); //2^21 = 2097152
    return memory;
}

void clean_memory(Memory *memory)
{
    free(memory);
}
