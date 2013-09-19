#include <stdio.h>
#include "list.h"

enum choise {EXIT ,ADDTO1, ADDTO2, EQUALS, VALUE, ADD, PRINT1, PRINT2};

void printChoises()
{
	printf("---------------------\n"
		   "1 - Add to 1 polynom\n"
		   "2 - Add to 2 polynom\n"
		   "3 - Equals(p,q)\n"
		   "4 - Value(p,x)\n"
		   "5 - P+Q\n"
		   "6 - Print 1 polynom\n"
		   "7 - Print 2 polynom\n"
		   "0 - Exit\n"
		   "---------------------\n");
}

void addTo(List *list)
{
	int degree = 0;
	int factor = 0;
	printf("Degree: ");
	scanf("%d", &degree);
	printf("Factor: ");
	scanf("%d", &factor);
	addListElement(list, degree, factor);
}


int main()
{
	List *p = createList();
	List *q = createList();
	List *r = createList();
	choise x = EXIT;
	int res = 0;
	int t = 0;
	do
	{
		printChoises();
		scanf("%d", &x);
		switch (x)
		{
			case ADDTO1: addTo(p); break;
			case ADDTO2: addTo(q); break;
			case EQUALS:
				if (equals(p, q))
					printf("yes\n");
				else printf("no\n");
				break;
			case VALUE:
				printf("Point: ");
				scanf("%d", &t);
				res = value(p, t);
				if (res == INT_MAX)
					printf("No elements\n");
				else printf("Result = %d\n", res);
				break;
			case ADD: addLists(p, q, r); printList(r); break;
			case PRINT1: printList(p); break;
			case PRINT2: printList(q); break;
			case EXIT: break;
		};
	}while (x != EXIT);
	destroyList(r);
	destroyList(p);
	destroyList(q);
	delete(p);
	delete(q);
	delete(r);
	return 0;
}

