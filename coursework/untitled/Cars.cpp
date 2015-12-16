#include "Cars.h"
#include <iostream>
#include <QString>

using namespace std;

Cars::Cars() : model(), number()
{
}

Cars::Cars(QString mod, QString cond, QString num) :
model(mod), number(num)
{
}

Cars::Cars(const Cars &temp)
{
	model = temp.model;
	condition = temp.condition;
	number = temp.number;
}

QString Cars::getModel()
{
	return model;
}

void Cars::setModel(QString newModel)
{
	model = newModel;
}

QString Cars::getCondition()
{
	return condition;
}

QString Cars::getCondition(int num)
{
    switch(num)
    {
    case 0:
        return "Свободен";
    case 1:
        return "В рейсе";
    case 2:
        return "На ремонте";
    case 3:
        return "Списан";
    default:
        return "Свободен";
    }
}

void Cars::setCondition(QString newCondition)
{
	condition = newCondition;
}

QString Cars::getNumber()
{
	return number;
}

void Cars::setNumber(QString newNumber)
{
	number = newNumber;
}

bool Cars::operator <(Cars &car)
{
    return model < car.model;
}

bool Cars::operator >(Cars &car)
{
    return model > car.model;
}

bool Cars::operator ==(Cars &car)
{
    return model == car.model;
}

Cars::~Cars()
{

}

Wagon:: Wagon(): Cars(), Driver(), type()
{

}

Wagon:: Wagon(QString model, QString cond, QString num, QString name, QString sur, QString patr, QString type1):
                    Cars(model,cond, num), Driver(name, sur, patr), type(type1)
{

}

QString Wagon:: getType()
{
    return type;
}

QString Wagon::getType(int num)
{
    switch(num)
    {
    case 0:
        return "Грузовой";
    case 1:
        return "Грузо-пассажирский";
    default:
        return "Грузовой";
    }
}

void Wagon:: setType(QString newType)
{
   type = newType;
}

QDataStream& operator >> (QDataStream& ds, Wagon &wagon)
{
    ds>>wagon.model>>wagon.number>>wagon.type>>wagon.condition
            >>wagon.DrSurname>>wagon.DrName>>wagon.DrPatronymic;
    return ds;
}

QDataStream& operator << (QDataStream& ds, Wagon &wagon)
{
    ds << wagon.model << wagon.number << wagon.type << wagon.condition
            << wagon.DrSurname << wagon.DrName << wagon.DrPatronymic;
    return ds;
}
Refrigerator:: Refrigerator(): Cars(), Driver(), tempDiap()
{

}

Refrigerator:: Refrigerator(QString model, QString cond, QString num, QString name, QString sur, QString patr, QString tempdiap):
                    Cars(model,cond, num), Driver(name, sur, patr), tempDiap(tempdiap)
{

}

QString Refrigerator:: getType()
{
    return getTempDiap();
}

QString Refrigerator:: getTempDiap()
{
    return tempDiap;
}

QString Refrigerator::getTempDiap(int num)
{
    switch(num)
    {
    case 0:
        return "0...12";
    case 1:
        return "-10...12";
    case 2:
        return "-20...12";
    default:
        return "0...12";
    }
}

void Refrigerator:: setTempDiap(QString newDiap)
{
   tempDiap = newDiap;
}

void Refrigerator:: setType(QString newDiap)
{
   setTempDiap(newDiap);
}
QDataStream& operator >> (QDataStream& ds, Refrigerator &refrig)
{
    ds>>refrig.model>>refrig.number>>refrig.tempDiap>>refrig.condition
            >>refrig.DrSurname>>refrig.DrName>>refrig.DrPatronymic;
    return ds;
}

QDataStream& operator << (QDataStream& ds, Refrigerator &refrig)
{
    ds<<refrig.model<<refrig.number<<refrig.tempDiap<<refrig.condition
            <<refrig.DrSurname<<refrig.DrName<<refrig.DrPatronymic;
    return ds;
}

Tipper:: Tipper(): Cars(), Driver(), type()
{

}

Tipper:: Tipper(QString model, QString cond, QString num, QString name, QString sur, QString patr, QString type1):
                    Cars(model,cond, num), Driver(name, sur, patr), type(type1)
{

}

QString Tipper:: getType()
{
    return type;
}

QString Tipper::getType(int num)
{
    switch(num)
    {
    case 0:
        return "Дорожный";
    case 1:
        return "Карьерный";
    case 2:
        return "Сочленённый";
    case 3:
        return "Подземный";
    default:
        return "Дорожный";
    }
}

void Tipper:: setType(QString newType)
{
   type = newType;
}

QDataStream& operator >> (QDataStream& ds, Tipper &tipper)
{
    ds>>tipper.model>>tipper.number>>tipper.type>>tipper.condition
            >>tipper.DrSurname>>tipper.DrName>>tipper.DrPatronymic;
    return ds;
}

QDataStream& operator << (QDataStream& ds, Tipper &tipper)
{
    ds<<tipper.model<<tipper.number<<tipper.type<<tipper.condition
            <<tipper.DrSurname<<tipper.DrName<<tipper.DrPatronymic;
    return ds;
}
OilCar:: OilCar(): Cars(), Driver(), type()
{

}

OilCar:: OilCar(QString model, QString cond, QString num, QString name, QString sur, QString patr, QString type1):
                    Cars(model,cond, num), Driver(name, sur, patr), type(type1)
{

}

QString OilCar:: getType()
{
    return type;
}

QString OilCar::getType(int num)
{
    switch(num)
    {
    case 0:
        return "Водовоз";
    case 1:
        return "Молоковоз";
    case 2:
        return "Бензовоз";
    case 3:
        return "Газовоз";
    case 4:
        return "Химическая";
    case 5:
        return "Пожарная";
    default:
        return "Водовоз";
    }
}

void OilCar:: setType(QString newType)
{
   type = newType;
}

QDataStream& operator >> (QDataStream& ds, OilCar &oilCar)
{
    ds>>oilCar.model>>oilCar.number>>oilCar.type>>oilCar.condition
            >>oilCar.DrSurname>>oilCar.DrName>>oilCar.DrPatronymic;
    return ds;
}

QDataStream& operator << (QDataStream& ds, OilCar &oilCar)
{
    ds<<oilCar.model<<oilCar.number<<oilCar.type<<oilCar.condition
            <<oilCar.DrSurname<<oilCar.DrName<<oilCar.DrPatronymic;
    return ds;
}
