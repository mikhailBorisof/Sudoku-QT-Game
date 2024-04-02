#ifndef DIALOGOPEN_H
#define DIALOGOPEN_H

#include <QLabel> // ���������� ����� �����������
#include <QFile> // ���������� ������ � �������
#include <QShowEvent> // ����� ������� ��������
#include <QDialog>  // ����� ������, �� �������� ����������� ���� ����� ����������

#include <QMessageBox> // ���������� ���������� ����
#include <cstdlib> // ����������� ���������� ( ��� ��� �������� �������� ���� int)
#include <QTextStream> // ���������� ��������� �������
#include <QDebug> // ���������� ������ � �������

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

    // ������ ������������ ������ ������� �����
    void sendItem(QString fileName);

private slots:

    // ������� ������ ����� ����������
    void showEvent(QShowEvent *);
    // ��������� ��������� ������
    void itemSelected();
    // ��������� ������� ��� �������� �������
    void startTable();
    // ������ �� ������ ������
    void on_btnCancel_clicked();
    // ������ �� ������ �������
    void on_btnOpen_clicked();
    // ������ �� ������ ������� ����
    void on_btnDelete_clicked();

private:
    Ui::DialogOpen *ui;

    // ������ ����� �������
    QLabel** masLabel;
    // ������ file ��� ������������� ����� ���� ������
    QFile* fileT;
    // ���������� ����� � �����
    int lineCount;
    // ����� ������� , ������� ����� ������� ������������
    int selectedRow;

};

#endif // DIALOGOPEN_H
