#ifndef DIALOGOPEN_H
#define DIALOGOPEN_H

#include <QLabel> // библиотека полей отображени€
#include <QFile> // библиотека работы с файлами
#include <QShowEvent> // класс событий открыти€
#include <QDialog>  // класс диалог, от которого наследуетс€ наша форма сохранени€

#include <QMessageBox> // библиотека диалоговых окон
#include <cstdlib> // стандартна€ библиотека ( тут дл€ создати€ обьектов типа int)
#include <QTextStream> // библиотека текстовых потоков
#include <QDebug> // библиотека работы с отладко

namespace Ui {
class DialogOpen;
}

class DialogOpen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOpen(QWidget *parent = 0);
    ~DialogOpen();

signals:

    // сигнал отправл€ющий строку главной форме
    void sendItem(QString fileName);

private slots:

    // событие показа формы сохранени€
    void showEvent(QShowEvent *);
    // изминение выбранной €чейки
    void itemSelected();
    // подгрузка таблицы при открытии диалога
    void startTable();
    // нажали на кнопку отмена
    void on_btnCancel_clicked();
    // нажали на кнопку открыть
    void on_btnOpen_clicked();
    // нажали на кнопку удалить игру
    void on_btnDelete_clicked();

private:
    Ui::DialogOpen *ui;

    // массив €чеек таблицы
    QLabel** masLabel;
    // ќбъект file дл€ представлени€ файла всех таблиц
    QFile* fileT;
    // количество строк в файле
    int lineCount;
    // номер таблицы , которую хочет открыть пользователь
    int selectedRow;

};

#endif // DIALOGOPEN_H
