#ifndef DRIVER_H
#define DRIVER_H
#include <iostream>
#include <QString>

using namespace std;

class Driver                 //Водитель
{
protected:
    QString DrName;                     //имя
    QString DrSurname;                  //фамилия
    QString DrPatronymic;               //отчество
public:
    Driver();                                   //конструктор
    Driver(QString name, QString surname,       //конструктор
           QString patronymic);                 //с параметрами
    Driver(const Driver &temp);                 //конструктор копирования

    QString getName();                          //получить имя
    void setName(QString newName);              //новое имя

    QString getSurname();                       //получить фамилию
    void setSurname(QString newSurname);        //новая фамилия

    QString getPatronymic();                    //получить отчество
    void setPatronymic(QString newPatronymic);  //новое отчество

    QString getFIO();                           //скоращённое ФИО

    ~Driver();                                  //деструктор
};
#endif
