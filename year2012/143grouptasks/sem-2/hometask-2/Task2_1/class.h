#pragma once

///Класс-родитель, линейный список
class ListType {
public:
    /*
      * Удаление из памяти списка
    */
    virtual ~ListType() {}
    /*
    * Добавить в список элемент
    * @param value Число, которое добавляется в список
    */
    virtual void add(int value) = 0;
    /*
    * Удалить элемент из списка
    * @param value Элемент, который удаляется из списка
    */
    virtual void remove(int value) = 0;
    ///Функция, распечатывающая список
    virtual void print() = 0;
};
