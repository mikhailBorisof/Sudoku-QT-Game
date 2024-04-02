#include "widget.h" // ������������ ���� ������ ������� �����
#include "ui_widget.h" // ���� ����� �������� ����

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myNewSave = new DialogSave(); // �������� ������ ����������
    myNewOpen = new DialogOpen(); // �������� ������ ��������

    // ���� �� ���������� ����� �������� �
    if(! QDir(QApplication::applicationDirPath()+"/data").exists())
    {
        // ������� ����� ����� � ������ exe
        QDir().mkdir(QApplication::applicationDirPath()+"/data");
    }

    // �������� ������ � ������� ����
    connect(ui->btnSoEasy,SIGNAL(clicked()),this,SLOT(newGame_VeryEasy()));
    connect(ui->btnEasy,SIGNAL(clicked()),this,SLOT(newGame_Easy()));
    connect(ui->btnNormal,SIGNAL(clicked()),this,SLOT(newGame_Normal()));
    connect(ui->btnHard,SIGNAL(clicked()),this,SLOT(newGame_Hard()));
    connect(ui->btnSoHard,SIGNAL(clicked()),this,SLOT(newGame_VeryHard()));

    // �������� ������ ����� ���������� � ����� ���������� ������� �����
    connect(myNewSave, SIGNAL(sendData(QString)), this, SLOT(savingGame(QString)));

    // �������� ����� ���������� � ����� �������� �������� �����
    connect(myNewOpen,SIGNAL(sendItem(QString)),this,SLOT(openingGame(QString)));

    // ������ �� ���������� ������� � ���������� ������� �������
    connect(this,SIGNAL(refreshTable()),myNewOpen,SLOT(startTable()));

    // �������� ������ �������� ����� ����������� ���� � ������ ��������
    connect(ui->btnOpen,SIGNAL(clicked()),this,SLOT(loadGame()));

    // ������ ��� �� �������
    isCreated = false;

    // ������� ������ �� �����
    srand(time(0));

    // ������ �������
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

    // ������ ��� �������
    ui->lblGameName->setVisible(false);
    ui->txtGameName->setVisible(false);

    // ����� �������� ����� � ��������
    ui->table_1->setRowCount(3 ); // ������������� ���-�� �����
    ui->table_1->setColumnCount(3); // ������������� ���-�� ��������
    ui->table_2->setRowCount(3 ); // ������������� ���-�� �����
    ui->table_2->setColumnCount(3); // ������������� ���-�� ��������
    ui->table_3->setRowCount(3 ); // ������������� ���-�� �����
    ui->table_3->setColumnCount(3); // ������������� ���-�� ��������
    ui->table_4->setRowCount(3 ); // ������������� ���-�� �����
    ui->table_4->setColumnCount(3); // ������������� ���-�� ��������
    ui->table_5->setRowCount(3 ); // ������������� ���-�� �����
    ui->table_5->setColumnCount(3); // ������������� ���-�� ��������
    ui->table_6->setRowCount(3 ); // ������������� ���-�� �����
    ui->table_6->setColumnCount(3); // ������������� ���-�� ��������
    ui->table_7->setRowCount(3 ); // ������������� ���-�� �����
    ui->table_7->setColumnCount(3); // ������������� ���-�� ��������
    ui->table_8->setRowCount(3 ); // ������������� ���-�� �����
    ui->table_8->setColumnCount(3); // ������������� ���-�� ��������
    ui->table_9->setRowCount(3); // ������������� ���-�� �����
    ui->table_9->setColumnCount(3); // ������������� ���-�� ��������

    // ��������� ���� ������������
    val = new QRegExpValidator(QRegExp("^[1-9]\\d?"), this);
    // ^ = ������� �������� ����� ��������, ���� �� ����������� � �������� ������� �������,
    // \d = true, ���� ������ ���������� �����
    // �� ���� � ��������� ������ �����. ��� ���� �������� �� ����� ���������� �� ����� 0.

    // �������� ���� ���
    menuCreation();


    // ��� | ���� ��������
    gameModeHelp = parametrMenu->addAction("��������", this , SLOT(gameModeHelpChanged()));
    gameModeHelp->setCheckable(true);
    gameModeHelp->setChecked(true); // �������� �������

    // �������� ������ � �������
    itemAdding();

    // ������� ������ �������������� ���� Disabled
    this->setWindowFlags(
                Qt::Dialog // ���������, ��� ������ ������������ ����� ����, ������� ������ ���� ��������� ��� ���������� ���� (�. �. ������ � ������ ��������� ��� ������ "����������" ��� "��������")
                | Qt::CustomizeWindowHint // ��������� ��������� ��������� ���� �� ���������.
                | Qt::WindowCloseButtonHint // ��������� ������ ���������
                | Qt::WindowMinimizeButtonHint ); // ��������� ������ ������������ ����

    // ������ ������ ������ � ����� ����������
    myNewSave->setWindowFlags(
                Qt::Dialog // ���������, ��� ������ ������������ ����� ����, ������� ������ ���� ��������� ��� ���������� ���� (�. �. ������ � ������ ��������� ��� ������ "����������" ��� "��������")
                | Qt::CustomizeWindowHint // ��������� ��������� ��������� ���� �� ���������.
                | Qt::WindowCloseButtonHint ); // ��������� ������ ���������

    // ������ ������ ������ � ����� ��������
    myNewOpen->setWindowFlags(
                Qt::Dialog // ���������, ��� ������ ������������ ����� ����, ������� ������ ���� ��������� ��� ���������� ���� (�. �. ������ � ������ ��������� ��� ������ "����������" ��� "��������")
                | Qt::CustomizeWindowHint // ��������� ��������� ��������� ���� �� ���������.
                | Qt::WindowCloseButtonHint ); // ��������� ������ ���������

}

Widget::~Widget()
{
    delete ui; // �������� ������� �����
    delete myNewSave; // �������� ����� ����������
    delete myNewOpen; // �������� ����� ��������

}

////////////// ������� �������� ��������  //////////////

// ������� ������� ����� ����
void Widget::newGame()
{
    // ������ ������
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

    // ������� ������ ��� �������
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

    // �������� ������� ��� ��������
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

    // ������� ��������� ���������
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

    // ������� ��� ������ ������� ���� ����������
    saveFile->setEnabled(true);
    // � ���� ����������_���
    saveFileHow->setEnabled(true);
    // ������� ������� ������� ��� ��� ������
    cleanTFile->setEnabled(false);

    // ��������� ��� ������� ��� ������������
    ui->txtGameName->setText("");

    // ������ ��� �� �������
    isCreated = false;
    isNamed = false;
    isSaved = false;

    // ������� ��������� ������� , ������� ��� ����� ������ ��� ������������
    toStartTable();

    // ���������� �������
    shuffle();

    // ������� ���������� �������� �����
    colVirvan = 0 ;

    // ������ �� ������� ������
    while( colVirvan != (level * 10 + 10) )
    {
        masT[rand() % 9][rand() % 9].setText("");
        colVirvan++;
    }

    // �������� ������� � ���������� & ������� ������� ������
    for (int stroka = 0 ; stroka < 9; stroka++)
    {
        for(int stolb = 0 ; stolb < 9; stolb++ )
        {
            // �������� ������ ���� �� ����( ���� ����� ����� ������ ������, � ����� ���)
            masClean[stroka][stolb].setText(masT[stroka][stolb].text());
            // ������ ����� ������� � ������ ( ����� ������� � ������� ����)
            masT[stroka][stolb].clearFocus();

            // ������ ������ ������ � ����������� �� �� ����������
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

    // ������ �������
    isCreated = true;
}
// ������ ���������� ( ����������� ������� ��������� )
void Widget::tableChanged()
{
    // ������� ���� �������
    if(isCreated)
    {
        // ������� ������� �������
        cleanTFile->setEnabled(true);

        // ���� ������� �������� , ������ �� ������������ ( �� �� ��� �������� ����� ��������� )
        isSaved = false;

        // �������  ������ ����������
        saveFile->setEnabled(true);

        int table = 0; // ����� �������
        int strokaT = -1 ; // ���������� � �������
        int stolbT = -1;  // ���������� � �������
        int itemT = 0; // ������� ���������������� �������
        struct povtor
        {
            int povtorStrok;
            int povtorStolb;
            int povtorSector;
        };
        povtor masPovtor [9][9]; // �������� ������ �������� , ���� ����� � �������� ������ � � ������ � � ������ � �������
        // ������� ��� � �������� �� ���� �� ��� ����
        for(int stroka = 0 ; stroka < 9 ; stroka++)
        {
            for(int stolb = 0; stolb < 9; stolb++ )
            {
                masPovtor[stroka][stolb].povtorStrok = 0 ;
                masPovtor[stroka][stolb].povtorStolb = 0 ;
                masPovtor[stroka][stolb].povtorSector = 0;
            }
        }

        int colRed = 0; // ���������� ��������
        int colText = 0; // ���������� ������
        int* masVrem; // ��������� ������ ��� �����

        // �������� � ������ ������
        for(int stroka = 0 ; stroka < 9 ; stroka++)
        {
            masVrem = new int[9];

            // ������� ����� ������
            for(int stolb = 0; stolb < 9; stolb++ )
            {
                masVrem[stolb] = masT[stroka][stolb].text().toInt();
            }

            // ������� ������ ������ � ������� � ������ ������� �����
            for(int stolb = 0; stolb < 9; stolb++ )
            {
                // ���� ������ �� ������ ��������
                if(masT[stroka][stolb].text() != ""  )
                {
                    for(int stolbV = 0; stolbV < 9; stolbV ++ )
                    {
                        // ���� ������ � ����� �������� � �����
                        if( masVrem[stolbV] ==  masT[stroka][stolb].text().toInt() )
                        {
                            masPovtor[stroka][stolb].povtorStrok++;

                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorStrok > 1)
                            {
                                // ���� �� ��� �� ������� ��� bad � � ����� ���� �� �������
                                if( masT[stroka][stolb].palette() != itemPalBedBase ||  masT[stroka][stolbV].palette() != itemPalBedBase
                                        || masT[stroka][stolb].palette() != itemPalBedReadOnly ||  masT[stroka][stolbV].palette() != itemPalBedReadOnly  )
                                {
                                    if(masT[stroka][stolb].isEnabled())
                                    {
                                        masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                    }
                                    else
                                    {
                                        masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                    }

                                    if(masT[stroka][stolbV].isEnabled())
                                    {
                                        masT[stroka][stolbV].setPalette(itemPalBedBase); // �� ������� ��� ���
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
            delete[] masVrem; // ������� ��� ������ ����� ������
        }

        // �������� � ������ �������
        for(int stolb = 0; stolb < 9; stolb++ )
        {
            masVrem = new int[9];

            // ������� ����� �������
            for(int stroka = 0 ; stroka < 9 ; stroka++)
            {
                masVrem[stroka] = masT[stroka][stolb].text().toInt();
            }

            // ������� ������ ������ � ������� � ������ ������� �����
            for(int stroka = 0 ; stroka < 9 ; stroka++)
            {
                // ���� ������ �� ������ ��������
                if(masT[stroka][stolb].text() != "" &&  masT[stroka][stolb].text().toInt() > 0)
                {
                    for(int strokaV = 0 ; strokaV < 9 ; strokaV++)
                    {
                        // ���� ������ � ����� �������� � �����
                        if( masVrem[strokaV] ==  masT[stroka][stolb].text().toInt()  )
                        {
                            masPovtor[stroka][stolb].povtorStolb++;

                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorStolb > 1)
                            {
                                // ���� �� ��� �� ������� ��� bad � � ����� ���� �� �������
                                if( masT[stroka][stolb].palette() != itemPalBedBase ||  masT[strokaV][stolb].palette() != itemPalBedBase
                                        || masT[stroka][stolb].palette() != itemPalBedReadOnly ||  masT[strokaV][stolb].palette() != itemPalBedReadOnly)
                                {
                                    if(masT[stroka][stolb].isEnabled())
                                    {
                                        masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                    }
                                    else
                                    {
                                        masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                    }

                                    if(masT[strokaV][stolb].isEnabled())
                                    {
                                        masT[strokaV][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
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
            delete[] masVrem; // ������� ��� ������ ������ �������
        }

        // �������� � ������ �������
        for (int stroka = 0 ; stroka < 9; stroka++)
        {
            for(int stolb = 0 ; stolb < 9; stolb++ )
            {
                masVrem = new int [9]; // ����� ������ ������� �����

                // ������ ����� �������
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
                    itemT = 0 ;  // ������� ������� ���������������� �������
                    // ������� ����� �������
                    for(int strokaVnutr = 0 ; strokaVnutr < 3 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 0; stolbVnutr < 3; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // ������� ������ �� ����� ���������� �������
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // ���� ������ � ����� �������� � �����
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // ������ ����� ���������� � ���� ������������� �����
                                if(itemT == 0){ strokaT = 0; stolbT = 0;}
                                if(itemT == 1){ strokaT = 0; stolbT = 1;}
                                if(itemT == 2){ strokaT = 0; stolbT = 2;}
                                if(itemT == 3){ strokaT = 1; stolbT = 0;}
                                if(itemT == 4){ strokaT = 1; stolbT = 1;}
                                if(itemT == 5){ strokaT = 1; stolbT = 2;}
                                if(itemT == 6){ strokaT = 2; stolbT = 0;}
                                if(itemT == 7){ strokaT = 2; stolbT = 1;}
                                if(itemT == 8){ strokaT = 2; stolbT = 2;}

                                // ������� => ������� ��� ���
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // ������� ��� ������ ������ c�������
                    itemT = 0; // ������� ������� ���������������� �������

                    break;
                }
                case 2:
                {
                    itemT = 0 ;  // ������� ������� ���������������� �������
                    // ������� ����� �������
                    for(int strokaVnutr = 0 ; strokaVnutr < 3 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 3; stolbVnutr < 6; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // ������� ������ �� ����� ���������� �������
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // ���� ������ � ����� �������� � �����
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // ������ ����� ���������� � ���� ������������� �����
                                if(itemT == 0){ strokaT = 0; stolbT = 3;}
                                if(itemT == 1){ strokaT = 0; stolbT = 4;}
                                if(itemT == 2){ strokaT = 0; stolbT = 5;}
                                if(itemT == 3){ strokaT = 1; stolbT = 3;}
                                if(itemT == 4){ strokaT = 1; stolbT = 4;}
                                if(itemT == 5){ strokaT = 1; stolbT = 5;}
                                if(itemT == 6){ strokaT = 2; stolbT = 3;}
                                if(itemT == 7){ strokaT = 2; stolbT = 4;}
                                if(itemT == 8){ strokaT = 2; stolbT = 5;}

                                // ������� => ������� ��� ���
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // ������� ��� ������ ������ c�������
                    itemT = 0; // ������� ������� ���������������� �������

                    break;
                }
                case 3:
                {
                    itemT = 0 ;  // ������� ������� ���������������� �������
                    // ������� ����� �������
                    for(int strokaVnutr = 0 ; strokaVnutr < 3 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 6; stolbVnutr < 9; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // ������� ������ �� ����� ���������� �������
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // ���� ������ � ����� �������� � �����
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // ������ ����� ���������� � ���� ������������� �����
                                if(itemT == 0){ strokaT = 0; stolbT = 6;}
                                if(itemT == 1){ strokaT = 0; stolbT = 7;}
                                if(itemT == 2){ strokaT = 0; stolbT = 8;}
                                if(itemT == 3){ strokaT = 1; stolbT = 6;}
                                if(itemT == 4){ strokaT = 1; stolbT = 7;}
                                if(itemT == 5){ strokaT = 1; stolbT = 8;}
                                if(itemT == 6){ strokaT = 2; stolbT = 6;}
                                if(itemT == 7){ strokaT = 2; stolbT = 7;}
                                if(itemT == 8){ strokaT = 2; stolbT = 8;}

                                // ������� => ������� ��� ���
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // ������� ��� ������ ������ c�������
                    itemT = 0; // ������� ������� ���������������� �������

                    break;
                }
                case 4:
                {
                    itemT = 0 ;  // ������� ������� ���������������� �������
                    // ������� ����� �������
                    for(int strokaVnutr = 3 ; strokaVnutr < 6 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 0; stolbVnutr < 3; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // ������� ������ �� ����� ���������� �������
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // ���� ������ � ����� �������� � �����
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // ������ ����� ���������� � ���� ������������� �����
                                if(itemT == 0){ strokaT = 3; stolbT = 0;}
                                if(itemT == 1){ strokaT = 4; stolbT = 1;}
                                if(itemT == 2){ strokaT = 5; stolbT = 2;}
                                if(itemT == 3){ strokaT = 3; stolbT = 0;}
                                if(itemT == 4){ strokaT = 4; stolbT = 1;}
                                if(itemT == 5){ strokaT = 5; stolbT = 2;}
                                if(itemT == 6){ strokaT = 3; stolbT = 0;}
                                if(itemT == 7){ strokaT = 4; stolbT = 1;}
                                if(itemT == 8){ strokaT = 5; stolbT = 2;}

                                // ������� => ������� ��� ���
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // ������� ��� ������ ������ c�������
                    itemT = 0; // ������� ������� ���������������� �������

                    break;
                }
                case 5:
                {
                    itemT = 0 ;  // ������� ������� ���������������� �������
                    // ������� ����� �������
                    for(int strokaVnutr = 3 ; strokaVnutr < 6 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 3; stolbVnutr < 6; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // ������� ������ �� ����� ���������� �������
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // ���� ������ � ����� �������� � �����
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // ������ ����� ���������� � ���� ������������� �����
                                if(itemT == 0){ strokaT = 3; stolbT = 3;}
                                if(itemT == 1){ strokaT = 4; stolbT = 4;}
                                if(itemT == 2){ strokaT = 5; stolbT = 5;}
                                if(itemT == 3){ strokaT = 3; stolbT = 3;}
                                if(itemT == 4){ strokaT = 4; stolbT = 4;}
                                if(itemT == 5){ strokaT = 5; stolbT = 5;}
                                if(itemT == 6){ strokaT = 3; stolbT = 3;}
                                if(itemT == 7){ strokaT = 4; stolbT = 4;}
                                if(itemT == 8){ strokaT = 5; stolbT = 5;}

                                // ������� => ������� ��� ���
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // ������� ��� ������ ������ c�������
                    itemT = 0; // ������� ������� ���������������� �������

                    break;
                }
                case 6:
                {
                    itemT = 0 ;  // ������� ������� ���������������� �������
                    // ������� ����� �������
                    for(int strokaVnutr = 3 ; strokaVnutr < 6 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 6; stolbVnutr < 9; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // ������� ������ �� ����� ���������� �������
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // ���� ������ � ����� �������� � �����
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // ������ ����� ���������� � ���� ������������� �����
                                if(itemT == 0){ strokaT = 3; stolbT = 6;}
                                if(itemT == 1){ strokaT = 4; stolbT = 7;}
                                if(itemT == 2){ strokaT = 5; stolbT = 8;}
                                if(itemT == 3){ strokaT = 3; stolbT = 6;}
                                if(itemT == 4){ strokaT = 4; stolbT = 7;}
                                if(itemT == 5){ strokaT = 5; stolbT = 8;}
                                if(itemT == 6){ strokaT = 3; stolbT = 6;}
                                if(itemT == 7){ strokaT = 4; stolbT = 7;}
                                if(itemT == 8){ strokaT = 5; stolbT = 8;}

                                // ������� => ������� ��� ���
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }

                    }

                    delete[] masVrem; // ������� ��� ������ ������ c�������
                    itemT = 0; // ������� ������� ���������������� �������

                    break;
                }
                case 7:
                {
                    itemT = 0 ;  // ������� ������� ���������������� �������
                    // ������� ����� �������
                    for(int strokaVnutr = 6 ; strokaVnutr < 9 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 0; stolbVnutr < 3; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // ������� ������ �� ����� ���������� �������
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // ���� ������ � ����� �������� � �����
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // ������ ����� ���������� � ���� ������������� �����
                                if(itemT == 0){ strokaT = 6; stolbT = 0;}
                                if(itemT == 1){ strokaT = 7; stolbT = 1;}
                                if(itemT == 2){ strokaT = 8; stolbT = 2;}
                                if(itemT == 3){ strokaT = 6; stolbT = 0;}
                                if(itemT == 4){ strokaT = 7; stolbT = 1;}
                                if(itemT == 5){ strokaT = 8; stolbT = 2;}
                                if(itemT == 6){ strokaT = 6; stolbT = 0;}
                                if(itemT == 7){ strokaT = 7; stolbT = 1;}
                                if(itemT == 8){ strokaT = 8; stolbT = 2;}

                                // ������� => ������� ��� ���
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // ������� ��� ������ ������ c�������
                    itemT = 0; // ������� ������� ���������������� �������

                    break;
                }
                case 8:
                {
                    itemT = 0 ;  // ������� ������� ���������������� �������
                    // ������� ����� �������
                    for(int strokaVnutr = 6 ; strokaVnutr < 9 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 3; stolbVnutr < 6; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // ������� ������ �� ����� ���������� �������
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // ���� ������ � ����� �������� � �����
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // ������ ����� ���������� � ���� ������������� �����
                                if(itemT == 0){ strokaT = 6; stolbT = 3;}
                                if(itemT == 1){ strokaT = 7; stolbT = 4;}
                                if(itemT == 2){ strokaT = 8; stolbT = 5;}
                                if(itemT == 3){ strokaT = 6; stolbT = 3;}
                                if(itemT == 4){ strokaT = 7; stolbT = 4;}
                                if(itemT == 5){ strokaT = 8; stolbT = 5;}
                                if(itemT == 6){ strokaT = 6; stolbT = 3;}
                                if(itemT == 7){ strokaT = 7; stolbT = 4;}
                                if(itemT == 8){ strokaT = 8; stolbT = 5;}

                                // ������� => ������� ��� ���
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // ������� ��� ������ ������ c�������
                    itemT = 0; // ������� ������� ���������������� �������

                    break;
                }
                case 9:
                {
                    itemT = 0 ;  // ������� ������� ���������������� �������
                    // ������� ����� �������
                    for(int strokaVnutr = 6 ; strokaVnutr < 9 ; strokaVnutr++)
                    {
                        for(int stolbVnutr = 6; stolbVnutr < 9; stolbVnutr++ )
                        {
                            masVrem[itemT] = masT[strokaVnutr][stolbVnutr].text().toInt();
                            itemT++;
                        }
                    }

                    // ������� ������ �� ����� ���������� �������
                    for(itemT = 0 ; itemT < 9 ; itemT++)
                    {
                        // ���� ������ � ����� �������� � �����
                        if( ( masVrem[itemT] ==  masT[stroka][stolb].text().toInt() ) && masVrem[itemT] != 0  )
                        {
                            masPovtor[stroka][stolb].povtorSector++;
                            // ���� ��� �� ������ ������ � �����
                            if(masPovtor[stroka][stolb].povtorSector > 1)
                            {
                                // ������ ����� ���������� � ���� ������������� �����
                                if(itemT == 0){ strokaT = 6; stolbT = 6;}
                                if(itemT == 1){ strokaT = 7; stolbT = 7;}
                                if(itemT == 2){ strokaT = 8; stolbT = 8;}
                                if(itemT == 3){ strokaT = 6; stolbT = 6;}
                                if(itemT == 4){ strokaT = 7; stolbT = 7;}
                                if(itemT == 5){ strokaT = 8; stolbT = 8;}
                                if(itemT == 6){ strokaT = 6; stolbT = 6;}
                                if(itemT == 7){ strokaT = 7; stolbT = 7;}
                                if(itemT == 8){ strokaT = 8; stolbT = 8;}

                                // ������� => ������� ��� ���
                                if(masT[stroka][stolb].isEnabled() )
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[stroka][stolb].setPalette(itemPalBedReadOnly);
                                }

                                if(masT[strokaT][stolbT].isEnabled())
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedBase); // �� ������� ��� ���
                                }
                                else
                                {
                                    masT[strokaT][stolbT].setPalette(itemPalBedReadOnly);
                                }
                            }
                        }
                    }

                    delete[] masVrem; // ������� ��� ������ ������ c�������
                    itemT = 0; // ������� ������� ���������������� �������

                    break;
                }
                default:
                {
                    QMessageBox::information(this,"������", "� �������� ������� �������");
                    break;
                }
                }
            }
        }

        // �������� ����� ���� ���� ������� � ����� � � ���� ��� ������ ��������
        for(int stroka = 0 ; stroka < 9 ; stroka++)
        {
            for(int stolb = 0; stolb < 9; stolb++ )
            {
                // ���� ����� � ����� ����������
                if(masPovtor[stroka][stolb].povtorStolb < 2 && masPovtor[stroka][stolb].povtorStrok < 2 && masPovtor[stroka][stolb].povtorSector < 2  )
                {
                    if( masT[stroka][stolb].isEnabled() == false )  masT[stroka][stolb].setPalette(itemPalReadOnly);  // ������� ��� readOnly
                    else masT[stroka][stolb].setPalette(itemPalStart); // ������� ��� �������
                }
            }
        }

        // �������� ���� ������� �� ����������
        for(int stroka = 0 ; stroka < 9 ; stroka++)
        {
            for(int stolb = 0; stolb < 9; stolb++ )
            {
                if(masT[stroka][stolb].text() == "") colText++;
                if(masT[stroka][stolb].palette() == itemPalBedBase ||masT[stroka][stolb].palette() == itemPalBedReadOnly ) colRed++;
            }
        }

        // ������������� �������� �� ����������
        if( (colRed + colText ) == 0)
        {
            QMessageBox::information(this,"���", "������ ������ !!!");
        }

        // �������� �� �������� �������
        if(colRed != 0 && colText == 0)
        {
            qDebug() << colRed;
            QMessageBox::information(this,"������", "������ ������, �� ������� !!!");
        }
        else
        {
            // ���� �������� �������� ������ ��� ����� �����  � �����
            if( ! gameModeHelp->isChecked() )
            {
                for (int stroka = 0 ; stroka < 9; stroka++)
                {
                    for(int stolb = 0 ; stolb < 9; stolb++ )
                    {
                        if( masT[stroka][stolb].isEnabled() == false )  masT[stroka][stolb].setPalette(itemPalReadOnly);  // ������� ��� readOnly
                        else masT[stroka][stolb].setPalette(itemPalStart); // ������� ��� �������
                    }
                }
            }
        }
    }
}
// ����������� ������� �������� �����
void Widget::openingGame(QString table)
{
    // �������� ��� �������� ����
    gameName = table;

    // ��������� ��� ������� ��� ������������
    ui->txtGameName->setText(table);

    // ������ ������
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

    // ������� ������ ��� �������
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

    // �������� ������� ��� ��������
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

    // ������� ��������� ���������
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

    // ������� ��� ������ ������� ���� ���������� ���
    saveFile->setEnabled(true);
    saveFileHow->setEnabled(true);

    // ������� ������� ������� ��� ��� ������
    cleanTFile->setEnabled(true);

    // ������  ��� �� �������( ��� �� ����������) // ���� �� �������� �������� ������ �������
    isCreated = false;
    isNamed = true;

    // ������� ����������� �������
    for(int stroka = 0 ;stroka < 9 ; stroka++) delete[] masT[stroka];
    delete[] masT;

    for(int stroka = 0 ;stroka < 9 ; stroka++) delete[] masClean[stroka];
    delete[] masClean;

    // �������� ����� � ����� �������
    menuCreation();

    // �������� ������ � ����� �������
    itemAdding();

    // ������� ����� ������ file ��� ������������� ����� � ������ ������
    QFile fileT (QApplication::applicationDirPath()+"/data" + "/" + table);

    // ������� ����� � ����������� ����� �� �������� ����
    QTextStream in(&fileT);

    // ������� ������ ����� , ���� ����� ���������� ����� �������� �����
    QStringList *row;

    if(fileT.open(QIODevice::ReadOnly)) //��������� ��� ������
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
                    ui->lblLevel->setText("������� ���������:  ����� ������");
                    break;
                }
                case 3:
                {
                    level = 3;
                    ui->lblLevel->setText("������� ���������:     ������");
                    break;
                }
                case 5:
                {
                    level = 5;
                    ui->lblLevel->setText("������� ���������:     �������");
                    break;
                }
                case 6:
                {
                    level = 6;
                    ui->lblLevel->setText("������� ���������:     �������");
                    break;
                }
                case 7:
                {
                    level = 7;
                    ui->lblLevel->setText("������� ���������: ����� �������");
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

        // ������� ����
        fileT.close();
    }
    else
    {
        QMessageBox::information(this,"�������� ����", "���� �� �������� ");
    }

    // �������� ������� � ���������� & ������� ������� ������
    for (int stroka = 0 ; stroka < 9; stroka++)
    {
        for(int stolb = 0 ; stolb < 9; stolb++ )
        {
            // �������� �� ������������� ������� � ����� � ������������� ������� � �������
            if(masT[stroka][stolb].text() == " ") masT[stroka][stolb].setText("");

            if(masT[stroka][stolb].isEnabled())
            {
                masT[stroka][stolb].setPalette(itemPalStart);
            }
            // ���� ������ ���������� ������� �� � ������ ������
            //( ������� ������������ ������������ ��� ������� �� �������)
            else
            {
                masClean[stroka][stolb].setText(masT[stroka][stolb].text());
                masT[stroka][stolb].setPalette(itemPalReadOnly);
            }
        }
    }

    // �������� �������� ��� �������� ������������ �����
    gameModeHelpChanged();

    // ������ ������� � ���������
    isCreated = true;
    isSaved = true;

}
// ����������� ������� ���������� ������ � ����
void Widget::savingGame(QString fileName)
{
    QString  dataT = QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss");
    QFile fileTables( QApplication::applicationDirPath()+"/data" + "/" + "Tables"); // ���� ���� ������

    // ���� ����� ��� ��� (�� ���� ���� ��� ������ ��� ���� ������������)
    if(!isNamed)
    {
        // ������� ��� ������� � ������
        gameName = fileName;
        // ��������� ��� ������� ��� ������������
        ui->txtGameName->setText(fileName);
        isNamed = true;
    }

    // ���� ��� ���� � ���������� ����������
    else
    {
        // ������ ���� ������ �������
        QFile(QApplication::applicationDirPath()+"/data" + "/" + fileName ).remove();

        // ������ ������� �� ����� ���� ���

        // �������� ���� ��� ��������������
        QFile vrem(QApplication::applicationDirPath()+"/data" + "/" + "Vremen");
        vrem.open(QIODevice::WriteOnly); // ������� ��� ����������

        // ��������� �� ��� ������ ��� ��������������
        QTextStream* from;
        QTextStream* to;

        // ������ ��� ������ �� ������
        QString line;

        //��������� ��� ������
        if(fileTables.open(QIODevice::ReadOnly))
        {
            // ������� ������ � ����������� ����� �� �������� �����
            from = new QTextStream(&fileTables);
            to = new QTextStream(&vrem);

            // ��������� ������ ������ �� ����� � ������� � ����
            // ������ ��������� � ������ ��������� �������
            QString strSrav;
            // ������� ��������, ��� �����
            int simbol;
            do
            {
                // ������� ������ ��� ���������
                strSrav = "";

                // ������� ������� ��������
                simbol = 0;

                // ������ ������ �� ������
                line = from->readLine();

                //���� ������ �� ������
                if(line != "")
                {
                    // ���� �� ����� �� ���������� � ������(�� ���� �� ����� �����)
                    while (line[simbol] != '|')
                    {
                        strSrav += line[simbol];
                        simbol++;
                    }

                    // ���� ��� �� �� ������, ��� �� ������� ������� � �����
                    if(strSrav != fileName) (*to) << line << "\n" ;
                }
            }
            while (!line.isNull()); // ���� �� ������ �� ������ ������ � ������

            // ������� �����
            fileTables.close();
            vrem.close();

            // ������� ���� Tables � �������
            fileTables.open(QIODevice::WriteOnly);
            fileTables.close();

            /////////////////////////////////////////
            //������� ���������� ����

            // ������� ������ ����
            fileTables.open(QIODevice::WriteOnly);
            // ������� ��������� ���� � ���������� ��������
            vrem.open(QIODevice::ReadOnly); // ������� ��� ������

            // ������� ������ � ����������� ����� �� �������� �����
            from = new QTextStream(&vrem);
            to = new QTextStream(&fileTables);

            // ����������� �� ������ � �����
            QString line2;
            do
            {
                line2 = from->readLine();
                (*to) << line2 << "\n";
            }
            while (!line2.isNull());

            // ������� �����
            fileTables.close();
            vrem.close();

            // ������ ������ �� ������ ������
            delete from;
            delete to;

            // ������ ��������� ����
            vrem.remove();

        }
        // �� ��������
        else
        {
            QMessageBox::information(this,"�������� ����", "�� ������� ������� ���� ������");
        }
    }

    // ������� � ���� ������ �������� � ����� �������
    if(fileTables.open(QIODevice::Append )) //��������� ��� ����������
    {
        QTextStream out(&fileTables); // ������� ����� � ����������� ����� �� �������� ����

        out << fileName << "|"<< level << "|" << dataT  << "\n";

        fileTables.close(); // ��������� ����
    }
    // �� ������� ������� ���� ������
    else
    {
        QMessageBox::information(this,"����������", "���� �� �������� ");
    }

    // ������� ������� � ���� ���������� ����
    QFile fileT(QApplication::applicationDirPath()+"/data" + "/" + fileName);
    if(fileT.open(QIODevice::WriteOnly)) //��������� ��� ����������
    {
        QTextStream out(&fileT); // ������� ����� � ����������� ����� �� �������� ����

        out << fileName << "\n";
        out << level << "\n";

        // �������� �����
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

        // �������� enabled
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
    // �� ������� ������� ���� ������
    else
    {
        QMessageBox::information(this,"����������", "���� �� �������� ");
    }
}

////////////// ������� ��� ���� ����  //////////////

// �������� ���� ���� � ��������� ���� ������� ����� � ������� ������
void Widget::menuCreation()
{
    // ����� ������ ������� �����
    masT = new QLineEdit * [9];

    // ����� ������ ������� �������
    masClean = new QLineEdit * [9];

    // �� �� ����� ������ & ������� ������� �����������
    for(int i=0; i < 9; i++)
    {
        // ����� ������
        masClean[i] = new  QLineEdit[9];
        masT[i] = new QLineEdit[9];

        // ������� ������� �����������
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

    // �������� ���������� ������� ������
    itemPalStart = masT[0][0].palette();
    itemPalStart.setColor(QPalette::Base, QColor(250,250,250));
    itemPalStart.setColor(QPalette::Text, QColor(0,0,0));

    // ������� ������� ��� readOnly �����
    itemPalReadOnly = masT[0][0].palette();
    itemPalReadOnly.setColor(QPalette::Text, QColor(100,100,100) );

    // ������� ������� ��� readOnly �������� �����
    itemPalBedReadOnly = masT[0][0].palette();
    itemPalBedReadOnly.setColor(QPalette::Background, QColor(255,20,147));
    itemPalBedReadOnly.setColor(QPalette::Shadow, QColor(255,20,147));
    itemPalBedReadOnly.setColor(QPalette::Window, QColor(255,20,147));

    // ������� ������� ��� ������� �������� �����
    itemPalBedBase = masT[0][0].palette();
    itemPalBedBase.setColor(QPalette::Text, QColor(255,20,147));

    // ��������� ����������� ������ �� ������ & �������� ���������� & �������� ������� ��������� �����
    for (int stroka = 0 ; stroka < 9; stroka++)
    {
        for(int stolb = 0 ; stolb < 9; stolb++ )
        {
            // ��������� ������������ ����� ������
            masT[stroka][stolb].setMaxLength(1);

            // ��������� ����������� ������ �� ������
            masT[stroka][stolb].setAlignment(Qt::AlignCenter);
            masClean[stroka][stolb].setAlignment(Qt::AlignCenter);

            // �������� ����������
            masT[stroka][stolb].setValidator(val);
            masClean[stroka][stolb].setValidator(val);

            // �������� ������� ��������� �����
            connect(&masT[stroka][stolb], SIGNAL( textChanged(const QString &)),this, SLOT(tableChanged()));
        }
    }

    // ��������� ������������� ������� ����� ����������
    myNewSave->setFixedSize(305,60);
    this->setFixedSize(445,491);

    // ������� ����
    // ���� ��� ������
    QMenuBar * menuBar = new QMenuBar(this);

    // ���� ����
    QMenu * fileMenu = new QMenu("����");

    // ���� ���������
    parametrMenu = new QMenu("���������");


    // ���� ����� ����
    QMenu * newGameMenu = new QMenu("������ ����� ����");
    gameModeSoEasy = newGameMenu->addAction("����� ������", this,SLOT(newGame_VeryEasy()) );
    gameModeEasy =  newGameMenu->addAction("������", this, SLOT(newGame_Easy()));
    gameModeNormal = newGameMenu->addAction("�������", this, SLOT(newGame_Normal()));
    gameModeHard = newGameMenu->addAction("�������", this, SLOT(newGame_Hard()));
    gameModeSoHard = newGameMenu->addAction("����� ������� ", this, SLOT(newGame_VeryHard()));
    // ������� ���� ������ ���� ����
    fileMenu->addMenu(newGameMenu);

    // ��������� ����
    openFiles = fileMenu->addAction(QPixmap(":/icons/openIcon"),"������� ����",this,SLOT(loadGame()), Qt::CTRL + Qt::Key_O );

    // ���������� ��������
    fileMenu ->addSeparator();

    // ��������� ����
    saveFile = fileMenu->addAction(QPixmap(":/icons/saving"),"��������� ����", this ,SLOT(saveGame()),Qt::CTRL + Qt::Key_S);

    // ��������� ���� ���
    saveFileHow = fileMenu->addAction("��������� ���� ���...", this ,SLOT(saveGameHow()),Qt::CTRL + Qt::SHIFT + Qt::Key_S);

    // ���������� ��������
    fileMenu ->addSeparator();

    // ������� �������
    cleanTFile = fileMenu->addAction("�������� ����������� ������",this,SLOT(cleanTable()));

    // ���������� ��������
    fileMenu ->addSeparator();

    // �����
    fileMenu->addAction("�����", this, SLOT(close()),Qt::CTRL + Qt::Key_Q );

    // �������� ���� � ���
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(parametrMenu); // ���� ����������

    // ������ ��� ������ ������� ���� ������� � ����������
    cleanTFile->setEnabled(false);
    saveFile->setEnabled(false);
    saveFileHow->setEnabled(false);
}
// ������� �������� ����� ������ ( ���������� ����� �������� )
int Widget::loadGame()
{
    // ���������� ����� �������� ���� , ��� ��� ������
    myNewOpen->move(this->x() + 30 ,this->y() + 60);

    // �������� ���� �� ���� ������ ���
    if(!QFile(QApplication::applicationDirPath()+"/data" + "/" + "Tables").open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this,"�������� ����", "� ��� ��� �� ����� ���������� ����");
        return 1; // ������
    }

    // �������� �������� ���� ��� �������� ����������
    QFile vrem(QApplication::applicationDirPath()+"/data" + "/" + "Tables");

    if(vrem.open(QIODevice::ReadOnly)) //��������� ��� ������
    {
        // ������� ����� � ����������� ����� �� �������� ����
        QTextStream in(&vrem);

        // ��������� ������ ��� ������ ����� �����
        QString line;

        // ���������� ����� � �����
        int lineCount = 0 ;

        // ������� ���������� ������������ � ������
        int colRaz = 0;

        // ��������� ���������� ����� � �����
        do
        {
            // ������� ����������� ������ �����
            line = in.readLine();

            // ������� �������
            colRaz = 0;
            for(int i = 0; i < line.size(); i++ )
            {
                if(line[i]=='|')  colRaz++;// ���������� �������� ���������� � ������
            }

            // ������ �� ������� � ����� ��� ����������
            if(!line.isNull() && colRaz == 2)lineCount++; // �������� ������� �����

        }
        while (!line.isNull()); // ���� �� ����� �� ������ ������

        // ���� ���� ����
        if(!lineCount)
        {
            QMessageBox::information(this,"�������� ����", "� ��� ��� �� ����� ���������� ����");
            return 1; // ������
        }
    }
    else
    {
        QMessageBox::information(this,"�������� ����", "� ��� ��� �� ����� ���������� ����");
        return 1; // ������
    }

    // ������� ������� ������� ( ����� ��� ������ �������� )
    this->refreshTable(); // signal connected to void DialogOpen::startTable()

    //  ��������� ����� � ���� ������, ����������� ���������� ����� ��������)
    // ������ ������ �������
    if(myNewOpen->exec() == QDialog::Accepted)
    {
        // ������ ����� ������� ������� ����
        for (int stroka = 0 ; stroka < 9; stroka++)
            for(int stolb = 0 ; stolb < 9; stolb++ )
                masT[stroka][stolb].clearFocus();

        QMessageBox::information(this,"��������", "������� ���� � ������:\n"  + gameName );
        // ������ ����� ������� ( qmessagebox ��� ����������,� ����� ����� �������� � ��������� �����)
        for (int stroka = 0 ; stroka < 9; stroka++)
            for(int stolb = 0 ; stolb < 9; stolb++ )
                masT[stroka][stolb].clearFocus();


        return 0 ;
    }

    // ������ ������ ������
    else
    {
        return 1; // ������
    }
}
// ������� ���������� ����������
int Widget::saveGame()
{
    // ����� ��� ���
    if(!isNamed)
    {
        if(!saveGameHow()) return 0; // ���� � ��������� ��� ������ ��
        else return 1 ; // �������� ����������
    }

    // ��� ��� ����
    else
    {
        savingGame(gameName);
        // ������ ������ ����������
        saveFile->setEnabled(false);
        return 0; // ���������
    }
}
// ������� �������� ����� ���������� ���
int Widget::saveGameHow()
{
    // ���������� ����� ���������� ���� , ��� ��� ������
    myNewSave->move(this->x() + 30 ,this->y() + 60);

    // ������ ������ ��������� ( ��������� ����� � ���� ������, ����������� ���������� ����� ����������)
    if(myNewSave->exec() == QDialog::Accepted)
    {
        QMessageBox::information(this,"����������", "���� ��������� ��� ������:\n"  + gameName );

        // ������ ���������
        isSaved = true;

        // ������ �������
        isNamed = true;

        // ������ ������ ����������
        saveFile->setEnabled(false);

        return 0 ;
    }

    // ������ ������ ������
    else
    {
        return 1;
    }
}
// ������� ������� �������
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

    // ������� ������� ������� ��� ��� ������
    cleanTFile->setEnabled(false);
}
// ������� �������� ���������
void Widget::closeEvent(QCloseEvent *event)
{
    // ��������� ��
    bool ignored = false;

    // event =  ������� �� ������ ��������
    // ���� ������� ������� �� �� �������
    if( isCreated && !isNamed)
    {
        // ����� ������������
        int answer  =  QMessageBox::question(this,"������","������ ��������� ��� ����?", "��", "���", "������") ;

        // ��, ���������
        if(answer == 0 )
        {
            // ������� ����� ����������
            // ���� ��������
            if(saveGameHow())
            {
                ignored = true; // ���, �� ���������
            }
        }
        // ������
        if( answer == 2 )
        {
            ignored = true; // ���, �� ���������
        }
    }

    // ������� ������� � �������, �� �� ���������
    if(isCreated && isNamed && !isSaved )
    {
        // ����� ������������
        int answer  =  QMessageBox::question(this,"������","������ ��������� ��������� � ����\n" + gameName + " ?", "���������", "�� ���������", "������") ;

        // ��, ���������
        if(answer == 0 )
        {
            // ���� �������� ������ ����� ����������
            if(saveGame()) // ������������ ������
            {
                ignored = true;
            }
            ignored = false;
        }

        // ���, �� ���������
        if ( answer  == 1 )
        {
            ignored = false;
        }

        // ������
        if( answer == 2 )
        {
            ignored = true; // ���, �� ���������
        }
    }

    // ���� ��������� ���������� , �� ������ ������
    if(!ignored)
    {
        //// �������� ������ ��� ��� ���
        //��������������� ������ ����� �� ���������� � ��������� ����������� � �������
        // ����� ���� ��� | ���� ��������
        delete gameModeHelp ;
        // ����� ���� ����� �������
        delete gameModeSoEasy;
        // ����� ���� �������
        delete gameModeEasy;
        // ����� ���� ����� ����������
        delete gameModeNormal;
        // ����� ���� �������
        delete gameModeHard;
        // ����� ���� ����� �������
        delete gameModeSoHard;
        // ��������� ����
        delete openFiles;
        // ��������� ����
        delete saveFile;
        // ��������� ���� ���
        delete saveFileHow;
        // ������� �������
        delete cleanTFile;
        // ������ ������ �� ���������
        delete val;
        // ������� ������ ����� �������
        for(int stroka = 0 ;stroka < 9 ; stroka++) delete[] masT[stroka];
        delete[] masT;
        // ������� ������ ��� ��������������
        for(int stroka = 0 ;stroka < 9 ; stroka++) delete[] masClean[stroka];
        delete[] masClean;

        event->accept(); // �� ��������� (������ ���� true)
    }

    // ���� �� ���������
    else
    {
        event->ignore(); // ������ ���� false ( �� �� ��������� )
    }
}

///////////// ������ ������� ���� ��� ���� ����  //////////////

// ������� ����� ������ ����
void Widget::newGame_VeryEasy()
{
    //���� ���������� ���� ���������� ������� ���� �� ��������
    if(isCreated)
    {
        // ���� ���������� ���� �� ��������� , ������� �� ���� �� ���������
        if(!isSaved)
        {
            // ����� ������������
            int answer = 2; // ������ �� ���������

            // ���� ���������� ���� �� �������
            if(!isNamed)
            {
                // ����� ������������
                answer  =  QMessageBox::question(this,"������","������ ��������� ��� ����?", "��", "���", "������") ;

                // ��, ���������
                if(answer == 0 )
                {
                    // ������� ����� ����������
                    // ���� �������� ������ ����� ����������
                    if(saveGame())
                    {
                        return; // ���, �� ��������� ����� ����
                    }
                }

                // ������
                if( answer == 2 )
                {
                    return;
                }
            }
            // ���� ���������� ���� �������
            else
            {
                // ����� ������������
                answer  =  QMessageBox::question(this,"������","������ ��������� ��������� � ����\n" + gameName + " ?", "���������", "�� ���������", "������") ;

                // ��, ���������
                if(answer == 0 )
                {
                    // ������� ����� ����������
                    // ���� �������� ������ ����� ����������
                    if(saveGame())
                    {
                        return; // ���, �� ��������� ����� ����
                    }
                }

                // ������
                if( answer == 2 )
                {
                    return;
                }
            }
        }
    }

    ui->lblLevel->setText("������� ���������:  ����� ������");
    level = 1;
    newGame();
}
// ������� ������ ����
void Widget::newGame_Easy()
{
    //���� ���������� ���� ���������� ������� ���� �� ��������
    if(isCreated)
    {
        // ���� ���������� ���� �� ��������� , ������� �� ���� �� ���������
        if(!isSaved)
        {
            // ����� ������������
            int answer = 2; // ������ �� ���������

            // ���� ���������� ���� �� �������
            if(!isNamed)
            {
                // ����� ������������
                answer  =  QMessageBox::question(this,"������","������ ��������� ��� ����?", "��", "���", "������") ;

                // ��, ���������
                if(answer == 0 )
                {
                    // ������� ����� ����������
                    // ���� �������� ������ ����� ����������
                    if(saveGame())
                    {
                        return; // ���, �� ��������� ����� ����
                    }
                }

                // ������
                if( answer == 2 )
                {
                    return;
                }
            }
            // ���� ���������� ���� �������
            else
            {
                // ����� ������������
                answer  =  QMessageBox::question(this,"������","������ ��������� ��������� � ����\n" + gameName + " ?", "���������", "�� ���������", "������") ;

                // ��, ���������
                if(answer == 0 )
                {
                    // ������� ����� ����������
                    // ���� �������� ������ ����� ����������
                    if(saveGame())
                    {
                        return; // ���, �� ��������� ����� ����
                    }
                }

                // ������
                if( answer == 2 )
                {
                    return;
                }
            }
        }
    }

    ui->lblLevel->setText("������� ���������:     ������");
    level = 3;
    newGame();
}
// ������� ���������� ����
void Widget::newGame_Normal()
{
    //���� ���������� ���� ���������� ������� ���� �� ��������
    if(isCreated)
    {
        // ���� ���������� ���� �� ��������� , ������� �� ���� �� ���������
        if(!isSaved)
        {
            // ����� ������������
            int answer = 2; // ������ �� ���������

            // ���� ���������� ���� �� �������
            if(!isNamed)
            {
                // ����� ������������
                answer  =  QMessageBox::question(this,"������","������ ��������� ��� ����?", "��", "���", "������") ;

                // ��, ���������
                if(answer == 0 )
                {
                    // ������� ����� ����������
                    // ���� �������� ������ ����� ����������
                    if(saveGame())
                    {
                        return; // ���, �� ��������� ����� ����
                    }
                }

                // ������
                if( answer == 2 )
                {
                    return;
                }
            }
            // ���� ���������� ���� �������
            else
            {
                // ����� ������������
                answer  =  QMessageBox::question(this,"������","������ ��������� ��������� � ����\n" + gameName + " ?", "���������", "�� ���������", "������") ;

                // ��, ���������
                if(answer == 0 )
                {
                    // ������� ����� ����������
                    // ���� �������� ������ ����� ����������
                    if(saveGame())
                    {
                        return; // ���, �� ��������� ����� ����
                    }
                }

                // ������
                if( answer == 2 )
                {
                    return;
                }
            }
        }
    }

    ui->lblLevel->setText("������� ���������:     �������");
    level = 5;
    newGame();
}
// ������� ������� ����
void Widget::newGame_Hard()
{
    //���� ���������� ���� ���������� ������� ���� �� ��������
    if(isCreated)
    {
        // ���� ���������� ���� �� ��������� , ������� �� ���� �� ���������
        if(!isSaved)
        {
            // ����� ������������
            int answer = 2; // ������ �� ���������

            // ���� ���������� ���� �� �������
            if(!isNamed)
            {
                // ����� ������������
                answer  =  QMessageBox::question(this,"������","������ ��������� ��� ����?", "��", "���", "������") ;

                // ��, ���������
                if(answer == 0 )
                {
                    // ������� ����� ����������
                    // ���� �������� ������ ����� ����������
                    if(saveGame())
                    {
                        return; // ���, �� ��������� ����� ����
                    }
                }

                // ������
                if( answer == 2 )
                {
                    return;
                }
            }
            // ���� ���������� ���� �������
            else
            {
                // ����� ������������
                answer  =  QMessageBox::question(this,"������","������ ��������� ��������� � ����\n" + gameName + " ?", "���������", "�� ���������", "������") ;

                // ��, ���������
                if(answer == 0 )
                {
                    // ������� ����� ����������
                    // ���� �������� ������ ����� ����������
                    if(saveGame())
                    {
                        return; // ���, �� ��������� ����� ����
                    }
                }

                // ������
                if( answer == 2 )
                {
                    return;
                }
            }
        }
    }

    ui->lblLevel->setText("������� ���������:     �������");
    level = 6;
    newGame();
}
// ������� ����� ������� ����
void Widget::newGame_VeryHard()
{
    //���� ���������� ���� ���������� ������� ���� �� ��������
    if(isCreated)
    {
        // ���� ���������� ���� �� ��������� , ������� �� ���� �� ���������
        if(!isSaved)
        {
            // ����� ������������
            int answer = 2; // ������ �� ���������

            // ���� ���������� ���� �� �������
            if(!isNamed)
            {
                // ����� ������������
                answer  =  QMessageBox::question(this,"������","������ ��������� ��� ����?", "��", "���", "������") ;

                // ��, ���������
                if(answer == 0 )
                {
                    // ������� ����� ����������
                    // ���� �������� ������ ����� ����������
                    if(saveGame())
                    {
                        return; // ���, �� ��������� ����� ����
                    }
                }

                // ������
                if( answer == 2 )
                {
                    return;
                }
            }
            // ���� ���������� ���� �������
            else
            {
                // ����� ������������
                answer  =  QMessageBox::question(this,"������","������ ��������� ��������� � ����\n" + gameName + " ?", "���������", "�� ���������", "������") ;

                // ��, ���������
                if(answer == 0 )
                {
                    // ������� ����� ����������
                    // ���� �������� ������ ����� ����������
                    if(saveGame())
                    {
                        return; // ���, �� ��������� ����� ����
                    }
                }

                // ������
                if( answer == 2 )
                {
                    return;
                }
            }
        }
    }

    ui->lblLevel->setText("������� ���������: ����� �������");
    level = 7;
    newGame();

}
// ��������� ������� ���� � ����������� | ���
void Widget::gameModeHelpChanged()
{
    if(gameModeHelp->isChecked()) // �������� ������� , �������� ���
    {
        tableChanged();
    }
    else // ���� �������� �������� ������ ��� ������� � �����
    {
        for (int stroka = 0 ; stroka < 9; stroka++)
        {
            for(int stolb = 0 ; stolb < 9; stolb++ )
            {
                if(! masT[stroka][stolb].isEnabled())  masT[stroka][stolb].setPalette(itemPalReadOnly);  // ������� ��� readOnly
                else masT[stroka][stolb].setPalette(itemPalStart); // ������� ��� �������
            }
        }
    }
}

////////////// ������� ������ � �������� //////////////

// ������� �������� "���������" �������
void Widget::toStartTable()
{
    // �������� ����� ������������ �������
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
// ������� �������� ����� � �������
void Widget::itemAdding()
{
    // �������� ������ � �������
    int table = 0;
    int strokaT = -1 ;
    int stolbT = -1;
    for (int stroka = 0 ; stroka < 9; stroka++) // �� ������� ������� �������
    {
        for(int stolb = 0 ; stolb < 9; stolb++ ) // �� �������� ������� �������
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
                QMessageBox::information(this,"������", "� ������� �������� �����");
                break;
            }
            }
        }
    }
}
// ������� ���������������� �������
void Widget::transposing()
{
    int temp;
    for (int stroka = 0 ; stroka < 8; stroka++) // 8 ������ ��� ����� ������ �� ��������� ������ ��� �� ���� ����� ������ �������������
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
            QMessageBox::information(this,"������", "� ������� ����������������");
            break;
        }
        }
    }
}
// ������� ������ ����� � �������� ������ ������ ( 3 � 9 )
void Widget::swapRowsSmall()
{
    // ����� ��� ����� ������ ������
    int area = 0;
    // ����� ������� ����� ������
    int line_1 = 0;
    int line_2 = 0;

    // ������ ��� ����������� �����
    int  temp [9];

    // �������� ���� ���
    for(int razPeremesh = 0;  razPeremesh < 5;  razPeremesh ++ )
    {
        // ������ ����� ��� ����� ������ ������
        area = rand() % 3;

        // ������ ����� ������� ����� ������
        line_1 = rand() % 3;
        line_2 = rand() % 3;
        while (line_1 == line_2) { line_2 = rand() % 3;} // ���� �� ������������ ���� � ��� ��

        // �������� �� �������
        for( int stolb = 0 ; stolb < 9; stolb++ )
        {
            temp[stolb] =  masT[area * 3 + line_1][stolb].text().toInt();
            masT[area * 3 + line_1][stolb].setText(masT[area* 3 + line_2][stolb].text());
            masT[area* 3 + line_2][stolb].setText(QString::number(temp[stolb]));
        }
    }
}
// ������� ������ �������� � �������� ������ ������ ( 9 � 3 )
void Widget::swapColumsSmall()
{
    // ����� ��� ����� ������ �������
    int area = 0;
    // ����� ������� ����� ������
    int column_1 = 0;
    int column_2 = 0;

    // ������ ��� ����������� ��������
    int  temp [9];

    // �������� ���� ���
    for(int razPeremesh = 0;  razPeremesh < 5;  razPeremesh ++ )
    {
        // ������ ����� ��� ����� ������ �������
        area = rand() % 3;

        // ������ ����� ������� ����� ������
        column_1 = rand() % 3;
        column_2 = rand() % 3;
        while (column_1 == column_2) { column_2 = rand() % 3;}

        // �������� �� �������
        for (int stroka = 0 ; stroka < 9; stroka++)
        {
            temp[stroka] =  masT[stroka][area * 3 + column_1].text().toInt();
            masT[stroka][area * 3 + column_1].setText(masT[stroka][area* 3 + column_2].text());
            masT[stroka][area* 3 + column_2].setText(QString::number(temp[stroka]));
        }
    }
}
// ������� ������ ������� �� �����������
void Widget::swapRowsArea()
{
    // ������ ����� ������ ����� ������
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
// ������� ������ ������� �� ���������
void Widget::swapColumsArea()
{
    // ������ ����� ������ ����� ������ (0/1/2)
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
// ������� ������������� �������
void Widget::shuffle()
{
    // ����������
    // � ������� ����������������
    // ������ ����� � ��������
    // ������ ������� �� �������� � ���������

    // � ������� ������:
    //transposing();
    //swapRowsSmall();
    //swapColumsSmall();
    //swapRowsArea();
    //swapColumsArea();

    // ��������� ��������������� ������ ������� �������������
    int masS[5] = {1,2,3,4,5}; // ������ ��� switch
    int temp; // ���������� ��� ��������������
    int j; // ����� ������ , ������ �������������

    // �������� ������ � �������
    for(int razPeremesh = 0;  razPeremesh < 3;  razPeremesh ++ )
    {
        // �������� ������
        for (int i = 4  ; i >= 1  ; i-- )
        {
            j = rand() % (i); // ������� �� ������� ����� ����� ��������
            temp = masS[j];
            masS[j] = masS[i];
            masS[i] = temp;
        }

        // �������� �������
        for(int i = 0; i < 5; i ++ )
        {
            switch (masS[i])
            {
            case 1:
            {
                // ������� ���������������� �������
                transposing();
                break;
            }
            case 2:
            {
                // ������� ������ ����� � �������� ������ ������ ( 3 � 9 )
                swapRowsSmall();
                break;
            }
            case 3:
            {
                // ������� ������ �������� � �������� ������ ������ ( 9 � 3 )
                swapColumsSmall();
                break;
            }
            case 4:
            {
                // ������� ������ ������� �� �����������
                swapRowsArea();
                break;
            }
            case 5:
            {
                // ������� ������ ������� �� ���������
                swapColumsArea();
                break;
            }
            default:
            {
                QMessageBox::information(this,"������", "� ������� shuffle");
                break;
            }
            }
        }
    }
}
