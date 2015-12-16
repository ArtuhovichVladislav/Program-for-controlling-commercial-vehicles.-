#ifndef CARS_H
#define CARS_H
#include <iostream>
#include <QString>
#include "Driver.h"
#include <QDataStream>
using namespace std;

class Cars                                      //базовый класс
{
protected:
    QString model;                              //марка/модель
    QString condition;                          //состояние авто
    QString number;                             //номер
public:                                         //конструктор
	Cars();
    Cars(QString mod,QString cond, QString num);//конструктор с параметрами
    Cars(const Cars &temp);                     //конструктор копирования

    QString getModel();                         //возвращает модель
    void setModel(QString newModel);            //новая модель/марка

    QString getCondition();                     //текущее состояние
    QString getCondition(int num);              //состояния по номерам
    void setCondition(QString newCondition);    //новое состояние

    QString getNumber();                        //текущий номер
    void setNumber(QString newNumber);          //новый номер

    bool operator <(Cars &car);                 //оператор меньше
    bool operator >(Cars &car);                 //оператор больше
    bool operator ==(Cars &car);                //оператор ==

    ~Cars();                                    //деструктор
};


class Wagon: public Cars, public Driver      //класс Фургон
{
private:
    QString type;                                     //тип фургона
public:
    Wagon();                                          //констркутор
    Wagon(QString model, QString cond, QString num,   //конструктор
          QString name, QString sur, QString patr,    //с параметрами
          QString type1);
    QString getType();                                 //текущий тип
    QString getType(int num);                          //типы по номерам
    void setType(QString newType);                     //новый тип

    friend QDataStream& operator >> (QDataStream& ds, //операторы ввода/вывода
                                     Wagon &wagon);    //в/из потока
    friend QDataStream& operator << (QDataStream& ds,
                                     Wagon &wagon);
};

class Refrigerator: public Cars, public Driver  //класс Рефрижератор
{
private:
    QString tempDiap;                                      //температура
public:
    Refrigerator();                                         //конструктор
    Refrigerator(QString model, QString cond, QString num,  //конструктор
                 QString name, QString sur, QString patr,   //с параметрами
                 QString tempdiap);
    QString getType();                                      //значение температуры
    QString getTempDiap();                                  //значение температуры
    QString getTempDiap(int num);                           //значение темп. по номерам
    void setTempDiap(QString newDiap);
    void setType(QString newDiap);
    friend QDataStream& operator >> (QDataStream& ds,       //операторы ввода/вывода
                                     Refrigerator &refrig);//в/из потока
    friend QDataStream& operator << (QDataStream& ds,
                                     Refrigerator &refrig);
};

class Tipper: public Cars, public Driver  //класс Самосвал
{
private:
    QString type;                                          //тип самосвала
public:
    Tipper();                                               //конструктор
    Tipper(QString model, QString cond, QString num,        //конструктор
           QString name, QString sur, QString patr,         //с параметрами
           QString type1);
    QString getType();                                      //текущий тип
    QString getType(int num);                               //тип по номерам
    void setType(QString newType);                          //новый тип

    friend QDataStream& operator >> (QDataStream& ds,       //операторы ввода/вывода
                                     Tipper &tipper);       //в/из потока
    friend QDataStream& operator << (QDataStream& ds,
                                     Tipper &tipper);
};

class OilCar: public Cars, public Driver                    //класс Цистерна
{
private:
    QString type;                                           //тип цистерны
public:
    OilCar();                                               //констурктор
    OilCar(QString model, QString cond, QString num,        //конструктор
           QString name, QString sur, QString patr,         //с парметрами
           QString type1);
    QString getType();                                      //текущий тип
    QString getType(int num);
    void setType(QString newType);                          //типы по номерам
    friend QDataStream& operator >> (QDataStream& ds,       //операторы ввода/вывода
                                     OilCar &oilCar);       //в/из потока
    friend QDataStream& operator << (QDataStream& ds,
                                     OilCar &oilCar);
};

#endif
