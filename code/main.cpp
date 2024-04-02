#include <QtGui/QApplication> // ����� QApplication ��������� ������� ���������� ����������� �����������
#include "widget.h" // ������������ ����
#include <QTextCodec> // ����������� ������ ������ ������

int main(int argc, char *argv[])
{
    //�������� �������� ����� � qt
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251"); //���������
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
    //

    QApplication a(argc, argv);
    // ������� ������ �����
    Widget w;
    // ���������� �����
    w.show();

    // ��������� ����������� ��������� � ���� ������, (����������� ���������� Application)
    return a.exec();
}
