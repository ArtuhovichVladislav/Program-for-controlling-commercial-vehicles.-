#include "mainwindow.h"
#include <QApplication>
#include "FirstWindow.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile styleF(":/style/Dark.qss");               //считываем файл стиля
    styleF.open(QFile::ReadOnly);                   //в режиме для чтения
    QString qssStr = QLatin1String(styleF.readAll());//одной строкой

    FirstWindow *window = new FirstWindow(0);       //создаём начальное окно
    window->setFixedWidth(170);
    qApp->setStyleSheet(qssStr);                    //устанавливаем стиль
    window->show();

    return a.exec();                                //обработка исключений
}
