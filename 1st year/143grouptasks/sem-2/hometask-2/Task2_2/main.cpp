#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "array.h"

enum Type {
    ARRAY = 0,
    STACK = 1
};


void doCalc(StackType *&stack, char *string)
{
    int n = strlen(string) - 1;
    for (int i = 0; i < n; i++)
    {
        if ((string[i] >= '0') && (string[i] <= '9'))
        {
            stack->add(string[i] - '0');
        } else if ((string[i] == '(') || (string[i] == ')') || (string[i] == ' '))
        {
            continue;
        } else
        {
            if (stack->isEmpty())
            {
                printf("Stack is empty!\n");
                return;
            }
            int b = stack->pop();
            if (stack->isEmpty())
            {
                printf("Stack is empty!\n");
                return;
            }
            int a = stack->pop();
            switch (string[i])
            {
                case '+': stack->add(a + b); break;
                case '-': stack->add(a - b); break;
                case '*': stack->add(a * b); break;
                case '/': stack->add(a / b); break;
            }
        }
    }
    printf("Result: %d\n", stack->pop());
}

void makeChoice(StackType *&stack)
{
    printf("-----------------------\n");
    printf("What kind of stack would you like to use?\n");
    printf("0 - Array\n");
    printf("1 - Stack\n");
    Type y = ARRAY;
    scanf("%d", &y);
    switch (y)
    {
        case ARRAY:
        {
            stack = new Array();
            break;
        }
        case STACK:
        {
            stack = new Stack();
            break;
        }
        default:
        {
            makeChoice(stack);
            return;
        }
    }
}

int main()
{
    StackType *stack = NULL;
    makeChoice(stack);
    FILE *input = fopen("input.txt", "r");
    char *string = new char[1000];
    fgets(string, 1000, input);
    //Reverse Polish notation;
    doCalc(stack, string);
    delete[] string;
    delete stack;
    fclose(input);
    return 0;
}

