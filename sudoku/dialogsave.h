#ifndef DIALOGSAVE_H
#define DIALOGSAVE_H

#include <QDialog> // класс диалог, от которого наследуется наша форма сохранения
#include <QShowEvent> // класс событий открытия
#include <QMessageBox> // библиотека диалоговых окон
#include <cstdlib> // стандартная библиотека ( тут для создатия обьектов типа int и пребразования типов)
#include <QFile> // библиотека работы с файлами
#include <ui_widget.h> // для отправления сигнала клавной форме
#include <QDebug> // класс работы с отладкой


namespace Ui {
    class DialogSave;
}

class DialogSave : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSave(QWidget *parent = 0);
    ~DialogSave();

signals:

    // сигнал отправляющий строку главной форме
    void sendData(QString fileName);

private slots:

    // нажатие на кнопку сохранения
    void on_btnSave_clicked();
    // нажали на кнопку отмена
    void on_btnCancel_clicked();
    // событие показа формы сохранения
    void showEvent(QShowEvent *);

private:
    Ui::DialogSave *ui;

    // функция проверки имени файла на соответствование имени/пути в WINDOWS
    int isLegalFileName(QString name);

};

#endif // DIALOGSAVE_H
