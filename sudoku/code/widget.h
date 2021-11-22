#ifndef WIDGET_H
#define WIDGET_H

#include <dialogopen.h> // добавим файл формы открытия главному окну
#include <dialogsave.h> // добавим файл формы сохранения главному окну
#include <QWidget> // класс виджет, от которого наследуется наша главная форма
#include <QLineEdit> // библиотека лайнЭдитов
#include <QRegExpValidator> // библиотека вадидаторов регулярных выражений
#include <QDebug> // для отладки
#include <QPalette> // библиотека цветов
#include <QPicture> // библиотека pixmapов
#include <QString> // библиотека строк
#include <QMessageBox> // библиотека окон ошибок
#include <iostream> // библиотека потоков ввода / вывода
#include <cstdlib> // для функций rand() и srand()
#include <QKeyEvent> // библиотека нажатия на клавишу клавиатуры
#include <ctime>  // для функции time()
#include <QTableWidgetItem> // библиотека элементов таблицы
#include <QMenuBar> // библиотека менюБара
#include <QMenu> // библиотка меню, из которых состоит меню бар
#include <QDir> // библиотека директорий
#include <QFile> // class работы с файлами
#include <QDateTime> // class работы с датой и временем

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    // принимающая функция сохранения судоку в файл
    void savingGame(QString fileName);
    // принимающая функция открытия файла
    void openingGame(QString table);

signals:
    // сигнал обновления таблицы
    void refreshTable();
private slots:

   ////////////// функции для меню бара  //////////////
    // функция очистки таблицы
    void cleanTable();
    // функция открытия формы сохранения как
    int saveGameHow ();
    // функция сохранения названного
    int saveGame();
    // функция загрузки файла судоку
    int loadGame();
    // выбрана очень легкая игра
    void newGame_VeryEasy();
    // выбрана легкая игра
    void newGame_Easy();
    // выбрана нормальная игра
    void newGame_Normal();
    // выбрана сложная игра
    void newGame_Hard();
    // выбрана очень сложная игра
    void newGame_VeryHard();
    // изменился вариант игры с подсказками | без
    void gameModeHelpChanged();
    // функция закрытия программы
    void closeEvent(QCloseEvent *event);
   ////////////// слоты для ячеек  //////////////
    // судоку изменилась
    void tableChanged();

private:
    Ui::Widget *ui; // главная форма
    DialogSave *myNewSave; // диалог сохранения
    DialogOpen *myNewOpen; // диалог открытия
    //  валидатор для ячеек
    QRegExpValidator* val;
    // судоку создано
    bool isCreated;
    // судоку сохранено
    bool isSaved;
    // судоку названо
    bool isNamed;
    // количество пустых ячеек таблицы
    int colVirvan;
    // уровень сложности
    int level;
    // строка режима игры
    QString gameStatus;
    // строка имени сохранённой игры
    QString gameName;
    //  функция создание меню бара
    void menuCreation();
    // функция запуска новой игры
    void newGame();

    ////////////// массивы для работы с таблицей  //////////////

    // массив ячеек таблицы
    QLineEdit **masT ;
    // чистый массив для очистки
    QLineEdit **masClean;

    ////////////// палитры ячеек  //////////////

    // стартовая палитра ячейки
    QPalette itemPalStart;
    // палитра неизменяемой ячейки ячейки
    QPalette itemPalReadOnly;
    // палитра неверной ячейки обычной ( пары )
    QPalette itemPalBedBase;
    // палитра неверной неизменимой ( пары )
    QPalette itemPalBedReadOnly;

    ////////////// события меню для меню бара  //////////////

    // меню параметры
    QMenu * parametrMenu;
    // режим игры вкл | выкл помощник
    QAction * gameModeHelp ;
    // режим игры очень простой
    QAction * gameModeSoEasy;
    // режим игры простой
    QAction * gameModeEasy;
    // режим игры очень нормальный
    QAction * gameModeNormal;
    // режим игры сложный
    QAction * gameModeHard;
    // режим игры очень сложный
    QAction * gameModeSoHard;
    // загрузить игру
    QAction *openFiles;
    // сохранить игру
    QAction *saveFile;
    // сохранить игру как
    QAction *saveFileHow;
    // очистка таблицы
    QAction *cleanTFile;

    ////////////// функции работы с таблицей //////////////

    // функция транспонирования таблицы
    void transposing();
    // функция обмена строк в пределах одного района ( 3 х 9 )
    void swapRowsSmall();
    // функция обмена столбцов в пределах одного района ( 9 х 3 )
    void swapColumsSmall();
    // функция обмена районов по горизонтали
    void swapRowsArea();
    // функция обмена районов по вертикали
    void swapColumsArea();
    // функция перемешивания таблицы
    void shuffle();
    // функция привязки ячеек к таблице
    void itemAdding();
    // функция возвращения таблицы к "начальной"
    void toStartTable();
};

#endif // WIDGET_H
