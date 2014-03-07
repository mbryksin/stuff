#include <iostream>
#include <stdio.h>
#include "list.h"
#include "array.h"

using namespace std;

enum ListChoise {
    ARRAY = 0,
    LIST = 1
};

enum CommandChoise {
    EXIT = 0,
    ADD = 1,
    REMOVE = 2,
    PRINT = 3
};

void printCommands(ListType *&list)
{
    cout << "--------------------" << endl;
    cout << "0 - exit\n1 - add\n2 - remove\n3 - print\n";
    CommandChoise command = EXIT;
    scanf("%d", &command);
    switch (command)
    {
    case EXIT: return;
    case ADD:
        {
            cout << "Write value:\n";
            int value = 0;
            cin >> value;
            list->add(value);
            break;
        }
    case REMOVE:
        {
            cout << "Write value:\n";
            int value = 0;
            cin >> value;
            list->remove(value);
            break;
        }
        break;
    case PRINT:
        {
            list->print();
        }
        break;
    default:
        printCommands(list);
        return;
    }
    printCommands(list);
}

void makeChoice(ListType *&list)
{
    cout << "--------------------" << endl;
    cout << "What type of List do you want to create?" << endl;
    cout << "0 - Array" << endl;
    cout << "1 - List" << endl;
    ListChoise x = ARRAY;
    scanf("%d", &x);
    switch (x)
    {
        case ARRAY:
        {
            list = new Array();
            break;
        }
        case LIST:
        {
            list = new List();
            break;
        }
        default:
            makeChoice(list);
            return;
    }
}

int main()
{
    ListType *list = NULL;
    makeChoice(list);
    printCommands(list);
    delete list;
    return 0;
}
