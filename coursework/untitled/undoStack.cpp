#include "undoStack.h"

undoStack::undoStack(int actionCode, QString data)
{
    this->actionCode = actionCode;      //конструктор с параметрами
    this->data = data;
    this->next = NULL;
    this->head = NULL;
}

undoStack::undoStack()
{
    this->head = NULL;                  //конструктор
}

void undoStack::push(undoStack *newAction)
{
    if (!head)
    {
        head = newAction;               //создаём стек
        head->next = NULL;
    }
    else
    {
        newAction->next = head;         //добавляем в стек
        head = newAction;
    }
}

undoStack* undoStack::pop()
{
    undoStack *temp = head;
    undoStack *returnedValue;
    returnedValue = new undoStack(head->actionCode, head->data);
    head = head->next;
    delete temp;
    return returnedValue;               //извлекаем из стека
}

QString undoStack::getData()
{
    return data;                        //получение данных
}

int undoStack::getActionCode()
{
    return actionCode;                  //получение кода
}

bool undoStack::isEmpty()               //проверка на пустоту
{
    if (head){
        return false;
    }
    else{
        return true;
    }
}

