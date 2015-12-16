#ifndef EDITCARWINDOW_H
#define EDITCARWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include "Cars.h"
#include "MainWindow.h"
#include "tree.cpp"

class MainWindow;

class EditCarWindow: public QDialog
{
    Q_OBJECT
public:
    EditCarWindow(MainWindow *mW,       //конструктор с параметрами
                  QWidget *parent,
                  QString model);
private:
    MainWindow *mw;                     //указаетль на главное окно

    Wagon *wagon;
    Tipper *tipper;                     //объекты авто
    OilCar *oilCar;
    Refrigerator *refrig;
    QString carModel;

    QComboBox *carType;                 //выплывающие списки
    QComboBox *carCondition;
    QLineEdit *number;
    QLineEdit *driverSurname;
    QLineEdit *driverName;
    QLineEdit *driverPatronymic;

    QPushButton *edit;
    QPushButton *cancel;

    template <class TYPE>
    void setValue(TYPE *obj,            //установка новых значение
                  QComboBox *cond,
                  QLineEdit *num,
                  QLineEdit *name,
                  QLineEdit *sur,
                  QLineEdit *patr);

    template <class TYPE>
    void insertValue(TYPE *obj,          //вставка старых значений
                     QString typeOfCar,
                     QComboBox *type,
                     QComboBox *cond,
                     QLineEdit *num,
                     QLineEdit *name,
                     QLineEdit *sur,
                     QLineEdit *patr);
private slots:
    void editClicked();                 //нажата кнопка Изменить
    void cancelClicked();               //нажата кнопка Отмена
    void setEditEnabled();              //включить кнопку Изменить
signals:
    void closed();
};
#endif // EDITCARWINDOW_H
