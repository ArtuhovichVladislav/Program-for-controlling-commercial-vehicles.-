#include "MainWindow.h"
//#include "AddWindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QVBoxLayout>
#include <QStringList>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    wagonFile = "Фургоны.apt";
    refrigFile = "Рефрижераторы.apt";                     //открываем файлы
    tipperFile = "Самосвалы.apt";
    oilCarFile = "Цистерны.apt";

    wagonTree = readCarFile<Wagon>(wagonFile,
                                   wagonTree);           //считываем файлы
    refrigTree = readCarFile<Refrigerator>(refrigFile,
                                           refrigTree);
    tipperTree = readCarFile<Tipper>(tipperFile,
                                     tipperTree);
    oilTree = readCarFile<OilCar>(oilCarFile,
                                  oilTree);

    wagonTable = new QTableWidget;
    tipperTable = new QTableWidget;                       //создаём таблицы
    oilCarTable = new QTableWidget;

    createMainLay();                                      //создание кгавного слоя
    createActions();                                      //создание действий кнопок
    createMenus();                                        //создание меню
    createToolBar();                                      //...тулбара

    showCar<Wagon>(wagonTable, wagonTree);                //выводим талицы
    showCar<Refrigerator>(refrigTable, refrigTree);        //авто
    showCar<Tipper>(tipperTable, tipperTree);
    showCar<OilCar>(oilCarTable, oilTree);

    connect(wagonTable, SIGNAL(clicked(QModelIndex)),
            this, SLOT(wagonActive()));                   //определяем
    connect(refrigTable, SIGNAL(clicked(QModelIndex)),     //какая
            this, SLOT(refrigActive()));
    connect(tipperTable, SIGNAL(clicked(QModelIndex)),    //таблица
            this, SLOT(tipperActive()));
    connect(oilCarTable, SIGNAL(clicked(QModelIndex)),    //активна
            this, SLOT(oilCarActive()));

    wagonsForDel = new QStringList;                     //создаём
    refrigForDel = new QStringList;                     //списки
    tippersForDel = new QStringList;
    oilCarsForDel = new QStringList;

    setWindowTitle("Автопарк 1.0");                     //название окна
    setWindowIcon(QIcon(":/Icons/icons/Delivery.png")); //иконка
}

void MainWindow::createActions()
{
    saveAct = new QAction(tr("&Сохранить"),this);                 //пункт сохранения
    saveAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));     //горячие клавиши
    saveAct->setIcon(QIcon(":/Icons/icons/Save.png"));            //иконка
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));    //действие по нажатии

    exitAct = new QAction(tr("&Выход"),  this);                   //пункт выхода
    exitAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));     //горячие клавиши
    exitAct->setIcon(QIcon(":/Icons/icons/Exit.png"));            //иконка
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));   //действие по нажатии

    undo = new QAction(tr("&Отмена"),  this);                      //пункт отмены
    undo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));          //горячие клавиши
    undo->setIcon(QIcon(":/Icons/icons/Undo.png"));                 //иконка
    undo->setEnabled(false);                                        //отключаем отмену
    connect(this, SIGNAL(stackChanged()), this,
            SLOT(setUndoEnabled()));                     //включаем,если стек не пуст
    connect(undo, SIGNAL(triggered()), this, SLOT(undoAction())); //запуск отмены

    addAct = new QAction(tr("&Добавить"),  this);                   //пункт добавить
    addAct->setIcon(QIcon(":/Icons/icons/Add.png"));                //иконка
    addAct->setShortcut(QKeySequence(Qt::Key_Plus));                //горячие клавиши
    connect(addAct, SIGNAL(triggered()), this, SLOT(add()));        //действие по нажатии

    deleteAct = new QAction(tr("Удалить элемент"), this);            //пункт добавить
    deleteAct->setShortcut(QKeySequence::Delete);                     //горячие клавиши
    deleteAct->setIcon(QIcon(":/Icons/icons/Delete.png"));            //иконка
    connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteCar())); //действие по нажатии

    editAct = new QAction(tr("&Изменить"),  this);                      //пункт изменить
    editAct->setIcon(QIcon(":/Icons/icons/Modify.png"));                //иконка
    connect(editAct, SIGNAL(triggered()), this, SLOT(editCarInfo()));   //действие по нажатии


    aboutAct = new QAction(tr("&О программе"),  this);              //о программе
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));    //вывод о программе
}

void MainWindow::createMenus()
{
    file = menuBar()->addMenu(tr("&Файл"));      //создаём меню файл
    file->addAction(saveAct);                   //добавляем действия
    file->addSeparator();
    file->addAction(exitAct);

    edit=menuBar()->addMenu(tr("Правка"));
    edit->addAction(undo);                           //Правка

    tools = menuBar()->addMenu(tr("Инструменты"));  //Инструменты
    tools->addAction(addAct);
    tools->addAction(deleteAct);
    tools->addAction(editAct);
    tools->addSeparator();

    help = menuBar()->addMenu(tr("Помощь"));
    help->addAction(aboutAct);
}

void MainWindow::createToolBar()
{
    fileToolBar = addToolBar(tr("&File"));          //создаём тулбар
    fileToolBar->addAction(saveAct);                //добавляем кнопку
    fileToolBar->setMovable(false);                 //неподвижный

    editToolBar = addToolBar(tr("&Tools"));         //создаём тулбар
    editToolBar->addAction(addAct);                 //добавялем кнопки
    editToolBar->addAction(editAct);
    editToolBar->addAction(deleteAct);
    editToolBar->setMovable(false);                 //неподвижный

    showBox = new QComboBox;                        //список типов авто
    showBox->addItem("Фургоны");
    showBox->addItem("Рефрижераторы");
    showBox->addItem("Самосвалы");
    showBox->addItem("Цистерны");
    showBox->addItem("Все");
    int index = showBox->findText("Все");
    showBox->setCurrentIndex(index);
    showToolBar=addToolBar(tr("Show"));             //добавляем в тулбар
    showToolBar->addWidget(showBox);
    showToolBar->setMovable(false);

    condBox = new QComboBox;                        //список состояний авто
    condBox->addItem("Все");
    condBox->addItem("Свободен");
    condBox->addItem("В рейсе");
    condBox->addItem("На ремонте");
    condBox->addItem("Списан");
    condToolBar = addToolBar(tr("Condition"));       //создаём тулбар
    condToolBar->addWidget(condBox);                //добавляем в тулбар
    condToolBar->setMovable(false);                 //неподвижный

    searchArea = new QLineEdit;                     //строка поиска
    searchArea->setMaximumWidth(150);
    searchArea->setMinimumWidth(150);

    searchToolBar = addToolBar(tr("Search"));       //создаём тулбар
    searchToolBar->addWidget(searchArea);           //добавляем в тулбар
    searchToolBar->setMovable(false);

    connect(searchArea, SIGNAL(textChanged(QString)),
            this, SLOT(searchCar()));                  //поиск
    connect(showBox, SIGNAL(currentTextChanged(QString)),
            this, SLOT(showTable()));                 //показ таблицы
    connect(condBox, SIGNAL(currentTextChanged(QString)),
            this, SLOT(showCondFilter()));             //вывод по фильтру
}

bool MainWindow::okToContinue()
{
    if(isWindowModified())                                   //если ч-н изменено
    {
        int r = QMessageBox:: warning(this, tr("Автопарк"),  //запрос на сохранение
                    tr("Документ был изменён.\n"
                       "Вы хотите сохранить изменения?"),
                    QMessageBox::Yes | QMessageBox:: No|
                    QMessageBox::Cancel);
        if(r == QMessageBox::Yes)                           //если да
        {
            return save();                                  //сохранить
        }
        else if(r == QMessageBox::Cancel)                   //отмена
        {
            return false;
        }
    }
    return true;
}

template <class TYPE>
void MainWindow::createCarTable(QTableWidget *table)
{
    table->setSelectionMode(QAbstractItemView::SingleSelection);   //выбор одной строки
    table->setSelectionBehavior(QAbstractItemView::SelectRows);    //выбор целой строки
    table->setEditTriggers(QAbstractItemView:: NoEditTriggers);    //запрет редактирования
                                                                   //в таблице
    table->setSortingEnabled(true);                                //включение сортировки
    table->sortByColumn(0, Qt::AscendingOrder);                    //по столбцам

    QStringList headers;
    headers << "Марка" << "Номер" << "Тип" << "Состояние"
            << "ФИО водителя";                                     //названия столбцов

    table->setRowCount(0);                                          //нач. количество срок
    table->setColumnCount(5);                                       //столбцов
    table->setHorizontalHeaderLabels(headers);                      //установка названий столбцов
    table->horizontalHeader()->setStretchLastSection(true);         //расятгивать послед. ст-ц
    table->horizontalHeader()->setSortIndicatorShown(true);         //индикатор сортировки

    table->setCurrentCell(0, 0);
}

void MainWindow::createRefrigTable()                               //аналогично созд. таблицу
{                                                                   //рефрижераторов
    refrigTable = new QTableWidget;
    refrigTable->setSelectionMode(QAbstractItemView::SingleSelection);
    refrigTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    refrigTable->setEditTriggers(QAbstractItemView:: NoEditTriggers);
    refrigTable->setSortingEnabled(true);
    refrigTable->sortByColumn(1, Qt::AscendingOrder);

    QStringList headers;
    headers << "Марка" << "Номер" << "Температура" << "Состояние" << "ФИО водителя";
    refrigTable->setRowCount(0);
    refrigTable->setColumnCount(5);
    refrigTable->setHorizontalHeaderLabels(headers);
    refrigTable->horizontalHeader()->setStretchLastSection(true);

    refrigTable->setCurrentCell(0, 0);
}

void MainWindow::createTables()             //вызываем создание таблицы
{                                           //каждого типа
    createCarTable<Wagon>(wagonTable);
    createRefrigTable();
    createCarTable<Tipper>(tipperTable);
    createCarTable<OilCar>(oilCarTable);
}

void MainWindow::createMainLay()
{
    createTables();                             //создаём таблицы

    QVBoxLayout *wagonLay = new QVBoxLayout;        //слой с таблицей
    wagonLay->addWidget(wagonTable);                //фургонов
    wagonBox = new QGroupBox(tr("Фургоны"));
    wagonBox->setLayout(wagonLay);

    QVBoxLayout *refrigLay = new QVBoxLayout;        //слой с таблицей
    refrigLay->addWidget(refrigTable);
    refrigBox = new QGroupBox(tr("Рефрижераторы"));  //рефрижераторов
    refrigBox->setLayout(refrigLay);

    QVBoxLayout *tipperLay = new QVBoxLayout;       //слой с таблицей
    tipperLay->addWidget(tipperTable);
    tipperBox = new QGroupBox("Самосвалы");         //самосвалов
    tipperBox->setLayout(tipperLay);

    QVBoxLayout *oilCarLay = new QVBoxLayout;       //слой с таблицей
    oilCarLay->addWidget(oilCarTable);
    oilCarBox = new QGroupBox("Цистерны");          //цистерн
    oilCarBox->setLayout(oilCarLay);

    QVBoxLayout *mainLay = new QVBoxLayout;         //создаём глаынй слой
    mainLay->addWidget(wagonBox);
    mainLay->addWidget(refrigBox);
    mainLay->addWidget(tipperBox);
    mainLay->addWidget(oilCarBox);

    QWidget *wind = new QWidget;
    wind->setLayout(mainLay);                       //устанавливаем его

    setCentralWidget(wind);
}

bool MainWindow::save()
{
    deleteCarBeforeSaving();                      //удаляем ненужные авто
    if(saveFile(wagonFile,refrigFile,             //если успешно сохранено
                tipperFile,oilCarFile))
    {
        setWindowModified(false);                 //окно без изменений
        return true;
    }
    else
        return false;
}

bool MainWindow::saveFile(QString fileName, QString fileName1,
                          QString fileName2, QString fileName3)
{
    if(!writeCarToFile<Wagon>(fileName, wagonTree)              //проверка записи в файлы
        ||!writeCarToFile<Refrigerator>(fileName1, refrigTree)  //если не записалось
        ||!writeCarToFile<Tipper>(fileName2, tipperTree)
        ||!writeCarToFile<OilCar>(fileName3, oilTree))
    {
        statusBar()->showMessage(tr("Не удалось выполнить сохранение"), 2000);
        return false;
    }
    statusBar()->showMessage(tr("Сохранено"), 2000);
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)     //обработка закрытия окна
{
    if(okToContinue())
    {
        event->accept();
    }
    else
        event->ignore();
}

void MainWindow::about()        //о программе
{
    QMessageBox::about(this, tr("О программе"),
tr("<h1><center><b>Автопарк 1.0</b></center></h1>"
  "<p><h3><center>Программа учёта наличия грузовых транспортных средств в автопарке</center></h3>"
  "<p><h3><center>Курсовая работа Артховича Владислава</center></h3>"
  "<p><h3><center>БГУИР, группа 350505</center></h3>"
  "<p>Copyright &copy; 2014 ArtVlad Inc."));
}

void MainWindow::add()              //добавление
{
    edw = new AddWindow(this, this);
    edw->show();                            //открываем окно добавления
    connect(edw, SIGNAL(closed()), this,    //обновляем таблицы
            SLOT(refresh()));
    connect(edw, SIGNAL(closed()), this,    //проверяем стек
            SLOT(setUndoEnabled()));        //если есть что, отмена вкл
    somethingChanged();
}

void MainWindow::showTable()
{
    if(showBox->currentText()=="Фургоны")
    {
        showCar<Wagon>(wagonTable, wagonTree); //показываем только
        wagonBox->show();                       //таблицу фургонов
        wagonTable->setEnabled(true);           //остальные скрываем
        refrigTable->setEnabled(false);
        tipperTable->setEnabled(false);
        oilCarTable->setEnabled(false);
        refrigBox->hide();
        tipperBox->hide();
        oilCarBox->hide();
    }
    if(showBox->currentText()=="Рефрижераторы")
    {
        showCar<Refrigerator>(refrigTable,     //показываем только
                              refrigTree);
        refrigBox->show();                     //таблицу рефрижераторов
        refrigTable->setEnabled(true);         //остальные скрываем
        wagonTable->setEnabled(false);
        tipperTable->setEnabled(false);
        oilCarTable->setEnabled(false);
        wagonBox->hide();
        tipperBox->hide();
        oilCarBox->hide();
    }
    if(showBox->currentText()=="Самосвалы")
    {
        showCar<Tipper>(tipperTable, tipperTree); //...самосвалов
        tipperBox->show();
        tipperTable->setEnabled(true);
        refrigTable->setEnabled(false);
        wagonTable->setEnabled(false);
        oilCarTable->setEnabled(false);
        refrigBox->hide();
        wagonBox->hide();
        oilCarBox->hide();
    }
    if(showBox->currentText()=="Цистерны")
    {
        showCar<OilCar>(oilCarTable, oilTree); //...цистерн
        oilCarBox->show();
        oilCarTable->setEnabled(true);
        tipperTable->setEnabled(false);
        refrigTable->setEnabled(false);
        wagonTable->setEnabled(false);
        refrigBox->hide();
        tipperBox->hide();
        wagonBox->hide();
    }
    if(showBox->currentText()=="Все")
    {
        wagonBox->show();                       //выводим все таблицы
        refrigBox->show();
        tipperBox->show();
        oilCarBox->show();
        oilCarTable->setEnabled(true);
        tipperTable->setEnabled(true);
        refrigTable->setEnabled(true);
        wagonTable->setEnabled(true);
        showCar<Wagon>(wagonTable, wagonTree);
        showCar<Refrigerator>(refrigTable, refrigTree);
        showCar<Tipper>(tipperTable, tipperTree);
        showCar<OilCar>(oilCarTable, oilTree);
    }
}

void MainWindow:: refresh()
{                                                   //обновляем все таблицы
    showCar<Wagon>(wagonTable, wagonTree);
    showCar<Refrigerator>(refrigTable, refrigTree);
    showCar<Tipper>(tipperTable, tipperTree);
    showCar<OilCar>(oilCarTable, oilTree);
}

template <class TYPE>
void MainWindow:: addCarToTable(int curRow, TYPE obj, QTableWidget *table)
{
    QTableWidgetItem *item = new QTableWidgetItem;  //объект для таблицы
    item->setText(obj.getModel());                  //получам модель
    table->setItem(curRow,0,item);                  //вставляем в 1 столбец

    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setText(obj.getNumber());                //номер
    table->setItem(curRow,1,item1);                 //во второй

    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(obj.getType());                  //вид
    table->setItem(curRow,2,item2);                 //в третий

    QTableWidgetItem *item3 = new QTableWidgetItem;
    item3->setText(obj.getCondition());             //состояние
    table->setItem(curRow,3,item3);                 //в четвёртый

    QTableWidgetItem *item4 = new QTableWidgetItem;
    item4->setText(obj.getFIO());                   //ФИО
    table->setItem(curRow,4,item4);                 //в пятый
}

template <class TYPE>
void MainWindow::showCar(QTableWidget *table, Tree<TYPE> tree)
{
    if(tree.emptyTree())                            //проверка дерева на пустоту
    {
        table->setRowCount(0);                      //пустое - обнуление кол-ва строк
    }                                               //таблицы
    else
    {
        int currentRow = 0;
        table->setRowCount(0);

        Tree<TYPE>::iterator iter = tree.begin();    //итератор
        if(tree.size() == 1 &&                      //1 элемент в дереве и не скрыт
                tree.getRoot()->hidden == false)
        {
           table->setRowCount(currentRow +1);       //увеличиваем кол-во строк в таблице
           addCarToTable(currentRow, *iter, table); //добавляем в таблицу
        }
        else
        {
            while(iter != tree.end())               //пока не конец дерева
            {
               if (iter.getNodeptr()->hidden == false) //если не скрыт
               {
                    table->setRowCount(currentRow+1); //увеличиваем кол-во строк в таблице
                    addCarToTable(currentRow, *iter,  //добавляем в таблицу
                                  table);
                    ++iter;                           //увеличиваем итератор
                    currentRow++;                     //и кол-во строк

                    if(iter == tree.end() &&            //дошли до конца
                       iter.getNodeptr()->hidden == false)//не скрыт
                    {
                        table->setRowCount(currentRow+1); //увеличиваем кол-во строк
                        addCarToTable(currentRow, *iter, table);//добавляем в таблицу
                    }
                    else continue;
               }
               else
               {   ++iter;                              //увеличиваем итератор
                   if(iter == tree.end() &&             //конец
                           iter.getNodeptr()->hidden == false)//не скрыт
                   {
                       table->setRowCount(currentRow+1);      //увеличиваем кол-во строк
                       addCarToTable(currentRow, *iter, table);//добавляем в таблицу
                   }
               }
            }
        }
    }
}

template <class TYPE>
undoStack MainWindow::hideCar(QStringList *list, Tree<TYPE> tree,
                              QTableWidget *table, int curRow,
                              undoStack stack)
{
    undoStack *action;                                //стек отмены
    QString model = table->item(curRow, 0)->text();   //текущая модель
    action = new undoStack(wasDeleted, model);
    stack.push(action);                               //добавляем в стек
    list->push_back(model);
    tree.setNodeHidden(model);                        //скрываем в дереве
    showCar<TYPE>(table, tree);                       //обновляем таблицу
    somethingChanged();                               //фиксируем изменения
    return stack;
}

void MainWindow::deleteCar()
{
    int currentRow = wagonTable->currentRow();        //получаем активные
    int currentRow1 = refrigTable->currentRow();      //строки
    int currentRow2 = tipperTable->currentRow();      //таблиц
    int currentRow3 = oilCarTable->currentRow();

    if((currentRow >= 0) &&                                 //проверка
            (currentRow <= wagonTable->rowCount())          //активности таблицы
            && wagonTable->isEnabled() && tableActive == 1)
    {
       undoDelWag = hideCar<Wagon>(wagonsForDel, wagonTree,  //заносим в стек
                                   wagonTable, currentRow,
                                   undoDelWag);
       emit stackChanged();
    }
    else if((currentRow1 >= 0) &&
            (currentRow1 <= refrigTable->rowCount())
            && refrigTable->isEnabled()&& tableActive == 2)
    {
        undoDelRefrig = hideCar<Refrigerator>(refrigForDel, //заносим в стек
                                              refrigTree,
                                              refrigTable,
                                              currentRow1,
                                              undoDelRefrig);
        emit stackChanged();
    }
    else if((currentRow2 >= 0) &&                           //проверка
            (currentRow2 <= tipperTable->rowCount())        //активности таблицы
            && tipperTable->isEnabled()&& tableActive == 3)
    {
        undoDelTipper = hideCar<Tipper>(tippersForDel,      //заносим в стек
                                        tipperTree,
                                        tipperTable,
                                        currentRow2,
                                        undoDelTipper);
        emit stackChanged();
    }
    else if((currentRow3 >= 0) &&                           //проверка
            (currentRow3 <= oilCarTable->rowCount())        //активности таблицы
            && oilCarTable->isEnabled()&& tableActive == 4)
    {
        undoDelOil = hideCar<OilCar>(oilCarsForDel,
                                     oilTree, oilCarTable,   //заносим в стек
                                     currentRow3, undoDelOil);
        emit stackChanged();
    }
    else
    {                                                       //иначе окно ошибки
        QMessageBox::information(this, tr("Ошибка"),
                     tr("Выберите элемент для удаления"));
    }
}

template <class TYPE>
Tree<TYPE> MainWindow::deleteByList(QStringList *list, Tree<TYPE> tree)
{
    QStringList::iterator iter = list->begin(); //итератор списка удаляемых
    if(!list->empty())
        for(iter = list->begin(); iter!=list->end(); ++iter)
        {
            QString current = *iter;            //текущий = удаляемый
            tree.deleteNode(current);           //удаляем
        }
    return tree;
}

void MainWindow::deleteCarBeforeSaving()    //удаление из всех деревьев
{
    wagonTree = deleteByList<Wagon>(wagonsForDel, wagonTree);
    refrigTree = deleteByList<Refrigerator>(refrigForDel, refrigTree);
    tipperTree = deleteByList<Tipper>(tippersForDel, tipperTree);
    oilTree = deleteByList<OilCar>(oilCarsForDel, oilTree);
    clearListAndStack(wagonsForDel, &undoDelWag);
    clearListAndStack(refrigForDel, &undoDelRefrig);
    clearListAndStack(tippersForDel, &undoDelTipper);
    clearListAndStack(oilCarsForDel, &undoDelOil);
    emit stackChanged();
}


void MainWindow::clearListAndStack(QStringList *list, undoStack *stack)
{
    while(!list->empty())
        list->pop_back();
    while(!stack->isEmpty())
        stack->pop();
}

template <class TYPE>
Tree<TYPE> MainWindow::undoActionsTemplate(undoStack *stack,
                                           Tree<TYPE> tree,
                                           QStringList *list)
{
    if(!stack->isEmpty())
    {
     undoStack *Action = stack->pop();          //извлекаем из стека
     int ActionCode = Action->getActionCode();  //код отмены
     switch(ActionCode)
     {
     case wasDeleted:                           //удаление
         list->pop_back();                      //извлекаем из списка
         tree.unsetNodeHidden(Action->getData());//снимаем скрытие
         break;
     case wasAdd:                               //добавление
         list->push_back(Action->getData());     //добавляем в список
         tree.setNodeHidden(Action->getData()); //скрываем
         break;
     case wasEdit:                              //редактирование
         list->pop_back();                      //извлекаем из списка
         tree = undoEditing(Action->getData(),  //отменяем
                            tree);
         break;
     }
     delete Action;
    }
    else
    {
        undo->setEnabled(false);                //отключаем кнопку отмены
    }
    return tree;
}


void MainWindow::undoAction()
{
    if(tableActive == 1)
    {
        wagonTree = undoActionsTemplate<Wagon>      //отмена для таблицы фургонов
                (&undoDelWag, wagonTree, wagonsForDel);
        showCar<Wagon>(wagonTable, wagonTree);
        emit stackChanged();
    }
    else if(tableActive == 2)
    {
        refrigTree = undoActionsTemplate<Refrigerator>//отмена для таблицы рефриж.
                (&undoDelRefrig, refrigTree, refrigForDel);
        showCar<Refrigerator>(refrigTable, refrigTree);
        emit stackChanged();
    }
    else if(tableActive == 3)
    {
        tipperTree = undoActionsTemplate<Tipper>    //отмена для таблицы самосвалов
                (&undoDelTipper, tipperTree, tippersForDel);
        showCar<Tipper>(tipperTable, tipperTree);
        emit stackChanged();
    }
    else if(tableActive == 4)
    {
        oilTree = undoActionsTemplate<OilCar>       //отмена для таблицы цистерн
                (&undoDelOil, oilTree, oilCarsForDel);
        showCar<OilCar>(oilCarTable, oilTree);
        emit stackChanged();
    }
}

template <class TYPE>
Tree<TYPE> MainWindow::undoEditing(QString data, Tree<TYPE> tree)
{
    QString model;
    QString cond;
    QString number;
    QString name;
    QString sur;
    QString patr;
    TYPE obj;

    int i=0, j=0;
    for(i; data[i]!=' '; i++)
        model[i] = data[i];                     //выделяем модель

    for(i++, j = 0; data[i]!=' '; i++, j++)
        cond[j] = data[i];                      //выделяем состояние

    for(i++, j = 0; data[i] != ' '; i++, j++)
        number[j] = data[i];                    //выдедяем номер

    for(i++, j = 0; data[i] != ' '; i++, j++)
        sur[j] = data[i];                       //выделяем фамилию

    for(i++, j = 0; data[i] != ' '; i++, j++)
        name[j] = data[i];                      //выделяем имя
    for(i++, j = 0; data[i] != '\0'; i++, j++)
        patr[j] = data[i];                      //выделяем отчество

    obj = *tree.search(model);                  //ищем в дереве
    obj.setCondition(cond);                     //устанавоиваем значения
    obj.setNumber(number);
    obj.setName(name);
    obj.setSurname(sur);
    obj.setPatronymic(patr);

    return tree;
}

template <class TYPE>
void MainWindow::editCar(int curRow, QTableWidget *table,
                         undoStack *stack, QStringList *list)
{
    QString str = table->item(curRow, 0)->text();

 /*   undoStack *action;
    QString model = table->item(curRow, 0)->text();     //получаем значения
    QString number = table->item(curRow, 1)->text();    //из таблицы
    QString type = table->item(curRow, 2)->text();
    QString cond = table->item(curRow, 3)->text();
    QString driver = table->item(curRow, 4)->text();

    action = new undoStack(wasEdit, model +' '+number+' '+
                           type+' '+cond+ ' ' + driver);
    stack->push(action);                                //заносим в стек
    list->push_back(model);                             //и модель в список
*/
    carEditWind = new EditCarWindow(this,this,str);     //окно редактирования
    carEditWind->setWindowTitle("Изменение данных");
    carEditWind->show();
    somethingChanged();
    connect(carEditWind, SIGNAL(closed()), this, SLOT(refresh()));//обновляем
}


void MainWindow::editCarInfo()
{
    int currentRow = wagonTable->currentRow();           //получаем текущие строки таблиц
    int currentRow1 = refrigTable->currentRow();
    int currentRow2 = tipperTable->currentRow();
    int currentRow3 = oilCarTable->currentRow();
    if((currentRow >= 0) && (currentRow <= wagonTable->rowCount())  //активна таблица фургонов
            && wagonTable->isEnabled()&& tableActive == 1)
    {
        editCar<Wagon>(currentRow, wagonTable, &undoDelWag, wagonsForDel);//запуск редактирования
    }
    else if((currentRow1 >= 0) && (currentRow1 <= refrigTable->rowCount())  //активна таблица рефриж.
            && refrigTable->isEnabled()&& tableActive == 2)
    {
        editCar<Refrigerator>(currentRow1, refrigTable, &undoDelRefrig, //запуск редактирования
                              refrigForDel);
    }
    else if((currentRow2 >= 0) && (currentRow2 <= tipperTable->rowCount())//активна таблица самосвалов
            && tipperTable->isEnabled()&& tableActive == 3)
    {
        editCar<Tipper>(currentRow2, tipperTable, &undoDelTipper, tippersForDel);//запуск редактирования
    }
    else if((currentRow3 >= 0) && (currentRow3 <= oilCarTable->rowCount())//активна таблица цистерн
            && oilCarTable->isEnabled()&& tableActive == 4)
    {
        editCar<OilCar>(currentRow3, oilCarTable, &undoDelOil, oilCarsForDel);//запуск редактирования
    }
    else
    {
        QMessageBox::information(this, tr("Ошибка"), tr("Выберите элемент для редактирования"));
    }
}


void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);                   //создаём меню ПКМ
    menu.addAction(deleteAct);
    menu.addAction(editAct);
    menu.exec(event->globalPos());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    for(int i = 0; i<5;i++)
    {
        wagonTable->setColumnWidth(i, (this->width()/5)-20);   //пересчитываем ширину столбцов
        refrigTable->setColumnWidth(i, (this->width()/5)-20);
        tipperTable->setColumnWidth(i, (this->width()/5)-20);
        oilCarTable->setColumnWidth(i, (this->width()/5)-20);
    }
}

template <class TYPE>
void MainWindow::conditionFilter(QTableWidget *table)
{
    QString filter = condBox->currentText();            //фильтр = тек. состояние
    for(int i = 0; i < table->rowCount(); ++i)          //по всем строкам
    {
        QTableWidgetItem *item = table->item(i, 3);     //значение 3 столбца
        if(item->text().contains(filter))               //совпало с фильтром
            table->setRowHidden(i, false);              //выводим строку
        else                                            //иначе
            table->setRowHidden(i, true);               //скрываем
    }
    if(filter == "Все")                                 //если все
        for(int i = 0; i < table->rowCount(); ++i)
           table->setRowHidden(i, false);               //выводим все
}

void MainWindow:: showCondFilter()
{
    conditionFilter<Wagon>(wagonTable);                 //включаем фильтр
    conditionFilter<Refrigerator>(refrigTable);         //для всех таблиц
    conditionFilter<Tipper>(tipperTable);
    conditionFilter<OilCar>(oilCarTable);
}


void MainWindow::wagonActive()
{
    tableActive = 1;                                   //фургоны активны
}

void MainWindow::refrigActive()
{
    tableActive = 2;                                   //рефрижераторы активны
}
void MainWindow::tipperActive()
{
    tableActive = 3;                                   //самосвалы
}

void MainWindow::oilCarActive()
{
    tableActive = 4;                                   //цистерны
}

template <class TYPE>
Tree<TYPE> MainWindow::readCarFile(QString fileName, Tree<TYPE> tree)
{
    TYPE obj;
    QFile carFile(fileName);                    //создаём/открываем файл
    if(!carFile.open(QIODevice::ReadOnly))      //в режиме для чтения
    {
           QMessageBox::information(0, fileName, "Ошибка открытия файла");
           carFile.open(QIODevice::ReadWrite);
    }

    QDataStream in(&carFile);                   //поток
    while(!in.atEnd())
    {
        in>> obj;                               //записываем в объект
        if (obj.getModel() == "")               //пустая стркоа
            break;                              //прервать
        tree.createTree(obj);                   //добавляем в дерево
    }
    carFile.flush();
    carFile.close();                            //закрываем
    return tree;
}

template <class TYPE>
bool MainWindow::writeCarToFile(QString filename, Tree<TYPE> tree)
{
    QFile carFile(filename);                //создаём/открываем файл
    if(!carFile.open(QIODevice::WriteOnly)) //в режиме для записи
    {
       QMessageBox::warning(0, filename, //если не открылся - ошибка
                            tr("Невозможно прочитать файл %1:\n%2.")
                            .arg(carFile.fileName())
                            .arg(carFile.errorString()));
       return false;
     }

    QDataStream out(&carFile);              //поток
    Tree<TYPE>::iterator iter = tree.begin();//итератор дерева

    if(tree.size() == 0)                //если пустое дерево
    {
        carFile.close();
        carFile.open(QIODevice::WriteOnly); //стираем файл
    }
    if(tree.size() == 1)
        out << *iter;                       //записываем в файл
    else
        while(iter!=tree.end())             //пока не конец дерева
        {
            out << *iter;                   //записываем
            ++iter;
            if(iter == tree.end())
                out << *iter;               //записываем последний
        }
    carFile.flush();
    carFile.close();                        //закрываем
    return true;
}

template <class TYPE>
void MainWindow::searchCar(QTableWidget *table)
{
    QString carModel;
    int numberOfMatches = 0;
    int count = 0;
    bool searchModeEnabled;
    int i;
    if(searchArea->text()!=NULL)                //область поиска не пуста
    {
        searchModeEnabled = true;
        count++;
    }
    else
        searchModeEnabled = false;

    for(i=0; i < table->rowCount(); i++)        //по всем строкам
    {
        if(table->isRowHidden(i))
            table->setRowHidden(i, false);
    }

    for(i=0; i < table->rowCount(); i++)        //по всем строкам
    {
        carModel = table->item(i, 0)->text();   //1-й столбец

        if(carModel.contains(searchArea->text()) //если содержит
                && searchModeEnabled)
        {
            numberOfMatches++;                  //количество совпадений++
        }
        if(count!=numberOfMatches)              //не содержит
        {
            table->setRowHidden(i, true);       //скрываем строки
        }
        numberOfMatches = 0;
    }
}

void MainWindow::searchCar()
{                                               //поиск по всем таблицам
    searchCar<Wagon>(wagonTable);
    searchCar<Refrigerator>(refrigTable);
    searchCar<Tipper>(tipperTable);
    searchCar<OilCar>(oilCarTable);
}

void MainWindow::somethingChanged()
{
    setWindowModified(true);
}

void MainWindow:: setUndoEnabled()
{
    if(!undoDelWag.isEmpty() && tableActive == 1)           //если стек не пуст
        undo->setEnabled(true);                             //и таблица активна
    else if(!undoDelRefrig.isEmpty() && tableActive == 2)   //включаем кнопку отмены
        undo->setEnabled(true);
    else if(!undoDelTipper.isEmpty() && tableActive == 3)
        undo->setEnabled(true);
    else if(!undoDelOil.isEmpty() && tableActive == 4)
        undo->setEnabled(true);
    else                                                    //иначе
        undo->setEnabled(false);                            //отключаем
}
