#include <iostream>
#include "listLib.h"

int search (List *target, int const k)
{
	bool canDelete = true;
	int result = 0;
	List *current;
	while (canDelete)
	{
		for (int i = 1; i < k; i++)
		{
			current = target;
			target = target->next;
		}
		canDelete = destroyTargetElement(current);
		//printCircleList(current->);
		if (canDelete)
		{
			target = current->next;
		}
		else
		{
			result = target->value;
		}
	}
	delete target;
	return result;
}

int main()
{
	int n = 0;
	std::cout << "Write number of players:\n";
	std::cin >> n;
	int i = 0;
	std::cout << "What count of player will live?:\n";
	std::cin >> i;
	bool hasResult = false;
	std::cout << "Positions for live: ";
	for (int j = 2; j <= n; j++)
	{
		List *head = new List;
		head->next = NULL;
		createCircleList(head, n);
		if (search(head, j) == i)
		{
			std::cout << j << " ";
			hasResult = true;
		}
	}
	if (! hasResult)
	{
		std::cout << "There are no positions for live\n";
	}
	std::cout << "\n";
	return 0;
}
