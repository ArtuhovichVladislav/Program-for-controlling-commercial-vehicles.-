#include "Driver.h"

using namespace std;

Driver::Driver() :DrName(), DrSurname(), DrPatronymic()
{

}

Driver::Driver(QString name, QString surname, QString patronymic) :
DrName(name), DrSurname(surname), DrPatronymic(patronymic)
{
}

Driver::Driver(const Driver &temp)
{
	DrName = temp.DrName;
	DrSurname = temp.DrSurname;
	DrPatronymic = temp.DrPatronymic;
}

QString Driver::getName()
{
	return DrName;
}

void Driver::setName(QString newName)
{
	DrName = newName;
}

QString Driver::getSurname()
{
	return DrSurname;
}

void Driver::setSurname(QString newSurname)
{
	DrSurname = newSurname;
}

QString Driver::getPatronymic()
{
	return DrPatronymic;
}

void Driver::setPatronymic(QString newPatronymic)
{
	DrPatronymic = newPatronymic;
}

QString Driver::getFIO()
{
    QString fio;

	fio = DrSurname +' '+ DrName[0] + '.' + ' ' + DrPatronymic[0] + '.';
	return fio;
}

Driver::~Driver()
{

}
