#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QWidget>
#include <QMessageBox>


class FirstWindow: public QDialog  //первое окно
{
    Q_OBJECT
public:
    FirstWindow(QWidget *parent);  //конструткор
private:
    QPushButton *about;             //кнопка Оп программе
    QPushButton *startFile;         //кнопка Запуска
    QPushButton *exit;              //кнопка Выхода
private slots:
    void aboutClicked();            //обработка кнопок
    void startClicked();
};

#endif // FIRSTWINDOW_H
