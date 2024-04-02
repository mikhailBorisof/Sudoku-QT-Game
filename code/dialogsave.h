#ifndef DIALOGSAVE_H
#define DIALOGSAVE_H

#include <QDialog> // ����� ������, �� �������� ����������� ���� ����� ����������
#include <QShowEvent> // ����� ������� ��������
#include <QMessageBox> // ���������� ���������� ����
#include <cstdlib> // ����������� ���������� ( ��� ��� �������� �������� ���� int � ������������� �����)
#include <QFile> // ���������� ������ � �������
#include <ui_widget.h> // ��� ����������� ������� ������� �����
#include <QDebug> // ����� ������ � ��������


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

    // ������ ������������ ������ ������� �����
    void sendData(QString fileName);

private slots:

    // ������� �� ������ ����������
    void on_btnSave_clicked();
    // ������ �� ������ ������
    void on_btnCancel_clicked();
    // ������� ������ ����� ����������
    void showEvent(QShowEvent *);

private:
    Ui::DialogSave *ui;

    // ������� �������� ����� ����� �� ���������������� �����/���� � WINDOWS
    int isLegalFileName(QString name);

};

#endif // DIALOGSAVE_H
