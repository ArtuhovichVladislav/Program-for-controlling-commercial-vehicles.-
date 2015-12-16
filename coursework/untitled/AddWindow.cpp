#include "AddWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

AddWindow::AddWindow(MainWindow *mW, QWidget *parent): QDialog(parent)
{
    mw = mW;
    QLabel *lbl0 = new QLabel("Выберите тип:");    //текст

    carType = new QComboBox();                     //создаём выплывающий список
    carType->addItem("Фургон");
    carType->addItem("Рефрижератор");
    carType->addItem("Самосвал");
    carType->addItem("Цистерна");
    carType->setMaximumWidth(210);                  //устанавливаем ширину
    carType->setMinimumWidth(210);

    QHBoxLayout *cb0 = new QHBoxLayout;             //новый горизонтальный слой
    cb0->addWidget(lbl0);
    cb0->addWidget(carType);                        //добавляем в него список и тескт

    QLabel *lbl = new QLabel("Введите марку:");     //ввод марки авто
    carModel = new QLineEdit;                       //поле ввода
    carModel->setMaximumWidth(195);                 //устанавливаем ширину
    carModel->setMinimumWidth(195);

    QRegExp exp("[А-ЯA-Z]{1,4}[а-яa-z]{0,10}[ ]{0,1}[А-ЯA-Z0-9]{0,1}[a-zа-я0-9]{0,10}");
    carModel->setValidator(new QRegExpValidator(exp, this)); //проверка на ввод

    QHBoxLayout *cb = new QHBoxLayout;               //новый слой
    cb->addWidget(lbl);
    cb->addWidget(carModel);

    wagonSpec = new QComboBox();                    //списки
    refrigSpec = new QComboBox();                   //характерстик
    tipperSpec = new QComboBox();                   //различных
    oilSpec = new QComboBox();                      //авто

    wagonLbl = new QLabel("Вид фургона:");
    for(int i =0; i < 2; i++)
        wagonSpec->addItem(wagon.getType(i));       //создаём список видов фургона
    refrigLbl = new QLabel("Температурный диапазон:");
    for(int i=0; i<3; i++)                           //список температур рефр.
        refrigSpec->addItem(refrig.getTempDiap(i));
    tipperLbl = new QLabel("Вид самосвала:");
    for(int i=0; i<3; i++)                           //виды самосвала
        tipperSpec->addItem(tipper.getType(i));
    oilLbl = new QLabel("Вид цистерны:");
    for(int i=0; i<3; i++)                           //виды цистерн
        oilSpec->addItem(oilCar.getType(i));
    tipperLbl->hide();                              //скрываем названия списков
    refrigLbl->hide();
    oilLbl->hide();
    refrigSpec->hide();
    tipperSpec->hide();
    oilSpec->hide();

    connect(carType,SIGNAL(currentTextChanged(QString)), //слот показа характеристик
            this, SLOT(cbChanged()));                     //активного типа авто

    QHBoxLayout *cbs = new QHBoxLayout;                   //новый слой
    cbs->addWidget(wagonLbl);                              //добавляем в него
    cbs->addWidget(refrigLbl);
    cbs->addWidget(tipperLbl);                             //списки и названия
    cbs->addWidget(oilLbl);
    cbs->addWidget(wagonSpec);
    cbs->addWidget(refrigSpec);
    cbs->addWidget(tipperSpec);
    cbs->addWidget(oilSpec);

    QLabel *lbl1 = new QLabel("Состояние:");
    carCondition = new QComboBox();                     //список состояний
    for(int i=0; i<4; i++)
        carCondition->addItem(wagon.getCondition(i));

    QHBoxLayout *cb1 = new QHBoxLayout;                 //новый слой
    cb1->addWidget(lbl1);
    cb1->addWidget(carCondition);

    QLabel *lbl2 = new QLabel("Регистрационный номер: ");
    carRegion = new QComboBox();                          //список номеров регионов
    for(int i=1; i<=7;i++)
        carRegion->addItem(QString::number(i));

    carNumber = new QLineEdit;                            //номер авто
    carNumber->setMaxLength(4);
    carNumber->setMaximumWidth(100);

    QRegExp numExp("[0-9]{4}");                             //проверка на ввод
    carNumber->setValidator(new QRegExpValidator(numExp, this));

    carSym = new QLineEdit;                                 //символы номера
    carSym->setMaximumWidth(50);
    QRegExp symExp("[A-Z]{2}");                             //проверка на ввод
    carSym->setValidator(new QRegExpValidator(symExp, this));

    QHBoxLayout *cb2 = new QHBoxLayout;                     //новый слой номера
    cb2->addWidget(lbl2);
    cb2->addWidget(carNumber);
    cb2->addWidget(carSym);
    cb2->addWidget(carRegion);

    QLabel *lbl3 = new QLabel("Информация о водителе");

    QLabel *sur = new QLabel("Фамилия");
    driverSurname = new QLineEdit;
    driverSurname->setMaximumWidth(195);
    driverSurname->setMinimumWidth(195);
    QRegExp surExp("[А-Я]{1}[а-я]{0,30}");                    //проверка на ввод
    driverSurname->setValidator(new QRegExpValidator(surExp, this));

    QHBoxLayout *cb3 = new QHBoxLayout;                        //слой фамилии
    cb3->addWidget(sur);
    cb3->addWidget(driverSurname);

    QLabel *name = new QLabel("Имя");
    driverName = new QLineEdit;
    driverName->setMaximumWidth(195);
    driverName->setMinimumWidth(195);
    QRegExp nameExp("[А-Я]{1}[а-я]{1,30}");                     //проверка на ввод
    driverName->setValidator(new QRegExpValidator(nameExp, this));
    QHBoxLayout *cb4 = new QHBoxLayout;                         //слой имени
    cb4->addWidget(name);
    cb4->addWidget(driverName);

    QLabel *sname = new QLabel("Отчество");
    driverSecName = new QLineEdit;
    driverSecName->setMaximumWidth(195);
    driverSecName->setMinimumWidth(195);
    QRegExp patrExp("[А-Я]{1}[а-я]{1,30}");
    driverSecName->setValidator(new QRegExpValidator(patrExp, this));
    QHBoxLayout *cb5 = new QHBoxLayout;                         //слой отчества
    cb5->addWidget(sname);
    cb5->addWidget(driverSecName);

    QVBoxLayout *drInfo = new QVBoxLayout;
    drInfo->addWidget(lbl3);
    drInfo->addLayout(cb3);
    drInfo->addLayout(cb4);
    drInfo->addLayout(cb5);

    ok = new QPushButton("Добавить");                            //кнопка ок
    ok->setEnabled(false);                                       //отключаем её
    cancel = new QPushButton("Отмена");                          //кнопка отмена
    QHBoxLayout *btns = new QHBoxLayout;                         //слой кнопок
    btns->addWidget(ok);
    btns->addWidget(cancel);

    QVBoxLayout *res = new QVBoxLayout;                          //общий слой
    res->addLayout(cb0);
    res->addLayout(cb);
    res->addLayout(cbs);
    res->addLayout(cb1);
    res->addLayout(cb2);
    res->addLayout(drInfo);
    res->addLayout(btns);
    setLayout(res);

    connect(carModel,SIGNAL(textChanged(QString)),              //проверяем
            this, SLOT(setOkEnabled()));
    connect(carNumber,SIGNAL(textChanged(QString)),             //на пустоту
            this, SLOT(setOkEnabled()));
    connect(carSym,SIGNAL(textChanged(QString)),                //поля ввода
            this, SLOT(setOkEnabled()));
    connect(carCondition,SIGNAL(currentTextChanged(QString)),   //и включаем
            this, SLOT(setOkEnabled()));
    connect(driverSurname,SIGNAL(textChanged(QString)),         //кнопку добавить
            this, SLOT(setOkEnabled()));
    connect(driverName,SIGNAL(textChanged(QString)),
            this, SLOT(setOkEnabled()));
    connect(driverSecName,SIGNAL(textChanged(QString)),
            this, SLOT(setOkEnabled()));
    connect(ok, SIGNAL(clicked()), this,                        //обработка нажатия
            SLOT(okClicked()));                                 //добавить
    connect(cancel, SIGNAL(clicked()),                          //..отмена
            this, SLOT(cancelClicked()));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //отключение ?
    setWindowTitle("Добавить автомобиль");                            //название окна
    setWindowIcon(QIcon(":/Icons/icons/Add.png"));                      //иконка окна
}

void AddWindow::setOkEnabled()
{
    if((carModel->text().isEmpty())                 //проверяем поля на пустоту
            || driverName->text().isEmpty() || driverSurname->text().isEmpty()
            || driverSecName->text().isEmpty())
    {
        ok->setEnabled(false); //отключаем кнопку
    }
    else
    {
        ok->setEnabled(true); //включаем
    }
    if(!carModel->text().isEmpty() && (carCondition->currentText() == "Списан"))
        ok->setEnabled(true); //включаем для состояния списан
}

void AddWindow::cbChanged()
{
    if(carType->currentText()=="Фургон")        //проверяем какой тип выбран
    {
        wagonLbl->show();
        tipperLbl->hide();                      //показываем присущие ему
        refrigLbl->hide();                      //характеристики
        oilLbl->hide();                          //остальное скрываем
        wagonSpec->show();
        refrigSpec->hide();
        tipperSpec->hide();
        oilSpec->hide();
    }
    if(carType->currentText()=="Рефрижератор")
    {
        wagonLbl->hide();
        tipperLbl->hide();
        refrigLbl->show();
        oilLbl->hide();
        refrigSpec->show();
        wagonSpec->hide();
        tipperSpec->hide();
        oilSpec->hide();
    }
    if(carType->currentText()=="Самосвал")
    {
        wagonLbl->hide();
        tipperLbl->show();
        refrigLbl->hide();
        oilLbl->hide();
        tipperSpec->show();
        wagonSpec->hide();
        refrigSpec->hide();
        oilSpec->hide();
    }
    if(carType->currentText()=="Цистерна")
    {
        wagonLbl->hide();
        tipperLbl->hide();
        refrigLbl->hide();
        oilLbl->show();
        oilSpec->show();
        wagonSpec->hide();
        refrigSpec->hide();
        tipperSpec->hide();
    }
}

void AddWindow::okClicked()
{
    if(carType->currentText()=="Фургон")                //считываем занчения
    {                                                   //окна и добаляем в объект
        setValue<Wagon>(&wagon, wagonSpec);
        undoAdd<Wagon>(wagon, 1);                       //заносим в стек
        mw->wagonTree.createTree(wagon);
    }
    if(carType->currentText()=="Рефрижератор")
    {
        setValue<Refrigerator>(&refrig, refrigSpec);
        undoAdd<Refrigerator>(refrig, 2);                   //...
        mw->refrigTree.createTree(refrig);
    }
    if(carType->currentText()=="Самосвал")
    {
        setValue<Tipper>(&tipper, tipperSpec);
        undoAdd<Tipper>(tipper, 3);                         //...
        mw->tipperTree.createTree(tipper);
    }
    if(carType->currentText()=="Цистерна")
    {
        setValue<OilCar>(&oilCar, oilSpec);
        undoAdd<OilCar>(oilCar, 4);                         //...
        mw->oilTree.createTree(oilCar);
    }
    emit closed();
    this->close();
}

template <class TYPE>
void AddWindow::undoAdd(TYPE obj, int tab)
{
    undoStack *action;                              //созадём стек отмены добавления
    action = new undoStack(wasAdd, obj.getModel());

    if(tab == 1)
    {
        mw->undoDelWag.push(action);                    //добавляем туда модель
        mw->wagonActive();
    }
    if(tab == 2)
    {
        mw->undoDelRefrig.push(action);
        mw->refrigActive();
    }
    if(tab == 3)
    {
        mw->undoDelTipper.push(action);
        mw->tipperActive();
    }
    if(tab == 4)
    {
        mw->undoDelOil.push(action);
        mw->oilCarActive();
    }
    emit mw->stackChanged();
}

void AddWindow::cancelClicked()
{
    this->close();              //закрытие текущего окна
}

template <class TYPE>
void AddWindow::setValue(TYPE *obj, QComboBox *objSpec)     //считывание значений окна
{
    obj->setModel(carModel->text());                        //занесение их в объект
    obj->setType(objSpec->currentText());
    obj->setCondition(carCondition->currentText());
    obj->setNumber(carNumber->text()+carSym->text()+carRegion->currentText());
    obj->setName(driverName->text());
    obj->setSurname(driverSurname->text());
    obj->setPatronymic(driverSecName->text());
}
