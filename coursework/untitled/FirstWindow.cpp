#ifndef FIRSTWINDOW_CPP
#define FIRSTWINDOW_CPP

#include "FirstWindow.h"
#include <QVBoxLayout>
#include "MainWindow.h"

FirstWindow::FirstWindow(QWidget *parent):QDialog(parent)
{
    about = new QPushButton("О программе");         //кнопка О программе
    about->setFixedSize(150, 50);                   //размер

    startFile = new QPushButton("Запустить");       //кнопка Запустить
    startFile->setFixedSize(150, 50);               //размер

    exit = new QPushButton("Выход");                //кнопка Выход
    exit->setFixedSize(150, 50);

    QVBoxLayout *lay = new QVBoxLayout;

    lay->addWidget(startFile);                      //добавляем кнопки на слой
    lay->addWidget(about);
    lay->addWidget(exit);

    connect(about, SIGNAL(clicked()), this, SLOT(aboutClicked())); //о программе
    connect(startFile, SIGNAL(clicked()), this, SLOT(startClicked()));//запустить
    connect(exit,SIGNAL(clicked()), this, SLOT(close()));              //закрыть
    setLayout(lay);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Автопарк");
    setWindowIcon(QIcon(":/Icons/icons/Delivery.png"));
}

void FirstWindow::aboutClicked()
{
    QMessageBox::about(this, tr("О программе"),
                   tr("<h1><center><b>Автопарк 1.0</b></center></h1>"
                      "<p><h3><center>Программа учёта наличия грузовых транспортных средств в автопарке</center></h3>"
                      "<p><h3><center>Курсовая работа Артховича Владислава</center></h3>"
                      "<p><h3><center>БГУИР, группа 350505</center></h3>"
                      "<p>Copyright &copy; 2014 ArtVlad Inc."));
}

void FirstWindow::startClicked()
{
    this->close();
    MainWindow *main = new MainWindow(0); //создаём главное окно
    main->resize(700,550);
    main->show();
}

#endif // FIRSTWINDOW_CPP
