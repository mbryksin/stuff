#pragma once
#include "class.h"

///Класс списка с реализацией через линейный список
class List: public ListType {
public:
    ///Конструктор создает пустой список
    List();
    ///Деструктор удаляет все элементы списка из памяти
    ~List();
    void add(int value);
    void remove(int value);
    void print();
protected:
    ///Структура, реализующая связанный список, с указателем на голову и хвост
    struct ListElement
    {
        int value;
        ListElement *next;
    };
    ListElement *head;
    ListElement *tail;
private:
    bool isEmpty();
};
