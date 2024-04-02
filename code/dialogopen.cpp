#include "dialogopen.h"  // заголовочный файл класса формы открытия
#include "ui_dialogopen.h" // файл формы окна открытия

// конструктор формы
DialogOpen::DialogOpen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOpen)
{
    ui->setupUi(this);
    // кнопка отмены открытия
    connect(ui->btnCancel,SIGNAL(clicked()),SLOT(reject())); // говорим модальности, что отклонили, если нажали cancel

    // выбрали ячейку таблицы пойдем в метод запоминающий строку ячейки
    connect(ui->table,SIGNAL(itemSelectionChanged()),this,SLOT(itemSelected()));
}
// деструктор формы
DialogOpen::~DialogOpen()
{
    delete ui;
}
// событие показа формы открытия
void DialogOpen::showEvent(QShowEvent *)
{
    // чтоб сразу при открытии формы фокус был на кнопке Отмена
    ui->btnDelete->setFocusPolicy(Qt::NoFocus);
    ui->table->setFocusPolicy(Qt::NoFocus);
    ui->btnOpen->setFocusPolicy(Qt::NoFocus);
    ui->btnCancel->setFocusPolicy( Qt::TabFocus);

}
// изминение выбранной ячейки
void DialogOpen::itemSelected()
{
    // selectionModel - класс знающий выбранные элементы таблицы
    // если что-то в таблице выбрано
    if(ui->table->selectionModel()->hasSelection())
    {
        // узнаем номер выбранной строки
        // selectedIndexes возвращает индексы выбранных ,
        //так как в нашей таблице только одно можно выбрать возьмем первый элемент списка
        // selectedIndexes возвращает индексы выбранных
        selectedRow = ui->table->selectionModel()->selectedIndexes().first().row() ;

        // открыть для пользователя кнопки удаления и открытия
        ui->btnDelete->setEnabled(true);
        ui->btnOpen->setEnabled(true);
    }
    else
    {
        // не открывать для пользователя кнопки удаления и открытия
        ui->btnDelete->setEnabled(false);
        ui->btnOpen->setEnabled(false);
    }
}
// подгрузка таблицы при открытии диалога
void DialogOpen::startTable()
{
    // кнопку открыть и удалить делаем не активными
    ui->btnOpen->setEnabled(false);
    ui->btnDelete->setEnabled(false);

    // только одну стороку таблицы можно выбрать
    ui->table->setSelectionMode(QAbstractItemView::SingleSelection);

    // устанавливает поведение строки при активации ячейки ( выделяет всю строку , в которой находиться ячейка)
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);

    // убирает предыдущие выделения , если они были
    ui->table->clearSelection();

    // Создаем новый объект file для представления файла с данным именем
    fileT = new QFile(QApplication::applicationDirPath()+"/data" + "/" + "Tables");

    if(fileT->open(QIODevice::ReadOnly)) //открываем для чтения
    {
        // создаем поток и прикрепляем поток на открытый файл
        QTextStream in(fileT);

        // создади список строк , куда будем записывать части файловых строк
        QStringList *tableF;

        // временная строка для записи строк файла
        QString line;

        // количество строк в файле
        lineCount = 0 ;

        // дадим памяти листу, куда будем складывать строки из файла
        tableF = new QStringList();

        // счетчик количества разделений в строке
        int colRaz = 0;

        // посчитаем количество строк в файле и запишем подходящие строки
        do
        {
            // запишем прочитанную строку файла
            line = in.readLine();
            //обнулим счетчик
            colRaz = 0;
            // посчитаем количество разделений в строке
            for(int i = 0; i < line.size(); i++)
            {
                if(line[i]=='|')  colRaz++;// количество символов разделения в строке файла
            }

            // строка не нулевая и нашли два разделения
            if(!line.isNull() && colRaz == 2)
            {
                // добавляет в строку | split разделяет строку на list строк
                tableF->append( line.split("|") );
            }
        }
        while (!line.isNull());// пока не дойдём до пустой строки

        // строк меньше, чем размер лист на количество ячеек в строке
        lineCount = tableF->size()/3;

        // файл не пустой
        if(lineCount)
        {
            // дадим памяти массиву ячеек
            masLabel = new QLabel* [lineCount];

            ui->table->setRowCount(lineCount ); // Устанавливает кол-во строк
            ui->table->setColumnCount(3); // Устанавливает кол-во столбцов

            // запретим менять ширину столбцов и строк
            ui->table->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
            ui->table->verticalHeader()->setResizeMode(QHeaderView::Fixed);

            // назовем столбцы таблицы
            QStringList name_table;
            name_table << "Название " << "Сложность" << "Дата";
            ui->table->setHorizontalHeaderLabels(name_table);

            // дадим строки
            for(int i = 0; i < lineCount; i++)
            {
                masLabel[i] = new QLabel[3];
            }

            // изменим цвет текста
            QPalette myPalette = masLabel[0][0].palette();
            myPalette.setColor(QPalette::Text, QColor(0,0,0));

            // дадим таблице ячеек
            for(int stroka = 0 ; stroka < lineCount ; stroka ++ )
            {
                for(int stolb = 0 ; stolb < 3; stolb++)
                {
                    ui->table->setCellWidget(stroka,stolb,&masLabel[stroka][stolb]); // привязка лэйблев к таблице
                    masLabel[stroka][stolb].setEnabled(false); // скроем возможность ввода текста
                    masLabel[stroka][stolb].setAlignment(Qt::AlignCenter); // текст по центру ячейки
                    masLabel[stroka][stolb].setPalette(myPalette); // изменим цвет текста
                }

                masLabel[stroka][0].setFixedWidth(250);
                masLabel[stroka][1].setFixedWidth(120);
                masLabel[stroka][2].setFixedWidth(140);
            }

            // установим параметры столбцов по ширине
            ui->table->setColumnWidth( 0, 250 );
            ui->table->setColumnWidth( 1, 120 );
            ui->table->setColumnWidth( 2, 140 );

            // прочитаем строки таблиц из файла
            for(int stroka = 0 ; stroka < lineCount ; stroka ++ )
            {
                // если в списке что-то есть
                for(int stolb = 0 ; stolb < 3; stolb++)
                {
                    // дадим содержимое столбца таблице ( кроме уровней сложности )
                    if(stolb != 1) masLabel[stroka][stolb].setText(tableF->at(stolb+(stroka*3)));
                    // для уровней сложности
                    else
                    {
                        if(tableF->at(stolb+(stroka*3)).toInt() == 1) masLabel[stroka][stolb].setText("Очень легкий");
                        if(tableF->at(stolb+(stroka*3)).toInt() == 3) masLabel[stroka][stolb].setText("Легкий");
                        if(tableF->at(stolb+(stroka*3)).toInt() == 5) masLabel[stroka][stolb].setText("Средний");
                        if(tableF->at(stolb+(stroka*3)).toInt() == 6) masLabel[stroka][stolb].setText("Сложный");
                        if(tableF->at(stolb+(stroka*3)).toInt() == 7) masLabel[stroka][stolb].setText("Очень сложный");
                    }
                }
            }

            // закроем всё
            // удалим указатель на лист
            delete tableF;
            // закроем файл
            fileT->close();
            // удалим указатель на файл
            delete fileT;
        }

        // файл пустой
        else
        {
            // скроем окно открытия игры
            this->hide();
            // сообщим модальности о закрытии окна
            this->on_btnCancel_clicked();
            // раскажем пользователю, что сохранённых игр нет
            QMessageBox::information(this,"Открытие игры", "У вас нет ни одной сохранённой игры");
            // закроем файл
            fileT->close();
            // удалим указатель на файл
            delete fileT;
        }
    }
    else
    {
        QMessageBox::information(this,"Открытие игры", "У вас нет ни одной сохранённой игры");
        // удалим указатель на файл
        delete fileT;
    }
}
// нажатие на кнопку отмены
void DialogOpen::on_btnCancel_clicked()
{
    // чистим память , чтоб при следующем показе формы можно было записать новое
    for(int stroka = 0 ;stroka < lineCount ; stroka++) delete[] masLabel[stroka];
    delete[] masLabel;
    // говорим модальности, что отклонили, если нажали cancel
    this->reject();
}
// нажатие на кнопку открыть
void DialogOpen::on_btnOpen_clicked()
{
    // отправим номер таблицы, которую следует открыть
    sendItem(masLabel[selectedRow][0].text());

    // чистим память , чтоб при следующем показе формы можно было записать новое
    for(int stroka = 0 ;stroka < lineCount ; stroka++) delete[] masLabel[stroka];
    delete[] masLabel;

    // говорим модальности, что приняли
    this->accept();
}
// нажатие на кнопку удаления
void DialogOpen::on_btnDelete_clicked()
{
    // lineCount для массива / rowCount для таблицы
    // удалим файл таблицы
    QString name = masLabel[selectedRow][0].text();
    QFile(QApplication::applicationDirPath()+"/data" + "/" + masLabel[selectedRow][0].text() ).remove();

    // дадим памяти массиву массивов ячеек новому
    QLabel** masCopy = new QLabel* [lineCount-1];
    // дадим строки
    for(int i=0; i < lineCount-1 ; i++) // он на одну строку короче старого из-за удаленной строки
    {
        masCopy[i] = new QLabel[3];
    }
    // копируем нашу таблицу в новый массив
    for(int stroka = 0 ; stroka < lineCount ; stroka ++ ) // кроме выбранной строки
    {
        for(int stolb = 0 ; stolb < 3; stolb++)
        {
            if(stroka < selectedRow)
            {
                masCopy[stroka][stolb].setText(masLabel[stroka][stolb].text());
            }

            if(stroka > selectedRow)
            {
                // все строчки сдвинулись на одну
                masCopy[stroka-1][stolb].setText(masLabel[stroka][stolb].text());
            }
        }
    }

    // удалим строчки и массив таблицы формы открытия ( он на один длинее нового)
    for(int stroka = 0 ;stroka < lineCount ; stroka++) delete[] masLabel[stroka];
    delete[] masLabel;

    // осталось ли что-то в таблице
    if(ui->table->rowCount()-1 != 0 )
    {
        // дадим памяти новому массиву ячеек
        masLabel = new QLabel* [ui->table->rowCount()-1];
        // дадим строки
        for(int i = 0; i < ui->table->rowCount()-1; i++) masLabel[i] = new QLabel[3];

        // изменим цвет текста
        QPalette myPalette = masLabel[0][0].palette();
        myPalette.setColor(QPalette::Text, QColor(0,0,0));

        // заполним массив таблицы открытия
        for(int stroka = 0 ; stroka < lineCount-1 ; stroka ++ )
        {
            for(int stolb = 0 ; stolb < 3; stolb++)
            {
                masLabel[stroka][stolb].setText(masCopy[stroka][stolb].text()); // напишем в массив все те занчения , что остались
                ui->table->setCellWidget(stroka,stolb,&masLabel[stroka][stolb]); // привязка новых лэйблев к таблице
                masLabel[stroka][stolb].setEnabled(false); // скроем возможность ввода текста
                masLabel[stroka][stolb].setAlignment(Qt::AlignCenter); // текст по центру ячейки
                masLabel[stroka][stolb].setPalette(myPalette); // изменим цвет текста
            }
        }
        // чистим память , чтоб при следующем показе формы можно было записать новое
        for(int stroka = 0 ;stroka < lineCount-1 ; stroka++) delete[] masCopy[stroka];
        delete[] masCopy;

        ///////////////////////////////////////////////////////////////////////////////////////////
        // удалим строчку из файла всех игр

        // Создаем ссылку на новый объект file для представления файла с данным именем
        fileT = new QFile(QApplication::applicationDirPath()+"/data" + "/" + "Tables");

        // врменный файл для перекладывания
        QFile vrem(QApplication::applicationDirPath()+"/data" + "/" + "Vremen");
        vrem.open(QIODevice::WriteOnly); // откроем для добавления

        // указатели на два потока для перекладывания
        QTextStream* from;
        QTextStream* to;

        // строка для чтения из потока
        QString line;

        if(fileT->open(QIODevice::ReadOnly)) //открываем для чтения
        {
            // создаем потоки и прикрепляем поток на открытый файлы
            from = new QTextStream(fileT);
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

                    // если это не та строка, что мы удаляем запишем в в лист
                    if(strSrav != name) (*to) << line << "\n" ;
                }
            }
            while (!line.isNull()); // пока не дойдем до пустой строки в потоке

            // закроем файлы
            fileT->close();
            vrem.close();

            // очистим файл Tables и закроем
            fileT->open(QIODevice::WriteOnly);
            fileT->close();

            /////////////////////////////////////////
            //запишем правильный файл

            // откроем пустой файл
            fileT->open(QIODevice::WriteOnly);
            // откроем временный файл с правильной таблицей
            vrem.open(QIODevice::ReadOnly); // откроем для чтения

            // создаем потоки и прикрепляем поток на открытый файлы
            from = new QTextStream(&vrem);
            to = new QTextStream(fileT);

            // перезапишем из потока в поток
            QString line2;
            do
            {
                line2 = from->readLine();
                (*to) << line2 << "\n";
            }
            while (!line2.isNull());

            // закроем файлы
            fileT->close();
            vrem.close();

            // удалим ссылки на старые потоки
            delete from;
            delete to;

            // удалим временный файл
            vrem.remove();

            // удалим указатель на файл
            delete fileT;

            // изменилось число строк
            lineCount = lineCount - 1;

            // изменилось число строк в таблице
            ui->table->setRowCount(lineCount);

            // уберем выделение
            ui->table->clearSelection();

        }
        // не открылся
        else
        {
            QMessageBox::information(this,"Открытие игры", "Не удалось открыть файл таблиц");
        }
    }
    // если ничего в таблице не остальсь
    else
    {
        // Создаем ссылку на новый объект file для представления файла с данным именем
        fileT = new QFile(QApplication::applicationDirPath()+"/data" + "/" + "Tables");
        if(fileT->open(QIODevice::WriteOnly))
        {
            // очистим файл и закроем файл
            fileT->close();

            // удалим указатель на массив копирования
            delete[] masCopy;
            // уберем выделение с выбранной строки
            ui->table->setRowCount(0);

            // говорим модальности, что отклонили, если нажали cancel
            this->reject();

            // скажем , что ничего не осталось
            QMessageBox::information(this,"Открытие игры", "У вас нет ни одной сохранённой игры");
        }
        // не открылся
        else
        {
            QMessageBox::information(this,"Открытие игры", "Не удалось открыть файл таблиц");
        }
    }
}
