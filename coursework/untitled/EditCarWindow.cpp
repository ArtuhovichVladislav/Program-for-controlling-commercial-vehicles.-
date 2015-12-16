#include "EditCarWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

EditCarWindow::EditCarWindow(MainWindow *mW, QWidget *parent, QString model): QDialog(parent)
{
    mw = mW;
    carModel = model;
    wagon = mw->wagonTree.search(carModel);         //ищем необходимый автомобиль
    refrig = mw->refrigTree.search(carModel);       //в таблицах
    tipper = mw->tipperTree.search(carModel);
    oilCar = mw->oilTree.search(carModel);

    QLabel *lbl = new QLabel("Тип:");

    carType = new QComboBox();                      //выпадающий список
    carType->addItem("Фургон");                     //типов авто
    carType->addItem("Рефрижератор");
    carType->addItem("Самосвал");
    carType->addItem("Цистерна");
    carType->setEnabled(false);

    QHBoxLayout *carTypeLay = new QHBoxLayout;      //новый слой
    carTypeLay->addWidget(lbl);
    carTypeLay->addWidget(carType);

    QLabel *condLbl = new QLabel("Состояние:");     //выпадающий список состояний
    carCondition = new QComboBox();
    for(int i=0; i<4; i++)
        carCondition->addItem(wagon->getCondition(i));

    QHBoxLayout *condLay = new QHBoxLayout;         //новый слой
    condLay->addWidget(condLbl);
    condLay->addWidget(carCondition);

    QLabel *numb = new QLabel("Номер");             //поле ввода номера
    number = new QLineEdit;
    number->setMinimumWidth(200);
    number->setMaximumWidth(200);
    QRegExp numExp("[0-9]{4}[A-Z]{2}[0-9]{1}");     //проверка на ввод
    number->setValidator(new QRegExpValidator(numExp, this));

    QHBoxLayout *numbLay = new QHBoxLayout;         //новый слой
    numbLay->addWidget(numb);
    numbLay->addWidget(number);

    QLabel *driverInfLbl = new QLabel("Информация о водителе");

    QLabel *sur = new QLabel("Фамилия");
    driverSurname = new QLineEdit;                  //поле фамилии
    driverSurname->setMinimumWidth(200);
    driverSurname->setMaximumWidth(200);
    QRegExp surExp("[А-Я]{1}[а-я]{0,30}");          //проверка на ввод
    driverSurname->setValidator(new QRegExpValidator(surExp, this));
    QHBoxLayout *surLay = new QHBoxLayout;          //новый слой
    surLay->addWidget(sur);
    surLay->addWidget(driverSurname);

    QLabel *name = new QLabel("Имя");
    driverName = new QLineEdit;                     //поле имени
    driverName->setMinimumWidth(200);
    driverName->setMaximumWidth(200);
    QRegExp nameExp("[А-Я]{1}[а-я]{1,30}");         //проверка на ввод
    driverName->setValidator(new QRegExpValidator(nameExp, this));
    QHBoxLayout *nameLay = new QHBoxLayout;         //новый слой
    nameLay->addWidget(name);
    nameLay->addWidget(driverName);

    QLabel *patr = new QLabel("Отчество");
    driverPatronymic = new QLineEdit;               //поле отчества
    driverPatronymic->setMinimumWidth(200);
    driverPatronymic->setMaximumWidth(200);
    QRegExp patrExp("[А-Я]{1}[а-я]{1,30}");         //проверка на ввод
    driverName->setValidator(new QRegExpValidator(patrExp, this));
    QHBoxLayout *patrLay = new QHBoxLayout;         //новый слой
    patrLay->addWidget(patr);
    patrLay->addWidget(driverPatronymic);

    QVBoxLayout *drInfo = new QVBoxLayout;          //слой информации
    drInfo->addWidget(driverInfLbl);                //о водителе
    drInfo->addLayout(surLay);
    drInfo->addLayout(nameLay);
    drInfo->addLayout(patrLay);

    edit = new QPushButton("Изменить");             //кнопка Изменить
    cancel = new QPushButton("Отмена");             //кнопка Добавить
    QHBoxLayout *btns = new QHBoxLayout;            //слой кнопок
    btns->addWidget(edit);
    btns->addWidget(cancel);

    QVBoxLayout *res = new QVBoxLayout;             //результирующий слой
    res->addLayout(carTypeLay);
    res->addLayout(condLay);
    res->addLayout(numbLay);
    res->addLayout(drInfo);
    res->addLayout(btns);
    setLayout(res);

    if(wagon)
    {

        //заполняем поля ввода старыми значениями
         insertValue<Wagon>(wagon, "Фургон", carType, carCondition,
                            number,
                             driverName, driverSurname,
                            driverPatronymic);
    }
    if(refrig)
    {
        //заполняем поля ввода старыми значениями
        insertValue<Refrigerator>(refrig, "Рефрижератор", carType,
                                  carCondition, number,
                            driverName, driverSurname,
                                  driverPatronymic);
    }
    if(tipper)
    {
        //заполняем поля ввода старыми значениями
        insertValue<Tipper>(tipper, "Самосвал", carType,
                            carCondition, number,
                            driverName, driverSurname,
                            driverPatronymic);
    }
    if(oilCar)
    {
        //заполняем поля ввода старыми значениями
        insertValue<OilCar>(oilCar, "Цистерна", carType,
                            carCondition, number,
                            driverName, driverSurname,
                            driverPatronymic);
    }
    connect(number,SIGNAL(textChanged(QString)),                //проверка полей на пустоту
            this, SLOT(setEditEnabled()));
    connect(carCondition, SIGNAL(currentTextChanged(QString)),  //и включение кнопки Изменить
            this, SLOT(setEditEnabled()));
    connect(driverSurname,SIGNAL(textChanged(QString)),
            this, SLOT(setEditEnabled()));
    connect(driverName,SIGNAL(textChanged(QString)),
            this, SLOT(setEditEnabled()));
    connect(driverPatronymic,SIGNAL(textChanged(QString)),
            this, SLOT(setEditEnabled()));
    connect(edit, SIGNAL(clicked()),
            this, SLOT(editClicked()));
    connect(cancel, SIGNAL(clicked()),                          //действие по кнопке отмена
            this, SLOT(cancelClicked()));
    setWindowFlags(windowFlags()
                   & ~Qt::WindowContextHelpButtonHint);         //удаление ?
}

void EditCarWindow::setEditEnabled()
{
   if(driverName->text().isEmpty() ||                           //проверка на пустоту полей
           driverSurname->text().isEmpty()
            || driverPatronymic->text().isEmpty()
           || number->text().isEmpty())
    {
        edit->setEnabled(false);                                //отключаем кнопку
    }
    else
    {
        edit->setEnabled(true);                                 //включаем
    }
    if(carCondition->currentText() == "Списан")                 //если Списан
           edit->setEnabled(true);                              //включаем
}

void EditCarWindow::editClicked()
{
    if(carType->currentText()=="Фургон")
    {
        setValue<Wagon>(wagon, carCondition, number, driverName,//устанавливаем новые значения
                        driverSurname, driverPatronymic);
    }
    if(carType->currentText()=="Рефрижератор")
    {
        setValue<Refrigerator>(refrig, carCondition, number, driverName,//устанавливаем новые значения
                        driverSurname, driverPatronymic);
    }
    if(carType->currentText()=="Самосвал")
    {
        setValue<Tipper>(tipper, carCondition, number, driverName,//устанавливаем новые значения
                        driverSurname, driverPatronymic);
    }
    if(carType->currentText()=="Цистерна")
    {
        setValue<OilCar>(oilCar, carCondition, number, driverName,//устанавливаем новые значения
                        driverSurname, driverPatronymic);
    }
    emit closed(); //сигнал закрытия окна
    this->close(); //закрываем
}

void EditCarWindow::cancelClicked()
{
    this->close(); //закрываем окно
}

template <class TYPE>
void EditCarWindow::setValue(TYPE *obj,QComboBox *cond, QLineEdit *num,
                             QLineEdit *name, QLineEdit *sur, QLineEdit *patr)
{
    obj->setCondition(cond->currentText());  //записываем в объект
    obj->setNumber(num->text());             //новые значения
    obj->setName(name->text());
    obj->setSurname(sur->text());
    obj->setPatronymic(patr->text());
}

template <class TYPE>
void EditCarWindow::insertValue(TYPE *obj, QString typeOfCar, QComboBox *type,
                                QComboBox *cond, QLineEdit *num,
                                QLineEdit *name, QLineEdit *sur, QLineEdit *patr)
{
    int index = type->findText(typeOfCar);          //заполянем поля ввода
    type->setCurrentIndex(index);                   //старыми значениями
    index = cond->findText(obj->getCondition());
    cond->setCurrentIndex(index);
    num->insert(obj->getNumber());
    sur->insert(obj->getSurname());
    name->insert(obj->getName());
    patr->insert(obj->getPatronymic());
}
