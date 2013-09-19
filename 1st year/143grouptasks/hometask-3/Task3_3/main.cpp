#include <iostream>
#include "stackLib.h"
#include <stdio.h>
#include <limits.h>
#define maximum 10000

using std::cout;
using std::cin;
using std::endl;

void rewriteToPostfix()
{
	Stack *stack = createStack();

	char infix[maximum] = {};
	char result[maximum] = {};
	cout << "Hello, user! Write me infix form:\n";
	fgets(infix, INT_MAX, stdin);
	int j = 0;
	int i = -1;
	while (infix[j] != '\n')
	{
		if (infix[j] <= '9' && infix[j] >= '0')
		{
			result[++i] = infix[j];
		}
		else if (infix[j] == '+' || infix[j] == '-')
		{
			while (!isEmpty(stack) && showTopPriority(stack) <= 2)
			{
				result[++i] = pop(stack);
			}
			push(stack, infix[j], 2);
		}
		else if (infix[j] == '*' || infix[j] == '/')
		{
			while (!isEmpty(stack) && showTopPriority(stack) <= 1)
			{
				result[++i] = pop(stack);
			}
			push(stack, infix[j], 1);
		}
		else if (infix[j] == '^')
		{
			while (!isEmpty(stack) && showTopPriority(stack) <= 0)
			{
				result[++i] = pop(stack);
			}
			push(stack, infix[j], 0);
		}
		else if (infix[j] == '(')
		{
			push(stack, infix[j], 3);
		}
		else if (infix[j] == ')')
		{
			while (!isEmpty(stack) && showTopPriority(stack) != 3)
			{
				result[++i] = pop(stack);
			}
			pop(stack);
		}
		j++;
	}
	while (! isEmpty(stack))
	{
		result[++i] = pop(stack);
	}
	destroy(stack);
	delete stack;
	cout << result;
}

int main()
{
	rewriteToPostfix();
	cout << "\n";
}
