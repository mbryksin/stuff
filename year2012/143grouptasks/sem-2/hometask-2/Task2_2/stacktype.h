#pragma once

///Класс стэка
class StackType {
public:
    ///Виртуальный деструктор, который удаляет стэк из памяти
    virtual ~StackType() {}
    /*
      * Функция, добавляющая число на вершину стека
      * @param value Добавляемое число
    */
    virtual void add(int value) = 0;
    /*
      * Функция, забирающая число с вершины стека
      * @return Число с вершины стека
    */
    virtual int pop() = 0;
    ///Пуст стек или нет
    virtual bool isEmpty() = 0;
};
