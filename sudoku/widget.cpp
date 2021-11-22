#include "widget.h" // заголовочный файл класса главной формы
#include "ui_widget.h" // файл формы главного окна

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myNewSave = new DialogSave(); // создадим диалог сохранения
    myNewOpen = new DialogOpen(); // создадим диалог открытия

    // если не существует папки создадим её
    if(! QDir(QApplication::applicationDirPath()+"/data").exists())
    {
        // создаст папку рядом с файлом exe
        QDir().mkdir(QApplication::applicationDirPath()+"/data");
    }

    // привяжем кнопки к режимам игры
    connect(ui->btnSoEasy,SIGNAL(clicked()),this,SLOT(newGame_VeryEasy()));
    connect(ui->btnEasy,SIGNAL(clicked()),this,SLOT(newGame_Easy()));
    connect(ui->btnNormal,SIGNAL(clicked()),this,SLOT(newGame_Normal()));
    connect(ui->btnHard,SIGNAL(clicked()),this,SLOT(newGame_Hard()));
    connect(ui->btnSoHard,SIGNAL(clicked()),this,SLOT(newGame_VeryHard()));

    // привяжем строку формы сохранения к слоту сохранения главной формы
    connect(myNewSave, SIGNAL(sendData(QString)), this, SLOT(savingGame(QString)));

    // привяжем выбор сохранение к слоту открытия глаавной формы
    connect(myNewOpen,SIGNAL(sendItem(QString)),this,SLOT(openingGame(QString)));

    // запрос на обновление таблицы к обновлению таблицы диалога
    connect(this,SIGNAL(refreshTable()),myNewOpen,SLOT(startTable()));

    // привяжем кнопку открытия ранее сохраненной игры к методу открытия
    connect(ui->btnOpen,SIGNAL(clicked()),this,SLOT(loadGame()));

    // судоку еще не создано
    isCreated = false;

    // завяжем рандом на время
    srand(time(0));

    // скроем таблицу
    ui->table_1->setVisible(false);
    ui->table_2->setVisible(false);
    ui->table_3->setVisible(false);
    ui->table_4->setVisible(false);
    ui->table_5->setVisible(false);
    ui->table_6->setVisible(false);
    ui->table_7->setVisible(false);
    ui->table_8->setVisible(false);
    ui->table_9->setVisible(false);
    ui->lineHFirst->setVisible(false);
    ui->lineHSecond->setVisible(false);
    ui->lineVFirst->setVisible(false);
    ui->lineVSecond->setVisible(false);
    ui->lblLevel->setVisible(false);

    // скроем имя таблицы
    ui->lblGameName->setVisible(false);
    ui->txtGameName->setVisible(false);

    // дадим таблицам строк и столбцов
    ui->table_1->setRowCount(3 ); // Устанавливает кол-во строк
    ui->table_1->setColumnCount(3); // Устанавливает кол-во столбцов
    ui->table_2->setRowCount(3 ); // Устанавливает кол-во строк
    ui->table_2->setColumnCount(3); // Устанавливает кол-во столбцов
    ui->table_3->setRowCount(3 ); // Устанавливает кол-во строк
    ui->table_3->setColumnCount(3); // Устанавливает кол-во столбцов
    ui->table_4->setRowCount(3 ); // Устанавливает кол-во строк
    ui->table_4->setColumnCount(3); // Устанавливает кол-во столбцов
    ui->table_5->setRowCount(3 ); // Устанавливает кол-во строк
    ui->table_5->setColumnCount(3); // Устанавливает кол-во столбцов
    ui->table_6->setRowCount(3 ); // Устанавливает кол-во строк
    ui->table_6->setColumnCount(3); // Устанавливает кол-во столбцов
    ui->table_7->setRowCount(3 ); // Устанавливает кол-во строк
    ui->table_7->setColumnCount(3); // Устанавливает кол-во столбцов
    ui->table_8->setRowCount(3 ); // Устанавливает кол-во строк
    ui->table_8->setColumnCount(3); // Устанавливает кол-во столбцов
    ui->table_9->setRowCount(3); // Устанавливает кол-во строк
    ui->table_9->setColumnCount(3); // Устанавливает кол-во столбцов

    // ограничим ввод пользователя
    val = new QRegExpValidator(QRegExp("^[1-9]\\d?"), this);
    // ^ = Каретка отрицает набор символов, если он встречается в качестве первого символа,
    // \d = true, если символ деситичная цифра
    // то есть В параметра только цифры. При этом значение не может начинаться на цифру 0.

    // создадим меню бар
    menuCreation();


    // вкл | выкл помощник
    gameModeHelp = parametrMenu->addAction("Помощник", this , SLOT(gameModeHelpChanged()));
    gameModeHelp->setCheckable(true);
    gameModeHelp->setChecked(true); // помощник включен

    // привяжем ячейки к таблице
    itemAdding();

    // сделаем кнопку разворачивания окна Disabled
    this->setWindowFlags(
                Qt::Dialog // указывает, что виджет представляет собой окно, которое должно быть оформлено как диалоговое окно (т. е. обычно в строке заголовка нет кнопок "развернуть" или "свернуть")
                | Qt::CustomizeWindowHint // отключает настройки заголовка окна по умолчанию.
                | Qt::WindowCloseButtonHint // добавляет кнопку закртытия
                | Qt::WindowMinimizeButtonHint ); // добавляет кнопку сворачивания окна

    // уберем лишние кнопки у формы сохранения
    myNewSave->setWindowFlags(
                Qt::Dialog // указывает, что виджет представляет собой окно, которое должно быть оформлено как диалоговое окно (т. е. обычно в строке заголовка нет кнопок "развернуть" или "свернуть")
                | Qt::CustomizeWindowHint // отключает настройки заголовка окна по умолчанию.
                | Qt::WindowCloseButtonHint ); // добавляет кнопку закртытия

    // уберем лишние кнопки у формы открытия
    myNewOpen->setWindowFlags(
                Qt::Dialog // указывает, что виджет представляет собой окно, которое должно быть оформлено как диалоговое окно (т. е. обычно в строке заголовка нет кнопок "развернуть" или "свернуть")
                | Qt::CustomizeWindowHint // отключает настройки заголовка окна по умолчанию.
                | Qt::WindowCloseButtonHint ); // добавляет кнопку закртытия

}

Widget::~Widget()
{
    delete ui; // удаление главной формы
    delete myNewSave; // удаление формы сохранения
    delete myNewOpen; // удаление формы открытия

}

////////////// функции игрового процесса  //////////////

// функция запуска новой игры
void Widget::newGame()
{
    // скроем кнопки
    ui->vLayoutHello->setEnabled(false);
    ui->lblHello->setVisible(false);
    ui->lblName->setVisible(false);
    ui->lblVibor->setVisible(false);
    ui->btnSoEasy->setVisible(false);
    ui->btnEasy->setVisible(false);
    ui->btnNormal->setVisible(false);
    ui->btnHard->setVisible(false);
    ui->btnSoHard->setVisible(false);
    ui->btnOpen->setVisible(false);
    ui->lineHButton->setVisible(false);

    // опустим кнопки под таблицу
    ui->lblHello->lower();
    ui->lblName->lower();
    ui->lblVibor->lower();
    ui->btnSoEasy->lower();
    ui->btnEasy->lower();
    ui->btnNormal->lower();
    ui->btnHard->lower();
    ui->btnSoHard->lower();
    ui->btnOpen->lower();
    ui->lineHButton->lower();

    // поднимем таблицы над кнопками
    ui->table_1->raise();
    ui->table_2->raise();
    ui->table_3->raise();
    ui->table_4->raise();
    ui->table_5->raise();
    ui->table_6->raise();
    ui->table_7->raise();
    ui->table_8->raise();
    ui->table_9->raise();
    ui->lineHFirst->raise();
    ui->lineHSecond->raise();
    ui->lineVFirst->raise();
    ui->lineVSecond->raise();
    ui->lblLevel->raise();

    // откроем видимость элементов
    ui->table_1->setVisible(true);
    ui->table_2->setVisible(true);
    ui->table_3->setVisible(true);
    ui->table_4->setVisible(true);
    ui->table_5->setVisible(true);
    ui->table_6->setVisible(true);
    ui->table_7->setVisible(true);
    ui->table_8->setVisible(true);
    ui->table_9->setVisible(true);
    ui->lineHFirst->setVisible(true);
    ui->lineHSecond->setVisible(true);
    ui->lineVFirst->setVisible(true);
    ui->lineVSecond->setVisible(true);
    ui->lblLevel->setVisible(true);
    ui->lblGameName->setVisible(true);
    ui->txtGameName->setVisible(true);

    // откроем при первом запуске меню сохранения
    saveFile->setEnabled(true);
    // и меню сохранения_как
    saveFileHow->setEnabled(true);
    // закроем очистку таблицы раз она чистая
    cleanTFile->setEnabled(false);

    // отобразим имя таблицы для пользователя
    ui->txtGameName->setText("");

    // судоку еще не создано
    isCreated = false;
    isNamed = false;
    isSaved = false;

    // создаем начальную таблицу , которую уже будем менять для пользователя
    toStartTable();

    // перетасуем таблицу
    shuffle();

    // обнулим количество вырваных ячеек
    colVirvan = 0 ;

    // вырвем из таблицы ячейки
    while( colVirvan != (level * 10 + 10) )
    {
        masT[rand() % 9][rand() % 9].setText("");
        colVirvan++;
    }

    // сохраним таблицу с вырванными & выделим базовые ячейки
    for (int stroka = 0 ; stroka < 9; stroka++)
    {
        for(int stolb = 0 ; stolb < 9; stolb++ )
        {
            // сохраним массив пока он чист( пока знаем какие ячейки пустые, а какие нет)
            masClean[stroka][stolb].setText(masT[stroka][stolb].text());
            // уберем фокус курсора с ячейки ( вдруг остался с прошлой игры)
            masT[stroka][stolb].clearFocus();

            // собирём разные ячейки в зависимости от их назначения
            if(masT[stroka][stolb].text() == "")
            {
                masT[stroka][stolb].setEnabled(true);

                masT[stroka][stolb].setPalette(itemPalStart);

            }
            else
            {
                masT[stroka][stolb].setEnabled(false);

                masT[stroka][stolb].setPalette(itemPalReadOnly);

            }
        }
    }

    // судоку создано
    isCreated = true;
}
// судоку изменилась ( проверочная функция помощника )
void Widget::tableChanged()
{
    // таблица была создана
    if(isCreated)
    {
        // откроем очистку таблицы
        cleanTFile->setEnabled(true);

        // если таблица изменена , значит не соответсвует ( но мы это исправим будет сравнение )
        isSaved = false;

        // откроем  кнопку сохранения
        saveFile->setEnabled(true);

        int table = 0; // номер сектора
        int strokaT = -1 ; // коориднаты в секторе
        int stolbT = -1;  // координаты в секторе
        int itemT = 0; // счетчик вспомогательного массива
        struct povtor
        {
            int povtorStrok;
            int povtorStolb;
            int povtorSector;
        };
        povtor masPovtor [9][9]; // создадим массив структур , чтоб знать о повторах ячейки и в строке и в толбце и секторе
        // обнулим его и проверим не дали ли нам ноль
        for(int stroka = 0 ; stroka < 9 ; stroka++)
        {
            for(int stolb = 0; stolb < 9; stolb++ )
            {
                masPovtor[stroka][stolb].povtorStrok = 0 ;
                masPovtor[stroka][stolb].povtorStolb = 0 ;
                masPovtor[stroka][stolb].povtorSector = 0;
            }
        }

        int colRed = 0; // количество неверных
        int colText = 0; // количество пустых
        int* masVrem; // временный массив для копий

        // проверка в каждой строке
        for(int stroka = 0 ; stroka < 9 ; stroka++)
        {
            masVrem = new int[9];

            // сделаем копию строки
            for(int stolb = 0; stolb < 9; stolb++ )
            {
                masVrem[stolb] = masT[stroka][stolb].text().toInt();
            }

            // возбмем каждую ячейку и сравним с каждой ячейкой копии
            for(int stolb = 0; stolb < 9; stolb++ )
            {
                // если ячейка не пустая проверим
                if(masT[stroka][stolb].text() != ""  )
                {
                    for(int stolbV = 0; stolbV < 9; stolbV ++ )
                    {
                        // если ячейка в копии совпадет с нашей
                        if( masVrem[stolbV] ==  masT[stroka][stolb].text().toInt() )
                        {
                            masPovtor[stroka][stolb].povtorStrok++;

                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorStrok > 1)
                            {
                                // если он еще не отмечен как bad и в копии тоже не отмечен
                                if( masT[stroka][stolb].palette() != itemPalBedBase ||  masT[stroka][stolbV].palette() != itemPalBedBase
                                        || masT[stroka][stolb].palette() != itemPalBedReadOnly ||  masT[stroka][stolbV].palette() != itemPalBedReadOnly  )
                                {
                                    if(masT[stroka][stolb].isEnabled())
                                    {
                                        masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                    }
                                    else
                                    {
                                        masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                    }

                                    if(masT[stroka][stolbV].isEnabled())
                                    {
                                        masT[stroka][stolbV].setPalette(itemPalBedBase); // то пометим как бед
                                    }
                                    else
                                    {
                                        masT[stroka][stolbV].setPalette(itemPalBedReadOnly);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            delete[] masVrem; // очистим для записи новой строки
        }

        // проверка в каждом столбце
        for(int stolb = 0; stolb < 9; stolb++ )
        {
            masVrem = new int[9];

            // сделаем копию столбца
            for(int stroka = 0 ; stroka < 9 ; stroka++)
            {
                masVrem[stroka] = masT[stroka][stolb].text().toInt();
            }

            // возьмем каждую ячейку и сравним с каждой ячейкой копии
            for(int stroka = 0 ; stroka < 9 ; stroka++)
            {
                // если ячейка не пустая проверим
                if(masT[stroka][stolb].text() != "" &&  masT[stroka][stolb].text().toInt() > 0)
                {
                    for(int strokaV = 0 ; strokaV < 9 ; strokaV++)
                    {
                        // если ячейка в копии совпадет с нашей
                        if( masVrem[strokaV] ==  masT[stroka][stolb].text().toInt()  )
                        {
                            masPovtor[stroka][stolb].povtorStolb++;

                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorStolb > 1)
                            {
                                // если он еще не отмечен как bad и в копии тоже не отмечен
                                if( masT[stroka][stolb].palette() != itemPalBedBase ||  masT[strokaV][stolb].palette() != itemPalBedBase
                                        || masT[stroka][stolb].palette() != itemPalBedReadOnly ||  masT[strokaV][stolb].palette() != itemPalBedReadOnly)
                                {
                                    if(masT[stroka][stolb].isEnabled())
                                    {
                                        masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                    }
                                    else
                                    {
                                        masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                    }

                                    if(masT[strokaV][stolb].isEnabled())
                                    {
                                        masT[strokaV][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                    }
                                    else
                                    {
                                        masT[strokaV][stolb].setPalette(itemPalBedReadOnly);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            delete[] masVrem; // очистим для записи нового столбца
        }

        // проверка в каждом секторе
        for (int stroka = 0 ; stroka < 9; stroka++)
        {
            for(int stolb = 0 ; stolb < 9; stolb++ )
            {
                masVrem = new int [9]; // дадим памяти массиву копий

                // узнаем номер сектора
                if(stroka < 3 && stolb < 3 ){ table = 1;  }
                if( 2 < stolb  && stolb < 6 && stroka < 3 ) { table = 2; }
                if(stolb > 5 && stroka < 3) { table = 3; }
                if(2 < stroka && stroka < 6 && stolb < 4) { table = 4; }
                if(stroka > 2 && stroka < 6 && stolb > 2 && stroka < 6 ) { table = 5; }
                if(stroka > 2 && stroka < 6 && stolb > 5 ) { table = 6; }
                if( stroka > 5 && stolb < 3) { table = 7; }
                if(stroka > 5 && stolb > 2 && stolb < 7)  { table = 8; }
                if(stroka > 5 && stolb > 5 ) { table = 9; }

                switch(table)
                {
                case 1:
                {
                    itemT = 0 ;  // обнулим счетчик вспомогательного массива
                    // сделаем копию сектора
                    for(int strokaVnutr = 0 ; strokaVnutr < 3 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 0; stolbVnutr < 3; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // сравним ячейку со всеми значениями сектора
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // если ячейка в копии совпадет с нашей
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // узнаем какие координаты у этой повторяющейся копии
                                if(itemT == 0){ strokaT = 0; stolbT = 0;}
                                if(itemT == 1){ strokaT = 0; stolbT = 1;}
                                if(itemT == 2){ strokaT = 0; stolbT = 2;}
                                if(itemT == 3){ strokaT = 1; stolbT = 0;}
                                if(itemT == 4){ strokaT = 1; stolbT = 1;}
                                if(itemT == 5){ strokaT = 1; stolbT = 2;}
                                if(itemT == 6){ strokaT = 2; stolbT = 0;}
                                if(itemT == 7){ strokaT = 2; stolbT = 1;}
                                if(itemT == 8){ strokaT = 2; stolbT = 2;}

                                // совпало => пометим как бед
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // очистим для записи нового cсектора
                    itemT = 0; // обнулим счетчик вспомогательного массива

                    break;
                }
                case 2:
                {
                    itemT = 0 ;  // обнулим счетчик вспомогательного массива
                    // сделаем копию сектора
                    for(int strokaVnutr = 0 ; strokaVnutr < 3 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 3; stolbVnutr < 6; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // сравним ячейку со всеми значениями сектора
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // если ячейка в копии совпадет с нашей
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // узнаем какие координаты у этой повторяющейся копии
                                if(itemT == 0){ strokaT = 0; stolbT = 3;}
                                if(itemT == 1){ strokaT = 0; stolbT = 4;}
                                if(itemT == 2){ strokaT = 0; stolbT = 5;}
                                if(itemT == 3){ strokaT = 1; stolbT = 3;}
                                if(itemT == 4){ strokaT = 1; stolbT = 4;}
                                if(itemT == 5){ strokaT = 1; stolbT = 5;}
                                if(itemT == 6){ strokaT = 2; stolbT = 3;}
                                if(itemT == 7){ strokaT = 2; stolbT = 4;}
                                if(itemT == 8){ strokaT = 2; stolbT = 5;}

                                // совпало => пометим как бед
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // очистим для записи нового cсектора
                    itemT = 0; // обнулим счетчик вспомогательного массива

                    break;
                }
                case 3:
                {
                    itemT = 0 ;  // обнулим счетчик вспомогательного массива
                    // сделаем копию сектора
                    for(int strokaVnutr = 0 ; strokaVnutr < 3 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 6; stolbVnutr < 9; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // сравним ячейку со всеми значениями сектора
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // если ячейка в копии совпадет с нашей
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // узнаем какие координаты у этой повторяющейся копии
                                if(itemT == 0){ strokaT = 0; stolbT = 6;}
                                if(itemT == 1){ strokaT = 0; stolbT = 7;}
                                if(itemT == 2){ strokaT = 0; stolbT = 8;}
                                if(itemT == 3){ strokaT = 1; stolbT = 6;}
                                if(itemT == 4){ strokaT = 1; stolbT = 7;}
                                if(itemT == 5){ strokaT = 1; stolbT = 8;}
                                if(itemT == 6){ strokaT = 2; stolbT = 6;}
                                if(itemT == 7){ strokaT = 2; stolbT = 7;}
                                if(itemT == 8){ strokaT = 2; stolbT = 8;}

                                // совпало => пометим как бед
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // очистим для записи нового cсектора
                    itemT = 0; // обнулим счетчик вспомогательного массива

                    break;
                }
                case 4:
                {
                    itemT = 0 ;  // обнулим счетчик вспомогательного массива
                    // сделаем копию сектора
                    for(int strokaVnutr = 3 ; strokaVnutr < 6 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 0; stolbVnutr < 3; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // сравним ячейку со всеми значениями сектора
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // если ячейка в копии совпадет с нашей
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // узнаем какие координаты у этой повторяющейся копии
                                if(itemT == 0){ strokaT = 3; stolbT = 0;}
                                if(itemT == 1){ strokaT = 4; stolbT = 1;}
                                if(itemT == 2){ strokaT = 5; stolbT = 2;}
                                if(itemT == 3){ strokaT = 3; stolbT = 0;}
                                if(itemT == 4){ strokaT = 4; stolbT = 1;}
                                if(itemT == 5){ strokaT = 5; stolbT = 2;}
                                if(itemT == 6){ strokaT = 3; stolbT = 0;}
                                if(itemT == 7){ strokaT = 4; stolbT = 1;}
                                if(itemT == 8){ strokaT = 5; stolbT = 2;}

                                // совпало => пометим как бед
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // очистим для записи нового cсектора
                    itemT = 0; // обнулим счетчик вспомогательного массива

                    break;
                }
                case 5:
                {
                    itemT = 0 ;  // обнулим счетчик вспомогательного массива
                    // сделаем копию сектора
                    for(int strokaVnutr = 3 ; strokaVnutr < 6 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 3; stolbVnutr < 6; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // сравним ячейку со всеми значениями сектора
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // если ячейка в копии совпадет с нашей
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // узнаем какие координаты у этой повторяющейся копии
                                if(itemT == 0){ strokaT = 3; stolbT = 3;}
                                if(itemT == 1){ strokaT = 4; stolbT = 4;}
                                if(itemT == 2){ strokaT = 5; stolbT = 5;}
                                if(itemT == 3){ strokaT = 3; stolbT = 3;}
                                if(itemT == 4){ strokaT = 4; stolbT = 4;}
                                if(itemT == 5){ strokaT = 5; stolbT = 5;}
                                if(itemT == 6){ strokaT = 3; stolbT = 3;}
                                if(itemT == 7){ strokaT = 4; stolbT = 4;}
                                if(itemT == 8){ strokaT = 5; stolbT = 5;}

                                // совпало => пометим как бед
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // очистим для записи нового cсектора
                    itemT = 0; // обнулим счетчик вспомогательного массива

                    break;
                }
                case 6:
                {
                    itemT = 0 ;  // обнулим счетчик вспомогательного массива
                    // сделаем копию сектора
                    for(int strokaVnutr = 3 ; strokaVnutr < 6 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 6; stolbVnutr < 9; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // сравним ячейку со всеми значениями сектора
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // если ячейка в копии совпадет с нашей
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // узнаем какие координаты у этой повторяющейся копии
                                if(itemT == 0){ strokaT = 3; stolbT = 6;}
                                if(itemT == 1){ strokaT = 4; stolbT = 7;}
                                if(itemT == 2){ strokaT = 5; stolbT = 8;}
                                if(itemT == 3){ strokaT = 3; stolbT = 6;}
                                if(itemT == 4){ strokaT = 4; stolbT = 7;}
                                if(itemT == 5){ strokaT = 5; stolbT = 8;}
                                if(itemT == 6){ strokaT = 3; stolbT = 6;}
                                if(itemT == 7){ strokaT = 4; stolbT = 7;}
                                if(itemT == 8){ strokaT = 5; stolbT = 8;}

                                // совпало => пометим как бед
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }

                    }

                    delete[] masVrem; // очистим для записи нового cсектора
                    itemT = 0; // обнулим счетчик вспомогательного массива

                    break;
                }
                case 7:
                {
                    itemT = 0 ;  // обнулим счетчик вспомогательного массива
                    // сделаем копию сектора
                    for(int strokaVnutr = 6 ; strokaVnutr < 9 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 0; stolbVnutr < 3; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // сравним ячейку со всеми значениями сектора
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // если ячейка в копии совпадет с нашей
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // узнаем какие координаты у этой повторяющейся копии
                                if(itemT == 0){ strokaT = 6; stolbT = 0;}
                                if(itemT == 1){ strokaT = 7; stolbT = 1;}
                                if(itemT == 2){ strokaT = 8; stolbT = 2;}
                                if(itemT == 3){ strokaT = 6; stolbT = 0;}
                                if(itemT == 4){ strokaT = 7; stolbT = 1;}
                                if(itemT == 5){ strokaT = 8; stolbT = 2;}
                                if(itemT == 6){ strokaT = 6; stolbT = 0;}
                                if(itemT == 7){ strokaT = 7; stolbT = 1;}
                                if(itemT == 8){ strokaT = 8; stolbT = 2;}

                                // совпало => пометим как бед
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // очистим для записи нового cсектора
                    itemT = 0; // обнулим счетчик вспомогательного массива

                    break;
                }
                case 8:
                {
                    itemT = 0 ;  // обнулим счетчик вспомогательного массива
                    // сделаем копию сектора
                    for(int strokaVnutr = 6 ; strokaVnutr < 9 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 3; stolbVnutr < 6; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // сравним ячейку со всеми значениями сектора
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // если ячейка в копии совпадет с нашей
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // узнаем какие координаты у этой повторяющейся копии
                                if(itemT == 0){ strokaT = 6; stolbT = 3;}
                                if(itemT == 1){ strokaT = 7; stolbT = 4;}
                                if(itemT == 2){ strokaT = 8; stolbT = 5;}
                                if(itemT == 3){ strokaT = 6; stolbT = 3;}
                                if(itemT == 4){ strokaT = 7; stolbT = 4;}
                                if(itemT == 5){ strokaT = 8; stolbT = 5;}
                                if(itemT == 6){ strokaT = 6; stolbT = 3;}
                                if(itemT == 7){ strokaT = 7; stolbT = 4;}
                                if(itemT == 8){ strokaT = 8; stolbT = 5;}

                                // совпало => пометим как бед
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // очистим для записи нового cсектора
                    itemT = 0; // обнулим счетчик вспомогательного массива

                    break;
                }
                case 9:
                {
                    itemT = 0 ;  // обнулим счетчик вспомогательного массива
                    // сделаем копию сектора
                    for(int strokaVnutr = 6 ; strokaVnutr < 9 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 6; stolbVnutr < 9; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // сравним ячейку со всеми значениями сектора
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // если ячейка в копии совпадет с нашей
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // если это не первый повтор в копии
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // узнаем какие координаты у этой повторяющейся копии
                                if(itemT == 0){ strokaT = 6; stolbT = 6;}
                                if(itemT == 1){ strokaT = 7; stolbT = 7;}
                                if(itemT == 2){ strokaT = 8; stolbT = 8;}
                                if(itemT == 3){ strokaT = 6; stolbT = 6;}
                                if(itemT == 4){ strokaT = 7; stolbT = 7;}
                                if(itemT == 5){ strokaT = 8; stolbT = 8;}
                                if(itemT == 6){ strokaT = 6; stolbT = 6;}
                                if(itemT == 7){ strokaT = 7; stolbT = 7;}
                                if(itemT == 8){ strokaT = 8; stolbT = 8;}

                                // совпало => пометим как бед
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // то пометим как бед
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // очистим для записи нового cсектора
                    itemT = 0; // обнулим счетчик вспомогательного массива

                    break;
                }
                default:
                {
                    QMessageBox::information(this,"Ошибка", "В проверке каждого сектора");
                    break;
                }
                }
            }
        }

        // проверка вдруг чего надо вернуть к стоку и у него нет больше повторов
        for(int stroka = 0 ; stroka < 9 ; stroka++)
        {
            for(int stolb = 0; stolb < 9; stolb++ )
            {
                // если всего в одном экземпляре
                if(masPovtor[stroka][stolb].povtorStolb < 2 && masPovtor[stroka][stolb].povtorStrok < 2 && masPovtor[stroka][stolb].povtorSector < 2  )
                {
                    if( masT[stroka][stolb].isEnabled() == false )  masT[stroka][stolb].setPalette(itemPalReadOnly);  // пометим как readOnly
                    else masT[stroka][stolb].setPalette(itemPalStart); // пометим как обычная
                }
            }
        }

        // проверка всей таблицы на решенность
        for(int stroka = 0 ; stroka < 9 ; stroka++)
        {
            for(int stolb = 0; stolb < 9; stolb++ )
            {
                if(masT[stroka][stolb].text() == "") colText++;
                if(masT[stroka][stolb].palette() == itemPalBedBase ||masT[stroka][stolb].palette() == itemPalBedReadOnly ) colRed++;
            }
        }

        // окончательная проверка на решенность
        if( (colRed + colText ) == 0)
        {
            QMessageBox::information(this,"Ура", "Судоку решено !!!");
        }

        // проверка на неверное решение
        if(colRed != 0 && colText == 0)
        {
            qDebug() << colRed;
            QMessageBox::information(this,"Печаль", "Судоку решено, но неверно !!!");
        }
        else
        {
            // если помощник выключен вернем все цвета ячеек  к стоку
            if( ! gameModeHelp->isChecked() )
            {
                for (int stroka = 0 ; stroka < 9; stroka++)
                {
                    for(int stolb = 0 ; stolb < 9; stolb++ )
                    {
                        if( masT[stroka][stolb].isEnabled() == false )  masT[stroka][stolb].setPalette(itemPalReadOnly);  // пометим как readOnly
                        else masT[stroka][stolb].setPalette(itemPalStart); // пометим как обычная
                    }
                }
            }
        }
    }
}
// принимающая функция открытия файла
void Widget::openingGame(QString table)
{
    // сохраним имя открытой игры
    gameName = table;

    // отобразим имя таблицы для пользователя
    ui->txtGameName->setText(table);

    // скроем кнопки
    ui->vLayoutHello->setEnabled(false);
    ui->lblHello->setVisible(false);
    ui->lblName->setVisible(false);
    ui->lblVibor->setVisible(false);
    ui->btnSoEasy->setVisible(false);
    ui->btnEasy->setVisible(false);
    ui->btnNormal->setVisible(false);
    ui->btnHard->setVisible(false);
    ui->btnSoHard->setVisible(false);
    ui->btnOpen->setVisible(false);
    ui->lineHButton->setVisible(false);

    // опустим кнопки под таблицу
    ui->lblHello->lower();
    ui->lblName->lower();
    ui->lblVibor->lower();
    ui->btnSoEasy->lower();
    ui->btnEasy->lower();
    ui->btnNormal->lower();
    ui->btnHard->lower();
    ui->btnSoHard->lower();
    ui->btnOpen->lower();
    ui->lineHButton->lower();

    // поднимем таблицы над кнопками
    ui->table_1->raise();
    ui->table_2->raise();
    ui->table_3->raise();
    ui->table_4->raise();
    ui->table_5->raise();
    ui->table_6->raise();
    ui->table_7->raise();
    ui->table_8->raise();
    ui->table_9->raise();
    ui->lineHFirst->raise();
    ui->lineHSecond->raise();
    ui->lineVFirst->raise();
    ui->lineVSecond->raise();
    ui->lblLevel->raise();

    // откроем видимость элементов
    ui->table_1->setVisible(true);
    ui->table_2->setVisible(true);
    ui->table_3->setVisible(true);
    ui->table_4->setVisible(true);
    ui->table_5->setVisible(true);
    ui->table_6->setVisible(true);
    ui->table_7->setVisible(true);
    ui->table_8->setVisible(true);
    ui->table_9->setVisible(true);
    ui->lineHFirst->setVisible(true);
    ui->lineHSecond->setVisible(true);
    ui->lineVFirst->setVisible(true);
    ui->lineVSecond->setVisible(true);
    ui->lblLevel->setVisible(true);
    ui->lblGameName->setVisible(true);
    ui->txtGameName->setVisible(true);

    // откроем при первом запуске меню сохранения как
    saveFile->setEnabled(true);
    saveFileHow->setEnabled(true);

    // откроем очистку таблицы раз она чистая
    cleanTFile->setEnabled(true);

    // судоку  еще не создано( еще не отображено) // чтоб не запускал помощник раньше времени
    isCreated = false;
    isNamed = true;

    // очистим предыдущуюю таблицу
    for(int stroka = 0 ;stroka < 9 ; stroka++) delete[] masT[stroka];
    delete[] masT;

    for(int stroka = 0 ;stroka < 9 ; stroka++) delete[] masClean[stroka];
    delete[] masClean;

    // настроим форму к новой таблице
    menuCreation();

    // привяжем ячейки к новой таблице
    itemAdding();

    // Создаем новый объект file для представления файла с данным именем
    QFile fileT (QApplication::applicationDirPath()+"/data" + "/" + table);

    // создаем поток и прикрепляем поток на открытый файл
    QTextStream in(&fileT);

    // создади список строк , куда будем записывать части файловых строк
    QStringList *row;

    if(fileT.open(QIODevice::ReadOnly)) //открываем для чтения
    {
        for (int stroka = 0 ; stroka < 21; stroka++)
        {
            row = new QStringList( in.readLine().split("|")     );

            if(stroka == 1)
            {
                switch(row->at(0).toInt())
                {
                case 1:
                {
                    level = 1;
                    ui->lblLevel->setText("Уровень сложности:  очень легкий");
                    break;
                }
                case 3:
                {
                    level = 3;
                    ui->lblLevel->setText("Уровень сложности:     легкий");
                    break;
                }
                case 5:
                {
                    level = 5;
                    ui->lblLevel->setText("Уровень сложности:     средний");
                    break;
                }
                case 6:
                {
                    level = 6;
                    ui->lblLevel->setText("Уровень сложности:     сложный");
                    break;
                }
                case 7:
                {
                    level = 7;
                    ui->lblLevel->setText("Уровень сложности: очень сложный");
                    break;
                }
                }
            }

            if(stroka > 1  && stroka < 11 )
            {
                for(int stolb = 0 ; stolb < 9; stolb++ )
                {
                    masT[stroka - 2 ][stolb].setText(row->at(stolb));
                }
            }

            if( stroka > 11 && stroka < 21)
            {
                for(int stolb = 0 ; stolb < 9; stolb++ )
                {
                    if(row->at(stolb).toInt() == 1) masT[stroka - 12 ][stolb].setEnabled(true);
                    else  masT[stroka - 12 ][stolb].setEnabled(false);
                }
            }
            delete row;
        }

        // закроем файл
        fileT.close();
    }
    else
    {
        QMessageBox::information(this,"Открытие игры", "Файл не открылся ");
    }

    // сохраним таблицу с вырванными & выделим базовые ячейки
    for (int stroka = 0 ; stroka < 9; stroka++)
    {
        for(int stolb = 0 ; stolb < 9; stolb++ )
        {
            // перейдем от представления таблицы в файле к представлению таблицы в таблице
            if(masT[stroka][stolb].text() == " ") masT[stroka][stolb].setText("");

            if(masT[stroka][stolb].isEnabled())
            {
                masT[stroka][stolb].setPalette(itemPalStart);
            }
            // если ячейка недоступна запишем ее в чистый массив
            //( который отображается пользователю при нажатии на очистку)
            else
            {
                masClean[stroka][stolb].setText(masT[stroka][stolb].text());
                masT[stroka][stolb].setPalette(itemPalReadOnly);
            }
        }
    }

    // запустим помощник для проверки правильности ячеек
    gameModeHelpChanged();

    // судоку создано и сохранено
    isCreated = true;
    isSaved = true;

}
// принимающая функция сохранения судоку в файл
void Widget::savingGame(QString fileName)
{
    QString  dataT = QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss");
    QFile fileTables( QApplication::applicationDirPath()+"/data" + "/" + "Tables"); // файл всех таблиц

    // если имени еще нет (то есть если его только что ввел пользователь)
    if(!isNamed)
    {
        // запишем имя таблицы в память
        gameName = fileName;
        // отобразим имя таблицы для пользователя
        ui->txtGameName->setText(fileName);
        isNamed = true;
    }

    // если имя есть и происходит перезапись
    else
    {
        // удалим файл старой таблицы
        QFile(QApplication::applicationDirPath()+"/data" + "/" + fileName ).remove();

        // удалим строчку из файла всех игр

        // врменный файл для перекладывания
        QFile vrem(QApplication::applicationDirPath()+"/data" + "/" + "Vremen");
        vrem.open(QIODevice::WriteOnly); // откроем для добавления

        // указатели на два потока для перекладывания
        QTextStream* from;
        QTextStream* to;

        // строка для чтения из потока
        QString line;

        //открываем для чтения
        if(fileTables.open(QIODevice::ReadOnly))
        {
            // создаем потоки и прикрепляем поток на открытый файлы
            from = new QTextStream(&fileTables);
            to = new QTextStream(&vrem);

            // прочитаем строки таблиц из файла и запишем в лист
            // строка сравнения с именем удаляемой таблицы
            QString strSrav;
            // счетчик символов, для чикла
            int simbol;
            do
            {
                // обнулим строку для сравнения
                strSrav = "";

                // обнулим счетчик символов
                simbol = 0;

                // возьмём строку из потока
                line = from->readLine();

                //если строка не пустая
                if(line != "")
                {
                    // пока не дойдём до разделения в строке(то есть до конца имени)
                    while (line[simbol] != '|')
                    {
                        strSrav += line[simbol];
                        simbol++;
                    }

                    // если это не та строка, что мы удаляем запишем в поток
                    if(strSrav != fileName) (*to) << line << "\n" ;
                }
            }
            while (!line.isNull()); // пока не дойдем до пустой строки в потоке

            // закроем файлы
            fileTables.close();
            vrem.close();

            // очистим файл Tables и закроем
            fileTables.open(QIODevice::WriteOnly);
            fileTables.close();

            /////////////////////////////////////////
            //запишем правильный файл

            // откроем пустой файл
            fileTables.open(QIODevice::WriteOnly);
            // откроем временный файл с правильной таблицей
            vrem.open(QIODevice::ReadOnly); // откроем для чтения

            // создаем потоки и прикрепляем поток на открытый файлы
            from = new QTextStream(&vrem);
            to = new QTextStream(&fileTables);

            // перезапишем из потока в поток
            QString line2;
            do
            {
                line2 = from->readLine();
                (*to) << line2 << "\n";
            }
            while (!line2.isNull());

            // закроем файлы
            fileTables.close();
            vrem.close();

            // удалим ссылки на старые потоки
            delete from;
            delete to;

            // удалим временный файл
            vrem.remove();

        }
        // не открылся
        else
        {
            QMessageBox::information(this,"Открытие игры", "Не удалось открыть файл таблиц");
        }
    }

    // запишем в файл таблиц сведения о новой таблице
    if(fileTables.open(QIODevice::Append )) //открываем для добавления
    {
        QTextStream out(&fileTables); // создаем поток и прикрепляем поток на открытый файл

        out << fileName << "|"<< level << "|" << dataT  << "\n";

        fileTables.close(); // закрываем файл
    }
    // не удалось открыть файл таблиц
    else
    {
        QMessageBox::information(this,"Сохранение", "файл не открылся ");
    }

    // запишем таблицу в свой собсвенный файл
    QFile fileT(QApplication::applicationDirPath()+"/data" + "/" + fileName);
    if(fileT.open(QIODevice::WriteOnly)) //открываем для добавления
    {
        QTextStream out(&fileT); // создаем поток и прикрепляем поток на открытый файл

        out << fileName << "\n";
        out << level << "\n";

        // запомним цифры
        for(int stroka = 0 ; stroka < 9 ; stroka++)
        {
            for(int stolb = 0 ; stolb < 9 ; stolb++)
            {
                if(masT[stroka][stolb].text() == "")
                {
                    if(stolb != 8)
                    {
                        out << " " << "|" ;
                    }
                    else out << " ";
                }
                else
                {
                    if(stolb != 8)
                    {
                        out << masT[stroka][stolb].text() << "|" ;
                    }
                    else out << masT[stroka][stolb].text();
                }
            }
            out << "\n";
        }

        out << "\n";

        // запомним enabled
        for(int stroka = 0 ; stroka < 9 ; stroka++)
        {
            for(int stolb = 0 ; stolb < 9 ; stolb++)
            {
                if(masT[stroka][stolb].isEnabled())
                {
                    if(stolb != 8)
                    {
                        out << 1 << "|" ;
                    }
                    else out << 1;
                }
                else
                {
                    if(stolb != 8)
                    {
                        out << 0 << "|" ;
                    }
                    else out << 0;
                }
            }
            out << "\n";
        }
    }
    // не удалось открыть файл таблиц
    else
    {
        QMessageBox::information(this,"Сохранение", "файл не открылся ");
    }
}

////////////// функции для меню бара  //////////////

// создание меню бара и настройки всей главной формы в игровом режиме
void Widget::menuCreation()
{
    // дадим памяти массиву ячеек
    masT = new QLineEdit * [9];

    // дадим памяти чистому массиву
    masClean = new QLineEdit * [9];

    // им же дадим строки & сделаем таблицы квадратными
    for(int i=0; i < 9; i++)
    {
        // дадим строки
        masClean[i] = new  QLineEdit[9];
        masT[i] = new QLineEdit[9];

        // сделаем таблицы квадратными
        ui->table_1->setColumnWidth( i, 40 );
        ui->table_1->setRowHeight( i, 40 );
        ui->table_2->setColumnWidth( i, 40 );
        ui->table_2->setRowHeight( i, 40 );
        ui->table_3->setColumnWidth( i, 40 );
        ui->table_3->setRowHeight( i, 40 );
        ui->table_4->setColumnWidth( i, 40 );
        ui->table_4->setRowHeight( i, 40 );
        ui->table_5->setColumnWidth( i, 40 );
        ui->table_5->setRowHeight( i, 40 );
        ui->table_6->setColumnWidth( i, 40 );
        ui->table_6->setRowHeight( i, 40 );
        ui->table_7->setColumnWidth( i, 40 );
        ui->table_7->setRowHeight( i, 40 );
        ui->table_8->setColumnWidth( i, 40 );
        ui->table_8->setRowHeight( i, 40 );
        ui->table_9->setColumnWidth( i, 40 );
        ui->table_9->setRowHeight( i, 40 );
    }

    // запомним страртовую палитру ячейки
    itemPalStart = masT[0][0].palette();
    itemPalStart.setColor(QPalette::Base, QColor(250,250,250));
    itemPalStart.setColor(QPalette::Text, QColor(0,0,0));

    // изменим палитру для readOnly ячеек
    itemPalReadOnly = masT[0][0].palette();
    itemPalReadOnly.setColor(QPalette::Text, QColor(100,100,100) );

    // изменим палитру для readOnly неверных ячеек
    itemPalBedReadOnly = masT[0][0].palette();
    itemPalBedReadOnly.setColor(QPalette::Background, QColor(255,20,147));
    itemPalBedReadOnly.setColor(QPalette::Shadow, QColor(255,20,147));
    itemPalBedReadOnly.setColor(QPalette::Window, QColor(255,20,147));

    // изменим палитру для обычных неверных ячеек
    itemPalBedBase = masT[0][0].palette();
    itemPalBedBase.setColor(QPalette::Text, QColor(255,20,147));

    // установим выравниваие текста по центру & привяжем валидаторы & привяжем сигналы изминения ячеек
    for (int stroka = 0 ; stroka < 9; stroka++)
    {
        for(int stolb = 0 ; stolb < 9; stolb++ )
        {
            // установим максимальную длину строки
            masT[stroka][stolb].setMaxLength(1);

            // установим выравниваие текста по центру
            masT[stroka][stolb].setAlignment(Qt::AlignCenter);
            masClean[stroka][stolb].setAlignment(Qt::AlignCenter);

            // привяжем валидаторы
            masT[stroka][stolb].setValidator(val);
            masClean[stroka][stolb].setValidator(val);

            // привяжем сигналы изминения ячеек
            connect(&masT[stroka][stolb], SIGNAL( textChanged(const QString &)),this, SLOT(tableChanged()));
        }
    }

    // установим фиксированные размеры формы сохарнения
    myNewSave->setFixedSize(305,60);
    this->setFixedSize(445,491);

    // оформим меню
    // меню бар сверху
    QMenuBar * menuBar = new QMenuBar(this);

    // меню файл
    QMenu * fileMenu = new QMenu("Файл");

    // меню параметры
    parametrMenu = new QMenu("Параметры");


    // меню новой игры
    QMenu * newGameMenu = new QMenu("Начать новую игру");
    gameModeSoEasy = newGameMenu->addAction("Очень легкий", this,SLOT(newGame_VeryEasy()) );
    gameModeEasy =  newGameMenu->addAction("Легкий", this, SLOT(newGame_Easy()));
    gameModeNormal = newGameMenu->addAction("Средний", this, SLOT(newGame_Normal()));
    gameModeHard = newGameMenu->addAction("Сложный", this, SLOT(newGame_Hard()));
    gameModeSoHard = newGameMenu->addAction("Очень сложный ", this, SLOT(newGame_VeryHard()));
    // добавим меню внутрь меню файл
    fileMenu->addMenu(newGameMenu);

    // загрузить игру
    openFiles = fileMenu->addAction(QPixmap(":/icons/openIcon"),"Открыть игру",this,SLOT(loadGame()), Qt::CTRL + Qt::Key_O );

    // разделение разделов
    fileMenu ->addSeparator();

    // сохранить игру
    saveFile = fileMenu->addAction(QPixmap(":/icons/saving"),"Сохранить игру", this ,SLOT(saveGame()),Qt::CTRL + Qt::Key_S);

    // сохранить игру как
    saveFileHow = fileMenu->addAction("Сохранить игру как...", this ,SLOT(saveGameHow()),Qt::CTRL + Qt::SHIFT + Qt::Key_S);

    // разделение разделов
    fileMenu ->addSeparator();

    // очистка таблицы
    cleanTFile = fileMenu->addAction("Очистить заполненные ячейки",this,SLOT(cleanTable()));

    // разделение разделов
    fileMenu ->addSeparator();

    // выход
    fileMenu->addAction("Выход", this, SLOT(close()),Qt::CTRL + Qt::Key_Q );

    // добавить меню в бар
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(parametrMenu); // меню параметров

    // скроем при первом запуске меню очистки и сохранения
    cleanTFile->setEnabled(false);
    saveFile->setEnabled(false);
    saveFileHow->setEnabled(false);
}
// функция загрузки файла судоку ( открыывает форму открытия )
int Widget::loadGame()
{
    // переместим форму открытия туда , где наш виджет
    myNewOpen->move(this->x() + 30 ,this->y() + 60);

    // проверим есть ли файл таблиц игр
    if(!QFile(QApplication::applicationDirPath()+"/data" + "/" + "Tables").open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this,"Открытие игры", "У вас нет ни одной сохранённой игры");
        return 1; // отмена
    }

    // создадим врменный файл для проверки содержания
    QFile vrem(QApplication::applicationDirPath()+"/data" + "/" + "Tables");

    if(vrem.open(QIODevice::ReadOnly)) //открываем для чтения
    {
        // создаем поток и прикрепляем поток на открытый файл
        QTextStream in(&vrem);

        // временная строка для записи строк файла
        QString line;

        // количество строк в файле
        int lineCount = 0 ;

        // счетчик количества разделителей в строке
        int colRaz = 0;

        // посчитаем количество строк в файле
        do
        {
            // запишем прочитанную строку файла
            line = in.readLine();

            // обнулим счетчик
            colRaz = 0;
            for(int i = 0; i < line.size(); i++ )
            {
                if(line[i]=='|')  colRaz++;// количество символов разделения в строке
            }

            // строка не нулевая и нашли два разделения
            if(!line.isNull() && colRaz == 2)lineCount++; // увеличим счетчик строк

        }
        while (!line.isNull()); // пока не дойдём до пустой строки

        // если файл пуст
        if(!lineCount)
        {
            QMessageBox::information(this,"Открытие игры", "У вас нет ни одной сохранённой игры");
            return 1; // отмена
        }
    }
    else
    {
        QMessageBox::information(this,"Открытие игры", "У вас нет ни одной сохранённой игры");
        return 1; // отмена
    }

    // обновим таблицу диалога ( вдруг что нового добавили )
    this->refreshTable(); // signal connected to void DialogOpen::startTable()

    //  запускает форму и ждет ответа, модальность передается форме открытия)
    // нажата кнопка открыть
    if(myNewOpen->exec() == QDialog::Accepted)
    {
        // уберем фокус курсора прошлой игры
        for (int stroka = 0 ; stroka < 9; stroka++)
            for(int stolb = 0 ; stolb < 9; stolb++ )
                masT[stroka][stolb].clearFocus();

        QMessageBox::information(this,"Открытие", "Открыта игра с именем:\n"  + gameName );
        // уберем фокус курсора ( qmessagebox уго перехватил,а потом сразу поставил в последнее место)
        for (int stroka = 0 ; stroka < 9; stroka++)
            for(int stolb = 0 ; stolb < 9; stolb++ )
                masT[stroka][stolb].clearFocus();


        return 0 ;
    }

    // нажата кнопка отмена
    else
    {
        return 1; // отмена
    }
}
// функция сохранения названного
int Widget::saveGame()
{
    // имени еще нет
    if(!isNamed)
    {
        if(!saveGameHow()) return 0; // если в сохранить как нажали да
        else return 1 ; // отменили сохранение
    }

    // имя уже есть
    else
    {
        savingGame(gameName);
        // скроем кнопку сохранения
        saveFile->setEnabled(false);
        return 0; // сохранили
    }
}
// функция открытия формы сохранения как
int Widget::saveGameHow()
{
    // переместим форму сохранения туда , где наш виджет
    myNewSave->move(this->x() + 30 ,this->y() + 60);

    // нажата кнопка сохранить ( запускает форму и ждет ответа, модальность передается форме сохранения)
    if(myNewSave->exec() == QDialog::Accepted)
    {
        QMessageBox::information(this,"Сохранение", "Игра сохранена под именем:\n"  + gameName );

        // судоку сохранено
        isSaved = true;

        // судоку названо
        isNamed = true;

        // скроем кнопку сохранения
        saveFile->setEnabled(false);

        return 0 ;
    }

    // нажата кнопка отмена
    else
    {
        return 1;
    }
}
// функция очистки таблицы
void Widget::cleanTable()
{
    for (int stroka = 0 ; stroka < 9; stroka++)
    {
        for(int stolb = 0 ; stolb < 9; stolb++ )
        {
            //
            if( masT[stroka][stolb].palette() != itemPalReadOnly &&  masT[stroka][stolb].palette() != itemPalBedReadOnly)
                masT[stroka][stolb].setText(masClean[stroka][stolb].text());
        }
    }

    // закроем очистку таблицы раз она чистая
    cleanTFile->setEnabled(false);
}
// функция закрытия программы
void Widget::closeEvent(QCloseEvent *event)
{
    // закрываем ли
    bool ignored = false;

    // event =  событие по кнопке закрытия
    // если таблица создана но не названа
    if( isCreated && !isNamed)
    {
        // ответ пользователя
        int answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить эту игру?", "Да", "Нет", "Отмена") ;

        // да, сохранять
        if(answer == 0 )
        {
            // откроем форму сохранения
            // если отменили
            if(saveGameHow())
            {
                ignored = true; // нет, не закрывать
            }
        }
        // отмена
        if( answer == 2 )
        {
            ignored = true; // нет, не закрывать
        }
    }

    // таблица создана и названа, но не сохранена
    if(isCreated && isNamed && !isSaved )
    {
        // ответ пользователя
        int answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить изминения в игре\n" + gameName + " ?", "Сохранить", "Не сохранять", "Отмена") ;

        // да, сохранять
        if(answer == 0 )
        {
            // если отменили внутри формы сохранения
            if(saveGame()) // перезаписали ячейку
            {
                ignored = true;
            }
            ignored = false;
        }

        // нет, не сохранять
        if ( answer  == 1 )
        {
            ignored = false;
        }

        // отмена
        if( answer == 2 )
        {
            ignored = true; // нет, не закрывать
        }
    }

    // если закрываем приложение , то чистим память
    if(!ignored)
    {
        //// почистим память так как при
        //переопределении метода этого не проищойдет и программа завершиться с ошибкой
        // режим игры вкл | выкл помощник
        delete gameModeHelp ;
        // режим игры очень простой
        delete gameModeSoEasy;
        // режим игры простой
        delete gameModeEasy;
        // режим игры очень нормальный
        delete gameModeNormal;
        // режим игры сложный
        delete gameModeHard;
        // режим игры очень сложный
        delete gameModeSoHard;
        // загрузить игру
        delete openFiles;
        // сохранить игру
        delete saveFile;
        // сохранить игру как
        delete saveFileHow;
        // очистка таблицы
        delete cleanTFile;
        // удалим ссылку на валидатор
        delete val;
        // очистим массив ячеек таблицы
        for(int stroka = 0 ;stroka < 9 ; stroka++) delete[] masT[stroka];
        delete[] masT;
        // очистим массив для перекладывания
        for(int stroka = 0 ;stroka < 9 ; stroka++) delete[] masClean[stroka];
        delete[] masClean;

        event->accept(); // да закрываем (ставит флаг true)
    }

    // если не закрываем
    else
    {
        event->ignore(); // ставит флаг false ( да не закрывать )
    }
}

///////////// выборы режимов игры для меню бара  //////////////

// выбрана очень легкая игра
void Widget::newGame_VeryEasy()
{
    //если предыдущая игра существует спросим надо ли изменить
    if(isCreated)
    {
        // если предыдущая игра не сохранена , спросим не надо ли сохранить
        if(!isSaved)
        {
            // ответ пользователя
            int answer = 2; // отмена по умолчанию

            // если предыдущая игра не названа
            if(!isNamed)
            {
                // ответ пользователя
                answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить эту игру?", "Да", "Нет", "Отмена") ;

                // да, сохранять
                if(answer == 0 )
                {
                    // откроем форму сохранения
                    // если отменили внутри формы сохранения
                    if(saveGame())
                    {
                        return; // нет, не открывать новую игру
                    }
                }

                // отмена
                if( answer == 2 )
                {
                    return;
                }
            }
            // если предыдущая игра названа
            else
            {
                // ответ пользователя
                answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить изминения в игре\n" + gameName + " ?", "Сохранить", "Не сохранять", "Отмена") ;

                // да, сохранять
                if(answer == 0 )
                {
                    // откроем форму сохранения
                    // если отменили внутри формы сохранения
                    if(saveGame())
                    {
                        return; // нет, не открывать новую игру
                    }
                }

                // отмена
                if( answer == 2 )
                {
                    return;
                }
            }
        }
    }

    ui->lblLevel->setText("Уровень сложности:  очень легкий");
    level = 1;
    newGame();
}
// выбрана легкая игра
void Widget::newGame_Easy()
{
    //если предыдущая игра существует спросим надо ли изменить
    if(isCreated)
    {
        // если предыдущая игра не сохранена , спросим не надо ли сохранить
        if(!isSaved)
        {
            // ответ пользователя
            int answer = 2; // отмена по умолчанию

            // если предыдущая игра не названа
            if(!isNamed)
            {
                // ответ пользователя
                answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить эту игру?", "Да", "Нет", "Отмена") ;

                // да, сохранять
                if(answer == 0 )
                {
                    // откроем форму сохранения
                    // если отменили внутри формы сохранения
                    if(saveGame())
                    {
                        return; // нет, не открывать новую игру
                    }
                }

                // отмена
                if( answer == 2 )
                {
                    return;
                }
            }
            // если предыдущая игра названа
            else
            {
                // ответ пользователя
                answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить изминения в игре\n" + gameName + " ?", "Сохранить", "Не сохранять", "Отмена") ;

                // да, сохранять
                if(answer == 0 )
                {
                    // откроем форму сохранения
                    // если отменили внутри формы сохранения
                    if(saveGame())
                    {
                        return; // нет, не открывать новую игру
                    }
                }

                // отмена
                if( answer == 2 )
                {
                    return;
                }
            }
        }
    }

    ui->lblLevel->setText("Уровень сложности:     легкий");
    level = 3;
    newGame();
}
// выбрана нормальная игра
void Widget::newGame_Normal()
{
    //если предыдущая игра существует спросим надо ли изменить
    if(isCreated)
    {
        // если предыдущая игра не сохранена , спросим не надо ли сохранить
        if(!isSaved)
        {
            // ответ пользователя
            int answer = 2; // отмена по умолчанию

            // если предыдущая игра не названа
            if(!isNamed)
            {
                // ответ пользователя
                answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить эту игру?", "Да", "Нет", "Отмена") ;

                // да, сохранять
                if(answer == 0 )
                {
                    // откроем форму сохранения
                    // если отменили внутри формы сохранения
                    if(saveGame())
                    {
                        return; // нет, не открывать новую игру
                    }
                }

                // отмена
                if( answer == 2 )
                {
                    return;
                }
            }
            // если предыдущая игра названа
            else
            {
                // ответ пользователя
                answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить изминения в игре\n" + gameName + " ?", "Сохранить", "Не сохранять", "Отмена") ;

                // да, сохранять
                if(answer == 0 )
                {
                    // откроем форму сохранения
                    // если отменили внутри формы сохранения
                    if(saveGame())
                    {
                        return; // нет, не открывать новую игру
                    }
                }

                // отмена
                if( answer == 2 )
                {
                    return;
                }
            }
        }
    }

    ui->lblLevel->setText("Уровень сложности:     средний");
    level = 5;
    newGame();
}
// выбрана сложная игра
void Widget::newGame_Hard()
{
    //если предыдущая игра существует спросим надо ли изменить
    if(isCreated)
    {
        // если предыдущая игра не сохранена , спросим не надо ли сохранить
        if(!isSaved)
        {
            // ответ пользователя
            int answer = 2; // отмена по умолчанию

            // если предыдущая игра не названа
            if(!isNamed)
            {
                // ответ пользователя
                answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить эту игру?", "Да", "Нет", "Отмена") ;

                // да, сохранять
                if(answer == 0 )
                {
                    // откроем форму сохранения
                    // если отменили внутри формы сохранения
                    if(saveGame())
                    {
                        return; // нет, не открывать новую игру
                    }
                }

                // отмена
                if( answer == 2 )
                {
                    return;
                }
            }
            // если предыдущая игра названа
            else
            {
                // ответ пользователя
                answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить изминения в игре\n" + gameName + " ?", "Сохранить", "Не сохранять", "Отмена") ;

                // да, сохранять
                if(answer == 0 )
                {
                    // откроем форму сохранения
                    // если отменили внутри формы сохранения
                    if(saveGame())
                    {
                        return; // нет, не открывать новую игру
                    }
                }

                // отмена
                if( answer == 2 )
                {
                    return;
                }
            }
        }
    }

    ui->lblLevel->setText("Уровень сложности:     сложный");
    level = 6;
    newGame();
}
// выбрана очень сложная игра
void Widget::newGame_VeryHard()
{
    //если предыдущая игра существует спросим надо ли изменить
    if(isCreated)
    {
        // если предыдущая игра не сохранена , спросим не надо ли сохранить
        if(!isSaved)
        {
            // ответ пользователя
            int answer = 2; // отмена по умолчанию

            // если предыдущая игра не названа
            if(!isNamed)
            {
                // ответ пользователя
                answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить эту игру?", "Да", "Нет", "Отмена") ;

                // да, сохранять
                if(answer == 0 )
                {
                    // откроем форму сохранения
                    // если отменили внутри формы сохранения
                    if(saveGame())
                    {
                        return; // нет, не открывать новую игру
                    }
                }

                // отмена
                if( answer == 2 )
                {
                    return;
                }
            }
            // если предыдущая игра названа
            else
            {
                // ответ пользователя
                answer  =  QMessageBox::question(this,"Судоку","Хотите сохранить изминения в игре\n" + gameName + " ?", "Сохранить", "Не сохранять", "Отмена") ;

                // да, сохранять
                if(answer == 0 )
                {
                    // откроем форму сохранения
                    // если отменили внутри формы сохранения
                    if(saveGame())
                    {
                        return; // нет, не открывать новую игру
                    }
                }

                // отмена
                if( answer == 2 )
                {
                    return;
                }
            }
        }
    }

    ui->lblLevel->setText("Уровень сложности: очень сложный");
    level = 7;
    newGame();

}
// изменился вариант игры с подсказками | без
void Widget::gameModeHelpChanged()
{
    if(gameModeHelp->isChecked()) // помощник включен , запустим его
    {
        tableChanged();
    }
    else // если помощник выключен вернем все палитры к стоку
    {
        for (int stroka = 0 ; stroka < 9; stroka++)
        {
            for(int stolb = 0 ; stolb < 9; stolb++ )
            {
                if(! masT[stroka][stolb].isEnabled())  masT[stroka][stolb].setPalette(itemPalReadOnly);  // пометим как readOnly
                else masT[stroka][stolb].setPalette(itemPalStart); // пометим как обычная
            }
        }
    }
}

////////////// функции работы с таблицей //////////////

// функция создания "начальной" таблицы
void Widget::toStartTable()
{
    // выбирает какую использовать таблицу
    if(rand()%2)
    {
        masT[0][0].setText(QString::number(2));
        masT[0][1].setText(QString::number(9));
        masT[0][2].setText(QString::number(3));
        masT[0][3].setText(QString::number(4));
        masT[0][4].setText(QString::number(5));
        masT[0][5].setText(QString::number(7));
        masT[0][6].setText(QString::number(6));
        masT[0][7].setText(QString::number(8));
        masT[0][8].setText(QString::number(1));

        masT[1][0].setText(QString::number(4));
        masT[1][1].setText(QString::number(7));
        masT[1][2].setText(QString::number(5));
        masT[1][3].setText(QString::number(1));
        masT[1][4].setText(QString::number(8));
        masT[1][5].setText(QString::number(6));
        masT[1][6].setText(QString::number(3));
        masT[1][7].setText(QString::number(9));
        masT[1][8].setText(QString::number(2));

        masT[2][0].setText(QString::number(1));
        masT[2][1].setText(QString::number(6));
        masT[2][2].setText(QString::number(8));
        masT[2][3].setText(QString::number(3));
        masT[2][4].setText(QString::number(9));
        masT[2][5].setText(QString::number(2));
        masT[2][6].setText(QString::number(7));
        masT[2][7].setText(QString::number(4));
        masT[2][8].setText(QString::number(5));

        masT[3][0].setText(QString::number(9));
        masT[3][1].setText(QString::number(4));
        masT[3][2].setText(QString::number(2));
        masT[3][3].setText(QString::number(5));
        masT[3][4].setText(QString::number(7));
        masT[3][5].setText(QString::number(1));
        masT[3][6].setText(QString::number(8));
        masT[3][7].setText(QString::number(6));
        masT[3][8].setText(QString::number(3));

        masT[4][0].setText(QString::number(3));
        masT[4][1].setText(QString::number(8));
        masT[4][2].setText(QString::number(1));
        masT[4][3].setText(QString::number(6));
        masT[4][4].setText(QString::number(2));
        masT[4][5].setText(QString::number(9));
        masT[4][6].setText(QString::number(5));
        masT[4][7].setText(QString::number(7));
        masT[4][8].setText(QString::number(4));

        masT[5][0].setText(QString::number(6));
        masT[5][1].setText(QString::number(5));
        masT[5][2].setText(QString::number(7));
        masT[5][3].setText(QString::number(8));
        masT[5][4].setText(QString::number(3));
        masT[5][5].setText(QString::number(4));
        masT[5][6].setText(QString::number(1));
        masT[5][7].setText(QString::number(2));
        masT[5][8].setText(QString::number(9));

        masT[6][0].setText(QString::number(7));
        masT[6][1].setText(QString::number(2));
        masT[6][2].setText(QString::number(6));
        masT[6][3].setText(QString::number(9));
        masT[6][4].setText(QString::number(1));
        masT[6][5].setText(QString::number(3));
        masT[6][6].setText(QString::number(4));
        masT[6][7].setText(QString::number(5));
        masT[6][8].setText(QString::number(8));

        masT[7][0].setText(QString::number(5));
        masT[7][1].setText(QString::number(1));
        masT[7][2].setText(QString::number(4));
        masT[7][3].setText(QString::number(2));
        masT[7][4].setText(QString::number(6));
        masT[7][5].setText(QString::number(8));
        masT[7][6].setText(QString::number(9));
        masT[7][7].setText(QString::number(3));
        masT[7][8].setText(QString::number(7));

        masT[8][0].setText(QString::number(8));
        masT[8][1].setText(QString::number(3));
        masT[8][2].setText(QString::number(9));
        masT[8][3].setText(QString::number(7));
        masT[8][4].setText(QString::number(4));
        masT[8][5].setText(QString::number(5));
        masT[8][6].setText(QString::number(2));
        masT[8][7].setText(QString::number(1));
        masT[8][8].setText(QString::number(6));
    }
    else
    {
        for (int stroka = 0 ; stroka < 9; stroka++)
        {
            for(int stolb = 0 ; stolb < 9; stolb++ )
            {
                if( stroka == 0 ) masT[stroka][stolb].setText(QString::number(stolb + 1));
                if( stroka == 1 && stolb < 6 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb + 4 ));
                }
                if( stroka == 1 && stolb > 5 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb - 5 ));
                }
                if( stroka == 2 && stolb < 3 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb + 7 ));
                }
                if( stroka == 2 && stolb > 2 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb - 2 ));
                }
                if( stroka == 3 && stolb < 8 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb + 2 ));
                }
                if( stroka == 3 && stolb > 7 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb - 7 ));
                }
                if( stroka == 4 && stolb < 5 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb + 5 ));
                }
                if( stroka == 4 && stolb > 4 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb - 4 ));
                }
                if( stroka == 5 && stolb < 2 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb + 8 ));
                }
                if( stroka == 5 && stolb > 1 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb -1  ));
                }
                if( stroka == 6 && stolb < 7 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb + 3 ));
                }
                if( stroka == 6 && stolb > 6 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb - 6 ));
                }
                if( stroka == 7 && stolb < 4 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb + 6 ));
                }
                if( stroka == 7 && stolb > 3 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb - 3  ));
                }
                if( stroka == 8 && stolb < 1 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb + 9 ));
                }
                if( stroka == 8 && stolb > 0 )
                {
                    masT[stroka][stolb].setText(QString::number(stolb));
                }
            }
        }
    }
}
// функция привязки ячеек к таблице
void Widget::itemAdding()
{
    // привяжем ячейки к таблице
    int table = 0;
    int strokaT = -1 ;
    int stolbT = -1;
    for (int stroka = 0 ; stroka < 9; stroka++) // по строкам большой таблицы
    {
        for(int stolb = 0 ; stolb < 9; stolb++ ) // по стотбцам большой таблице
        {
            if(stroka < 3 && stolb < 3 ){ table = 1; }
            if( 2 < stolb  && stolb < 6 && stroka < 3 ) { table = 2; }
            if(stolb > 5 && stroka < 3) { table = 3; }
            if(2 < stroka && stroka < 6 && stolb < 4) { table = 4; }
            if(stroka > 2 && stroka < 6 && stolb > 2 && stroka < 6 ) { table = 5; }
            if(stroka > 2 && stroka < 6 && stolb > 5 ) { table = 6; }
            if( stroka > 5 && stolb < 3) { table = 7; }
            if(stroka > 5 && stolb > 2 && stolb < 7)  { table = 8; }
            if(stroka > 5 && stolb > 5 ) { table = 9; }

            switch (table)
            {
            case 1:
            {
                if(stolb == 0) stolbT = 0;
                if(stolb == 1 ) stolbT = 1;
                if(stolb == 2 ) stolbT = 2;

                if(stroka == 0) strokaT = 0;
                if(stroka == 1) strokaT = 1;
                if(stroka == 2) strokaT = 2;

                ui->table_1->setCellWidget(strokaT, stolbT, &masT[stroka][stolb]);
                break;
            }
            case 2:
            {
                if(stolb == 3) stolbT = 0;
                if(stolb == 4 ) stolbT = 1;
                if(stolb == 5 ) stolbT = 2;

                if(stroka == 0) strokaT = 0;
                if(stroka == 1) strokaT = 1;
                if(stroka == 2) strokaT = 2;

                ui->table_2->setCellWidget(strokaT, stolbT, &masT[stroka][stolb]);
                break;
            }
            case 3:
            {
                if(stolb == 6) stolbT = 0;
                if(stolb == 7 ) stolbT = 1;
                if(stolb == 8 ) stolbT = 2;

                if(stroka == 0) strokaT = 0;
                if(stroka == 1) strokaT = 1;
                if(stroka == 2) strokaT = 2;

                ui->table_3->setCellWidget(strokaT, stolbT, &masT[stroka][stolb]);
                break;
            }
            case 4:
            {
                if(stroka == 3) strokaT = 0;
                if(stroka == 4) strokaT = 1;
                if(stroka == 5) strokaT = 2;

                if(stolb == 0) stolbT = 0;
                if(stolb == 1 ) stolbT = 1;
                if(stolb == 2 ) stolbT = 2;

                ui->table_4->setCellWidget(strokaT, stolbT, &masT[stroka][stolb]);
                break;
            }
            case 5:
            {
                if(stolb == 3) stolbT = 0;
                if(stolb == 4 ) stolbT = 1;
                if(stolb == 5 ) stolbT = 2;

                if(stroka == 3) strokaT = 0;
                if(stroka == 4) strokaT = 1;
                if(stroka == 5) strokaT = 2;

                ui->table_5->setCellWidget(strokaT, stolbT, &masT[stroka][stolb]);
                break;
            }
            case 6:
            {
                if(stolb == 6) stolbT = 0;
                if(stolb == 7 ) stolbT = 1;
                if(stolb == 8 ) stolbT = 2;

                if(stroka == 3) strokaT = 0;
                if(stroka == 4) strokaT = 1;
                if(stroka == 5) strokaT = 2;

                ui->table_6->setCellWidget(strokaT, stolbT, &masT[stroka][stolb]);
                break;
            }
            case 7:
            {
                if(stroka == 6) strokaT = 0;
                if(stroka == 7) strokaT = 1;
                if(stroka == 8) strokaT = 2;

                if(stolb == 0) stolbT = 0;
                if(stolb == 1) stolbT = 1;
                if(stolb == 2 ) stolbT = 2;

                ui->table_7->setCellWidget(strokaT, stolbT, &masT[stroka][stolb]);
                break;
            }
            case 8:
            {
                if(stolb == 3) stolbT = 0;
                if(stolb == 4 ) stolbT = 1;
                if(stolb == 5 ) stolbT = 2;

                if(stroka == 6) strokaT = 0;
                if(stroka == 7) strokaT = 1;
                if(stroka == 8) strokaT = 2;

                ui->table_8->setCellWidget(strokaT, stolbT, &masT[stroka][stolb]);
                break;
            }
            case 9:
            {
                if(stolb == 6) stolbT = 0;
                if(stolb == 7 ) stolbT = 1;
                if(stolb == 8 ) stolbT = 2;

                if(stroka == 6) strokaT = 0;
                if(stroka == 7) strokaT = 1;
                if(stroka == 8) strokaT = 2;

                ui->table_9->setCellWidget(strokaT, stolbT, &masT[stroka][stolb]);
                break;
            }
            default:
            {
                QMessageBox::information(this,"Ошибка", "В давании таблицам ячеек");
                break;
            }
            }
        }
    }
}
// функция транспонирования таблицы
void Widget::transposing()
{
    int temp;
    for (int stroka = 0 ; stroka < 8; stroka++) // 8 потому что когда дойдем до последней строки уже не надо будет ничего перекладывать
    {
        switch(stroka)
        {
        case 0:
        {
            for(int stolb = 1 ; stolb < 9; stolb++ )
            {
                temp = masT[stroka][stolb].text().toInt();
                masT[stroka][stolb].setText(QString::number(masT[stolb][stroka].text().toInt()));
                masT[stolb][stroka].setText(QString::number(temp));
            }
            break;
        }
        case 1:
        {
            for(int stolb = 2 ; stolb < 9; stolb++ )
            {
                temp = masT[stroka][stolb].text().toInt();
                masT[stroka][stolb].setText(QString::number(masT[stolb][stroka].text().toInt()));
                masT[stolb][stroka].setText(QString::number(temp));
            }
            break;
        }
        case 2:
        {
            for(int stolb = 3 ; stolb < 9; stolb++ )
            {
                temp = masT[stroka][stolb].text().toInt();
                masT[stroka][stolb].setText(QString::number(masT[stolb][stroka].text().toInt()));
                masT[stolb][stroka].setText(QString::number(temp));
            }
            break;
        }
        case 3:
        {
            for(int stolb = 4 ; stolb < 9; stolb++ )
            {
                temp = masT[stroka][stolb].text().toInt();
                masT[stroka][stolb].setText(QString::number(masT[stolb][stroka].text().toInt()));
                masT[stolb][stroka].setText(QString::number(temp));
            }
            break;
        }
        case 4:
        {
            for(int stolb = 5 ; stolb < 9; stolb++ )
            {
                temp = masT[stroka][stolb].text().toInt();
                masT[stroka][stolb].setText(QString::number(masT[stolb][stroka].text().toInt()));
                masT[stolb][stroka].setText(QString::number(temp));
            }
            break;
        }
        case 5:
        {
            for(int stolb = 6 ; stolb < 9; stolb++ )
            {
                temp = masT[stroka][stolb].text().toInt();
                masT[stroka][stolb].setText(QString::number(masT[stolb][stroka].text().toInt()));
                masT[stolb][stroka].setText(QString::number(temp));
            }
            break;
        }
        case 6:
        {
            for(int stolb = 7 ; stolb < 9; stolb++ )
            {
                temp = masT[stroka][stolb].text().toInt();
                masT[stroka][stolb].setText(QString::number(masT[stolb][stroka].text().toInt()));
                masT[stolb][stroka].setText(QString::number(temp));
            }
            break;
        }
        case 7:
        {
            for(int stolb = 8 ; stolb < 9; stolb++ )
            {
                temp = masT[stroka][stolb].text().toInt();
                masT[stroka][stolb].setText(QString::number(masT[stolb][stroka].text().toInt()));
                masT[stolb][stroka].setText(QString::number(temp));
            }
            break;
        }
        default:
        {
            QMessageBox::information(this,"Ошибка", "В функции транспонирования");
            break;
        }
        }
    }
}
// функция обмена строк в пределах одного района ( 3 х 9 )
void Widget::swapRowsSmall()
{
    // район где будет менять строки
    int area = 0;
    // какие строкии будем менять
    int line_1 = 0;
    int line_2 = 0;

    // массив для копирования строк
    int  temp [9];

    // помешаем пять раз
    for(int razPeremesh = 0;  razPeremesh < 5;  razPeremesh ++ )
    {
        // найдем район где будет менять строки
        area = rand() % 3;

        // найдем какие строкии будем менять
        line_1 = rand() % 3;
        line_2 = rand() % 3;
        while (line_1 == line_2) { line_2 = rand() % 3;} // чтоб не переставлять один и тот же

        // поменяем их местами
        for( int stolb = 0 ; stolb < 9; stolb++ )
        {
            temp[stolb] =  masT[area * 3 + line_1][stolb].text().toInt();
            masT[area * 3 + line_1][stolb].setText(masT[area* 3 + line_2][stolb].text());
            masT[area* 3 + line_2][stolb].setText(QString::number(temp[stolb]));
        }
    }
}
// функция обмена столбцов в пределах одного района ( 9 х 3 )
void Widget::swapColumsSmall()
{
    // район где будет менять столбцы
    int area = 0;
    // какие столбцы будем менять
    int column_1 = 0;
    int column_2 = 0;

    // массив для копирования столбцов
    int  temp [9];

    // помешаем пять раз
    for(int razPeremesh = 0;  razPeremesh < 5;  razPeremesh ++ )
    {
        // найдем район где будет менять столбцы
        area = rand() % 3;

        // найдем какие столбцы будем менять
        column_1 = rand() % 3;
        column_2 = rand() % 3;
        while (column_1 == column_2) { column_2 = rand() % 3;}

        // поменяем их местами
        for (int stroka = 0 ; stroka < 9; stroka++)
        {
            temp[stroka] =  masT[stroka][area * 3 + column_1].text().toInt();
            masT[stroka][area * 3 + column_1].setText(masT[stroka][area* 3 + column_2].text());
            masT[stroka][area* 3 + column_2].setText(QString::number(temp[stroka]));
        }
    }
}
// функция обмена районов по горизонтали
void Widget::swapRowsArea()
{
    // найдем какие районы будем менять
    int area_1 = rand() % 3;
    int area_2 = rand() % 3;
    while (area_1 == area_2) { area_2 = rand() % 3;}

    int temp [9];
    for( int strokaN = 0 ; strokaN < 3; strokaN++)
    {
        for( int stolb = 0 ; stolb < 9; stolb++ )
        {
            temp[stolb] =  masT[area_1 * 3 + strokaN][stolb].text().toInt();
            masT[area_1 * 3 + strokaN][stolb].setText(masT[area_2 * 3 + strokaN][stolb].text());
            masT[area_2 * 3 + strokaN][stolb].setText(QString::number(temp[stolb]));
        }
    }
}
// функция обмена районов по вертикали
void Widget::swapColumsArea()
{
    // найдем какие районы будем менять (0/1/2)
    int area_1 = rand() % 3;
    int area_2 = rand() % 3;
    while (area_1 == area_2) { area_2 = rand() % 3;}

    int temp [9];
    for( int stolbN = 0 ; stolbN < 3; stolbN++)
    {
        for (int stroka = 0 ; stroka < 9; stroka++)
        {
            temp[stroka] =  masT[stroka][area_1 * 3 + stolbN].text().toInt();
            masT[stroka][area_1 * 3 + stolbN].setText(masT[stroka][area_2 * 3 + stolbN].text());
            masT[stroka][area_2 * 3 + stolbN].setText(QString::number(temp[stroka]));
        }
    }
}
// функция перемешивания таблицы
void Widget::shuffle()
{
    // перемешаем
    // с помощью транспонирования
    // обмена строк и столбцов
    // обмена районов со строками и столбцами

    // с помощью функий:
    //transposing();
    //swapRowsSmall();
    //swapColumsSmall();
    //swapRowsArea();
    //swapColumsArea();

    // обеспечим беспорядочность вызова функций перемешивания
    int masS[5] = {1,2,3,4,5}; // массив для switch
    int temp; // переменная для перекладывания
    int j; // номер ячейки , откуда перекладываем

    // помешаем массив и таблицу
    for(int razPeremesh = 0;  razPeremesh < 3;  razPeremesh ++ )
    {
        // помешаем массив
        for (int i = 4  ; i >= 1  ; i-- )
        {
            j = rand() % (i); // остаток от деления будет новым индексом
            temp = masS[j];
            masS[j] = masS[i];
            masS[i] = temp;
        }

        // помешаем таблицу
        for(int i = 0; i < 5; i ++ )
        {
            switch (masS[i])
            {
            case 1:
            {
                // функция транспонирования таблицы
                transposing();
                break;
            }
            case 2:
            {
                // функция обмена строк в пределах одного района ( 3 х 9 )
                swapRowsSmall();
                break;
            }
            case 3:
            {
                // функция обмена столбцов в пределах одного района ( 9 х 3 )
                swapColumsSmall();
                break;
            }
            case 4:
            {
                // функция обмена районов по горизонтали
                swapRowsArea();
                break;
            }
            case 5:
            {
                // функция обмена районов по вертикали
                swapColumsArea();
                break;
            }
            default:
            {
                QMessageBox::information(this,"Ошибка", "В функции shuffle");
                break;
            }
            }
        }
    }
}
