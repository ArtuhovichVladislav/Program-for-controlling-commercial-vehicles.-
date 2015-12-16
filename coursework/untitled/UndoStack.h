#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <QString>
using namespace std;

class undoStack                             //стек отмены действий
{
public:
    int actionCode;                          //код действия
    QString data;                           //данные
    undoStack *next;
public:
    undoStack *head;                        //голова стека
public:
    undoStack();                            //конструктор
    undoStack(int actionCode, QString data);//конструктор с парметрами
    void push(undoStack *newAction);        //добавление в стек
    undoStack* pop();                       //извлечение
    QString getData();                      //получение данных
    int getActionCode();                    //получение кода
    bool isEmpty();                         //проверка на пустоту
};

#endif // UNDOSTACK_H
