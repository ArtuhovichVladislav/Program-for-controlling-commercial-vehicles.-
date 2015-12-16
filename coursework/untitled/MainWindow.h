#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QDialog>
#include <QToolBar>
#include <QMenuBar>
#include <QComboBox>
#include <QLineEdit>
#include <QToolBar>
#include <QStatusBar>
#include <QMainWindow>
#include <QLabel>
#include <QCloseEvent>
#include <QStringList>
#include <QTextEdit>
#include "tree.cpp"
#include "Cars.h"
#include "AddWindow.h"
#include "EditCarWindow.h"
#include <QTableWidget>
#include <QGroupBox>
#include "UndoStack.h"

const int wasDeleted = 0;
const int wasAdd = 1;
const int wasEdit = 2;
class AddWindow;
class EditCarWindow;
class MainWindow: public QMainWindow   //главное окно
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent);        //конструктор

    Tree<Wagon> wagonTree;              //дерево фургонов
    Tree<Refrigerator> refrigTree;      //дерево рефрижераторов
    Tree<Tipper> tipperTree;            //дерево самосвалов
    Tree<OilCar> oilTree;               //дерево цистерн

    QStringList *wagonsForDel;          //списки авто
    QStringList *refrigForDel;          //для удаления
    QStringList *tippersForDel;         //перед
    QStringList *oilCarsForDel;         //сохранением

    undoStack undoDelWag;               //стеки
    undoStack undoDelRefrig;            //отмены
    undoStack undoDelTipper;            //последних
    undoStack undoDelOil;               //действий
protected:
   void closeEvent(QCloseEvent *event);                 //обработка закрытия окна
   void contextMenuEvent(QContextMenuEvent *event);     //ПКМ
   void resizeEvent(QResizeEvent *event);               //перерисовка таблицы

private:
    AddWindow *edw;                                     //указатель окна добавления
    EditCarWindow *carEditWind;                         //указатель окна редактирования
    void createMenus();                                 //создание меню
    void createActions();                               //создание кнопок
    void createToolBar();                               //тулбар
    bool okToContinue();                                //вопрос для продолженяи работы
    void createTables();                                //создание таблиц
    void createMainLay();                               //главный слой

    template <class TYPE>
    void createCarTable(QTableWidget *table);           //шаблон создания таблиц
    void createRefrigTable();                           //таблица рефрижератора

    template <class TYPE>
    Tree<TYPE> readCarFile(QString filename, Tree<TYPE> tree);    //чтение файла

    template <class TYPE>
    bool writeCarToFile(QString filename, Tree<TYPE> tree);        //запись в файл

    template <class TYPE>
    void addCarToTable(int curRow, TYPE obj, QTableWidget *table);  //добавление в таблицу

    template <class TYPE>
    void showCar(QTableWidget *table, Tree<TYPE> tree);             //обновление таблицы

    template <class TYPE>
    void searchCar(QTableWidget *table);                            //поиск авто

    template <class TYPE>
    undoStack hideCar(QStringList *list, Tree<TYPE> tree,           //скрытие авто
                      QTableWidget *table, int curRow,
                      undoStack stack);

    template <class TYPE>
    Tree<TYPE> undoEditing(QString data, Tree<TYPE> tree);          //отмена редактирования

    template <class TYPE>
    Tree<TYPE> undoActionsTemplate(undoStack *stack,                //шаблон отмены
                                   Tree<TYPE> tree,
                                   QStringList *list);

    template <class TYPE>
    Tree<TYPE> deleteByList(QStringList *list, Tree<TYPE> tree);    //удаление перед сохранением

    template <class TYPE>
    void editCar(int curRow, QTableWidget *table, undoStack *stack, //редактирование
                 QStringList *list);

    template <class TYPE>
    void conditionFilter(QTableWidget *table);                      //фильтр

    void clearListAndStack(QStringList *list, undoStack *stack);

    bool saveFile(QString fileName, QString fileName1,              //сохранение
                  QString fileName2 ,QString fileName3);

    Wagon wagon;                 //объекты
    Refrigerator refrig;         //различных классов
    Tipper tipper;               //авто
    OilCar oilCar;

    QTableWidget *wagonTable;    //таблицы авто
    QTableWidget *refrigTable;
    QTableWidget *tipperTable;
    QTableWidget *oilCarTable;

    QString wagonFile;          //названия файлов
    QString refrigFile;
    QString tipperFile;
    QString oilCarFile;

    QGroupBox *wagonBox;        //блоки для создания слоя
    QGroupBox *refrigBox;
    QGroupBox *tipperBox;
    QGroupBox *oilCarBox;

    QMenu *file;                //меню главного окна
    QMenu *edit;
    QMenu *tools;
    QMenu *help;

    QToolBar *fileToolBar;      //тулбары
    QToolBar *editToolBar;
    QToolBar *showToolBar;
    QToolBar *condToolBar;
    QToolBar *searchToolBar;

    QComboBox *showBox;         //список типов
    QComboBox *condBox;         //список состояний

    QAction *saveAct;           //действие сохранения
    QAction *exitAct;           //...выход

    QAction *undo;              //...отмена

    QAction *addAct;            //...добавление
    QAction *editAct;           //...редактирование
    QAction *deleteAct;         //...удаление

    QAction *helpAct;           //...справка
    QAction *aboutAct;          //...о программе

    QLineEdit *searchArea;      //строка поиска

    int tableActive;            //текущая таблица
signals:
    void stackChanged();        //сигнал изменения стека
private slots:
    void searchCar();           //поиск
    void showTable();           //показ таблицы
    void refresh();             //обновдение таблиц

    void showCondFilter();      //выбор фильтра
    void deleteCar();           //удалить
    void editCarInfo();         //редактировать

    void add();                 //добавить
    bool save();                //сохранить
    void about();               //о программе
    void somethingChanged();    //изменения в программе

    void deleteCarBeforeSaving(); //удаление скрытых авто
    void undoAction();              //отмена
    void setUndoEnabled();          //включение кнопки отмена
public slots:
    void wagonActive();             //активная таблица
    void refrigActive();
    void tipperActive();
    void oilCarActive();
};

#endif // MAINWINDOW_H
