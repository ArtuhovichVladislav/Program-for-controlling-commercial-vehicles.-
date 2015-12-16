#ifndef ADDWINDOW_H
#define ADDWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include "Cars.h"
#include "MainWindow.h"
#include "tree.cpp"
#include "UndoStack.h"

class MainWindow;
class AddWindow: public QDialog      //класс окна добавления
{
    Q_OBJECT
public:
    AddWindow(MainWindow *mW, QWidget *parent); //конструктор
                                                //с параметрами
private:
    template <class TYPE>                        //шаблон. метод
    void setValue(TYPE *obj, QComboBox *spec);  //установки значения объекту
    template <class TYPE>                       //шаблон. метод
    void undoAdd(TYPE obj, int tab);            //отмены добавления
    MainWindow *mw;                             //указатель на Главное окно

    Wagon wagon;                                //объект Фургон
    Tipper tipper;                              //объект Самосвал
    OilCar oilCar;                              //объект Цистерна
    Refrigerator refrig;                        //объект Рефрижератор

    QLabel *wagonLbl;                           //Текст в окне
    QLabel *refrigLbl;
    QLabel *tipperLbl;
    QLabel *oilLbl;

    QComboBox *wagonSpec;                       //Выплывающие
    QComboBox *refrigSpec;                      //списки
    QComboBox *tipperSpec;                      //типов
    QComboBox *oilSpec;                         //авто

    QLineEdit *carModel;                        //поле ввода марки
    QComboBox *carType;                         //выплывающий список типа
    QComboBox *carCondition;                    //...состояний
    QLineEdit *carNumber;                       //поле номера
    QLineEdit *carSym;                          //поле символов номера
    QComboBox *carRegion;                       //поле регионов номера
    QLineEdit *driverSurname;                   //поле фамилии
    QLineEdit *driverName;                      //поле имени
    QLineEdit *driverSecName;                   //поле отчества

    QPushButton *ok;                            //кнопка ОК
    QPushButton *cancel;                        //кнопка Отмена

signals:
    void stackChanged();                        //сигнал изменения стека
private slots:
    void okClicked();                           //обработка нажатия ок
    void cancelClicked();                       //...отмена
    void cbChanged();                           //обработка выбора из списка
    void setOkEnabled();                        //вкл/откл ок
signals:
    void closed();                              //сигнал закрытия окна
};


#endif // AddWindow_H
