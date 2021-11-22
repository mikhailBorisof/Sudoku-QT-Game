#include <QtGui/QApplication> // Класс QApplication управляет потоком управления графическим интерфейсом
#include "widget.h" // заголовочный файл
#include <QTextCodec> // подключение класса кодека текста

int main(int argc, char *argv[])
{
    //устанока русского языка в qt
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251"); //изменения
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
    //

    QApplication a(argc, argv);
    // создать объект формы
    Widget w;
    // отобразить форму
    w.show();

    // запускает графический интерфейс и ждет ответа, (модальность передается Application)
    return a.exec();
}
