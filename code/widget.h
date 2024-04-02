#ifndef WIDGET_H
#define WIDGET_H

#include <dialogopen.h> // ������� ���� ����� �������� �������� ����
#include <dialogsave.h> // ������� ���� ����� ���������� �������� ����
#include <QWidget> // ����� ������, �� �������� ����������� ���� ������� �����
#include <QLineEdit> // ���������� ����������
#include <QRegExpValidator> // ���������� ����������� ���������� ���������
#include <QDebug> // ��� �������
#include <QPalette> // ���������� ������
#include <QPicture> // ���������� pixmap��
#include <QString> // ���������� �����
#include <QMessageBox> // ���������� ���� ������
#include <iostream> // ���������� ������� ����� / ������
#include <cstdlib> // ��� ������� rand() � srand()
#include <QKeyEvent> // ���������� ������� �� ������� ����������
#include <ctime>  // ��� ������� time()
#include <QTableWidgetItem> // ���������� ��������� �������
#include <QMenuBar> // ���������� ��������
#include <QMenu> // ��������� ����, �� ������� ������� ���� ���
#include <QDir> // ���������� ����������
#include <QFile> // class ������ � �������
#include <QDateTime> // class ������ � ����� � ��������

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
    // ����������� ������� ���������� ������ � ����
    void savingGame(QString fileName);
    // ����������� ������� �������� �����
    void openingGame(QString table);

signals:
    // ������ ���������� �������
    void refreshTable();
private slots:

   ////////////// ������� ��� ���� ����  //////////////
    // ������� ������� �������
    void cleanTable();
    // ������� �������� ����� ���������� ���
    int saveGameHow ();
    // ������� ���������� ����������
    int saveGame();
    // ������� �������� ����� ������
    int loadGame();
    // ������� ����� ������ ����
    void newGame_VeryEasy();
    // ������� ������ ����
    void newGame_Easy();
    // ������� ���������� ����
    void newGame_Normal();
    // ������� ������� ����
    void newGame_Hard();
    // ������� ����� ������� ����
    void newGame_VeryHard();
    // ��������� ������� ���� � ����������� | ���
    void gameModeHelpChanged();
    // ������� �������� ���������
    void closeEvent(QCloseEvent *event);
   ////////////// ����� ��� �����  //////////////
    // ������ ����������
    void tableChanged();

private:
    Ui::Widget *ui; // ������� �����
    DialogSave *myNewSave; // ������ ����������
    DialogOpen *myNewOpen; // ������ ��������
    //  ��������� ��� �����
    QRegExpValidator* val;
    // ������ �������
    bool isCreated;
    // ������ ���������
    bool isSaved;
    // ������ �������
    bool isNamed;
    // ���������� ������ ����� �������
    int colVirvan;
    // ������� ���������
    int level;
    // ������ ������ ����
    QString gameStatus;
    // ������ ����� ���������� ����
    QString gameName;
    //  ������� �������� ���� ����
    void menuCreation();
    // ������� ������� ����� ����
    void newGame();

    ////////////// ������� ��� ������ � ��������  //////////////

    // ������ ����� �������
    QLineEdit **masT ;
    // ������ ������ ��� �������
    QLineEdit **masClean;

    ////////////// ������� �����  //////////////

    // ��������� ������� ������
    QPalette itemPalStart;
    // ������� ������������ ������ ������
    QPalette itemPalReadOnly;
    // ������� �������� ������ ������� ( ���� )
    QPalette itemPalBedBase;
    // ������� �������� ����������� ( ���� )
    QPalette itemPalBedReadOnly;

    ////////////// ������� ���� ��� ���� ����  //////////////

    // ���� ���������
    QMenu * parametrMenu;
    // ����� ���� ��� | ���� ��������
    QAction * gameModeHelp ;
    // ����� ���� ����� �������
    QAction * gameModeSoEasy;
    // ����� ���� �������
    QAction * gameModeEasy;
    // ����� ���� ����� ����������
    QAction * gameModeNormal;
    // ����� ���� �������
    QAction * gameModeHard;
    // ����� ���� ����� �������
    QAction * gameModeSoHard;
    // ��������� ����
    QAction *openFiles;
    // ��������� ����
    QAction *saveFile;
    // ��������� ���� ���
    QAction *saveFileHow;
    // ������� �������
    QAction *cleanTFile;

    ////////////// ������� ������ � �������� //////////////

    // ������� ���������������� �������
    void transposing();
    // ������� ������ ����� � �������� ������ ������ ( 3 � 9 )
    void swapRowsSmall();
    // ������� ������ �������� � �������� ������ ������ ( 9 � 3 )
    void swapColumsSmall();
    // ������� ������ ������� �� �����������
    void swapRowsArea();
    // ������� ������ ������� �� ���������
    void swapColumsArea();
    // ������� ������������� �������
    void shuffle();
    // ������� �������� ����� � �������
    void itemAdding();
    // ������� ����������� ������� � "���������"
    void toStartTable();
};

#endif // WIDGET_H
