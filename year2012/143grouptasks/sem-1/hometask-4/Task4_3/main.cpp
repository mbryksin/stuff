#include <iostream>
#include <stdlib.h>
#include "listLib.h"

using namespace std;

/*
void test1()
{
	cout << "Test 1:" << endl;
	List *list = createList();
	cout << "Is empty? "<< isEmpty(list) << endl;
	delete list;
}

void test2()
{
	cout << "Test 2:" << endl;
	List *list = createList();
	addListElement(list, 5);
	cout << "Is empty? After add: "<< isEmpty(list) << endl;
	destroyList(list);
	cout << "Is empty? After destroy: "<< isEmpty(list) << endl;
	delete list;
}

void test3()
{
	cout << "Test 3:" << endl;
	List *list = createList();
	addListElement(list, 5);
	addListElement(list, 10);
	addListElement(list, 7);
	addListElement(list, 2);
	addListElement(list, 4);
	printList(list);
	destroyList(list);
	cout << "Is empty? After destroy: "<< isEmpty(list) << endl;
	delete list;
}

void test4()
{
	cout << "Test 3:" << endl;
	List *list = createList();
	addListElement(list, 5);
	addListElement(list, 10);
	addListElement(list, 7);
	addListElement(list, 2);
	addListElement(list, 4);
	printList(list);
	removeValue(list, 3);
	printList(list);
	destroyList(list);
	cout << "Is empty? After destroy: "<< isEmpty(list) << endl;
	delete list;
}
*/

void printChooses()
{
	cout << "--------------------------" << endl;
	cout << "0 - exit" << endl;
	cout << "1 - add value to sorted list" << endl;
	cout << "2 - remove value from list" << endl;
	cout << "3 - print list" << endl;
}

void tellUser ()
{
	List *list = createList();
	int decision = -1;
	while (decision != 0)
	{
		int x = 0;
		printChooses();
		cout << "Your decision: ";
		cin >> decision;
		switch (decision)
		{
		case 0:
			break;
		case 1:
			cout << "Write value: ";
			cin >> x;
			addListElement(list, x);
			break;
		case 2:
			cout << "Write value: ";
			cin >> x;
			removeValue(list, x);
			break;
		case 3:
			printList(list);
			break;
		}
	}
	destroyList(list);
	delete list;
}

int main()
{
	cout << "Dialog" << endl;
	tellUser();
	cout << endl;
	return 0;
}
