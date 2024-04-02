#include "dialogopen.h"  // ������������ ���� ������ ����� ��������
#include "ui_dialogopen.h" // ���� ����� ���� ��������

// ����������� �����
DialogOpen::DialogOpen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOpen)
{
    ui->setupUi(this);
    // ������ ������ ��������
    connect(ui->btnCancel,SIGNAL(clicked()),SLOT(reject())); // ������� �����������, ��� ���������, ���� ������ cancel

    // ������� ������ ������� ������ � ����� ������������ ������ ������
    connect(ui->table,SIGNAL(itemSelectionChanged()),this,SLOT(itemSelected()));
}
// ���������� �����
DialogOpen::~DialogOpen()
{
    delete ui;
}
// ������� ������ ����� ��������
void DialogOpen::showEvent(QShowEvent *)
{
    // ���� ����� ��� �������� ����� ����� ��� �� ������ ������
    ui->btnDelete->setFocusPolicy(Qt::NoFocus);
    ui->table->setFocusPolicy(Qt::NoFocus);
    ui->btnOpen->setFocusPolicy(Qt::NoFocus);
    ui->btnCancel->setFocusPolicy( Qt::TabFocus);

}
// ��������� ��������� ������
void DialogOpen::itemSelected()
{
    // selectionModel - ����� ������� ��������� �������� �������
    // ���� ���-�� � ������� �������
    if(ui->table->selectionModel()->hasSelection())
    {
        // ������ ����� ��������� ������
        // selectedIndexes ���������� ������� ��������� ,
        //��� ��� � ����� ������� ������ ���� ����� ������� ������� ������ ������� ������
        // selectedIndexes ���������� ������� ���������
        selectedRow = ui->table->selectionModel()->selectedIndexes().first().row() ;

        // ������� ��� ������������ ������ �������� � ��������
        ui->btnDelete->setEnabled(true);
        ui->btnOpen->setEnabled(true);
    }
    else
    {
        // �� ��������� ��� ������������ ������ �������� � ��������
        ui->btnDelete->setEnabled(false);
        ui->btnOpen->setEnabled(false);
    }
}
// ��������� ������� ��� �������� �������
void DialogOpen::startTable()
{
    // ������ ������� � ������� ������ �� ���������
    ui->btnOpen->setEnabled(false);
    ui->btnDelete->setEnabled(false);

    // ������ ���� ������� ������� ����� �������
    ui->table->setSelectionMode(QAbstractItemView::SingleSelection);

    // ������������� ��������� ������ ��� ��������� ������ ( �������� ��� ������ , � ������� ���������� ������)
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);

    // ������� ���������� ��������� , ���� ��� ����
    ui->table->clearSelection();

    // ������� ����� ������ file ��� ������������� ����� � ������ ������
    fileT = new QFile(QApplication::applicationDirPath()+"/data" + "/" + "Tables");

    if(fileT->open(QIODevice::ReadOnly)) //��������� ��� ������
    {
        // ������� ����� � ����������� ����� �� �������� ����
        QTextStream in(fileT);

        // ������� ������ ����� , ���� ����� ���������� ����� �������� �����
        QStringList *tableF;

        // ��������� ������ ��� ������ ����� �����
        QString line;

        // ���������� ����� � �����
        lineCount = 0 ;

        // ����� ������ �����, ���� ����� ���������� ������ �� �����
        tableF = new QStringList();

        // ������� ���������� ���������� � ������
        int colRaz = 0;

        // ��������� ���������� ����� � ����� � ������� ���������� ������
        do
        {
            // ������� ����������� ������ �����
            line = in.readLine();
            //������� �������
            colRaz = 0;
            // ��������� ���������� ���������� � ������
            for(int i = 0; i < line.size(); i++)
            {
                if(line[i]=='|')  colRaz++;// ���������� �������� ���������� � ������ �����
            }

            // ������ �� ������� � ����� ��� ����������
            if(!line.isNull() && colRaz == 2)
            {
                // ��������� � ������ | split ��������� ������ �� list �����
                tableF->append( line.split("|") );
            }
        }
        while (!line.isNull());// ���� �� ����� �� ������ ������

        // ����� ������, ��� ������ ���� �� ���������� ����� � ������
        lineCount = tableF->size()/3;

        // ���� �� ������
        if(lineCount)
        {
            // ����� ������ ������� �����
            masLabel = new QLabel* [lineCount];

            ui->table->setRowCount(lineCount ); // ������������� ���-�� �����
            ui->table->setColumnCount(3); // ������������� ���-�� ��������

            // �������� ������ ������ �������� � �����
            ui->table->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
            ui->table->verticalHeader()->setResizeMode(QHeaderView::Fixed);

            // ������� ������� �������
            QStringList name_table;
            name_table << "�������� " << "���������" << "����";
            ui->table->setHorizontalHeaderLabels(name_table);

            // ����� ������
            for(int i = 0; i < lineCount; i++)
            {
                masLabel[i] = new QLabel[3];
            }

            // ������� ���� ������
            QPalette myPalette = masLabel[0][0].palette();
            myPalette.setColor(QPalette::Text, QColor(0,0,0));

            // ����� ������� �����
            for(int stroka = 0 ; stroka < lineCount ; stroka ++ )
            {
                for(int stolb = 0 ; stolb < 3; stolb++)
                {
                    ui->table->setCellWidget(stroka,stolb,&masLabel[stroka][stolb]); // �������� ������� � �������
                    masLabel[stroka][stolb].setEnabled(false); // ������ ����������� ����� ������
                    masLabel[stroka][stolb].setAlignment(Qt::AlignCenter); // ����� �� ������ ������
                    masLabel[stroka][stolb].setPalette(myPalette); // ������� ���� ������
                }

                masLabel[stroka][0].setFixedWidth(250);
                masLabel[stroka][1].setFixedWidth(120);
                masLabel[stroka][2].setFixedWidth(140);
            }

            // ��������� ��������� �������� �� ������
            ui->table->setColumnWidth( 0, 250 );
            ui->table->setColumnWidth( 1, 120 );
            ui->table->setColumnWidth( 2, 140 );

            // ��������� ������ ������ �� �����
            for(int stroka = 0 ; stroka < lineCount ; stroka ++ )
            {
                // ���� � ������ ���-�� ����
                for(int stolb = 0 ; stolb < 3; stolb++)
                {
                    // ����� ���������� ������� ������� ( ����� ������� ��������� )
                    if(stolb != 1) masLabel[stroka][stolb].setText(tableF->at(stolb+(stroka*3)));
                    // ��� ������� ���������
                    else
                    {
                        if(tableF->at(stolb+(stroka*3)).toInt() == 1) masLabel[stroka][stolb].setText("����� ������");
                        if(tableF->at(stolb+(stroka*3)).toInt() == 3) masLabel[stroka][stolb].setText("������");
                        if(tableF->at(stolb+(stroka*3)).toInt() == 5) masLabel[stroka][stolb].setText("�������");
                        if(tableF->at(stolb+(stroka*3)).toInt() == 6) masLabel[stroka][stolb].setText("�������");
                        if(tableF->at(stolb+(stroka*3)).toInt() == 7) masLabel[stroka][stolb].setText("����� �������");
                    }
                }
            }

            // ������� ��
            // ������ ��������� �� ����
            delete tableF;
            // ������� ����
            fileT->close();
            // ������ ��������� �� ����
            delete fileT;
        }

        // ���� ������
        else
        {
            // ������ ���� �������� ����
            this->hide();
            // ������� ����������� � �������� ����
            this->on_btnCancel_clicked();
            // �������� ������������, ��� ���������� ��� ���
            QMessageBox::information(this,"�������� ����", "� ��� ��� �� ����� ���������� ����");
            // ������� ����
            fileT->close();
            // ������ ��������� �� ����
            delete fileT;
        }
    }
    else
    {
        QMessageBox::information(this,"�������� ����", "� ��� ��� �� ����� ���������� ����");
        // ������ ��������� �� ����
        delete fileT;
    }
}
// ������� �� ������ ������
void DialogOpen::on_btnCancel_clicked()
{
    // ������ ������ , ���� ��� ��������� ������ ����� ����� ���� �������� �����
    for(int stroka = 0 ;stroka < lineCount ; stroka++) delete[] masLabel[stroka];
    delete[] masLabel;
    // ������� �����������, ��� ���������, ���� ������ cancel
    this->reject();
}
// ������� �� ������ �������
void DialogOpen::on_btnOpen_clicked()
{
    // �������� ����� �������, ������� ������� �������
    sendItem(masLabel[selectedRow][0].text());

    // ������ ������ , ���� ��� ��������� ������ ����� ����� ���� �������� �����
    for(int stroka = 0 ;stroka < lineCount ; stroka++) delete[] masLabel[stroka];
    delete[] masLabel;

    // ������� �����������, ��� �������
    this->accept();
}
// ������� �� ������ ��������
void DialogOpen::on_btnDelete_clicked()
{
    // lineCount ��� ������� / rowCount ��� �������
    // ������ ���� �������
    QString name = masLabel[selectedRow][0].text();
    QFile(QApplication::applicationDirPath()+"/data" + "/" + masLabel[selectedRow][0].text() ).remove();

    // ����� ������ ������� �������� ����� ������
    QLabel** masCopy = new QLabel* [lineCount-1];
    // ����� ������
    for(int i=0; i < lineCount-1 ; i++) // �� �� ���� ������ ������ ������� ��-�� ��������� ������
    {
        masCopy[i] = new QLabel[3];
    }
    // �������� ���� ������� � ����� ������
    for(int stroka = 0 ; stroka < lineCount ; stroka ++ ) // ����� ��������� ������
    {
        for(int stolb = 0 ; stolb < 3; stolb++)
        {
            if(stroka < selectedRow)
            {
                masCopy[stroka][stolb].setText(masLabel[stroka][stolb].text());
            }

            if(stroka > selectedRow)
            {
                // ��� ������� ���������� �� ����
                masCopy[stroka-1][stolb].setText(masLabel[stroka][stolb].text());
            }
        }
    }

    // ������ ������� � ������ ������� ����� �������� ( �� �� ���� ������ ������)
    for(int stroka = 0 ;stroka < lineCount ; stroka++) delete[] masLabel[stroka];
    delete[] masLabel;

    // �������� �� ���-�� � �������
    if(ui->table->rowCount()-1 != 0 )
    {
        // ����� ������ ������ ������� �����
        masLabel = new QLabel* [ui->table->rowCount()-1];
        // ����� ������
        for(int i = 0; i < ui->table->rowCount()-1; i++) masLabel[i] = new QLabel[3];

        // ������� ���� ������
        QPalette myPalette = masLabel[0][0].palette();
        myPalette.setColor(QPalette::Text, QColor(0,0,0));

        // �������� ������ ������� ��������
        for(int stroka = 0 ; stroka < lineCount-1 ; stroka ++ )
        {
            for(int stolb = 0 ; stolb < 3; stolb++)
            {
                masLabel[stroka][stolb].setText(masCopy[stroka][stolb].text()); // ������� � ������ ��� �� �������� , ��� ��������
                ui->table->setCellWidget(stroka,stolb,&masLabel[stroka][stolb]); // �������� ����� ������� � �������
                masLabel[stroka][stolb].setEnabled(false); // ������ ����������� ����� ������
                masLabel[stroka][stolb].setAlignment(Qt::AlignCenter); // ����� �� ������ ������
                masLabel[stroka][stolb].setPalette(myPalette); // ������� ���� ������
            }
        }
        // ������ ������ , ���� ��� ��������� ������ ����� ����� ���� �������� �����
        for(int stroka = 0 ;stroka < lineCount-1 ; stroka++) delete[] masCopy[stroka];
        delete[] masCopy;

        ///////////////////////////////////////////////////////////////////////////////////////////
        // ������ ������� �� ����� ���� ���

        // ������� ������ �� ����� ������ file ��� ������������� ����� � ������ ������
        fileT = new QFile(QApplication::applicationDirPath()+"/data" + "/" + "Tables");

        // �������� ���� ��� ��������������
        QFile vrem(QApplication::applicationDirPath()+"/data" + "/" + "Vremen");
        vrem.open(QIODevice::WriteOnly); // ������� ��� ����������

        // ��������� �� ��� ������ ��� ��������������
        QTextStream* from;
        QTextStream* to;

        // ������ ��� ������ �� ������
        QString line;

        if(fileT->open(QIODevice::ReadOnly)) //��������� ��� ������
        {
            // ������� ������ � ����������� ����� �� �������� �����
            from = new QTextStream(fileT);
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

                    // ���� ��� �� �� ������, ��� �� ������� ������� � � ����
                    if(strSrav != name) (*to) << line << "\n" ;
                }
            }
            while (!line.isNull()); // ���� �� ������ �� ������ ������ � ������

            // ������� �����
            fileT->close();
            vrem.close();

            // ������� ���� Tables � �������
            fileT->open(QIODevice::WriteOnly);
            fileT->close();

            /////////////////////////////////////////
            //������� ���������� ����

            // ������� ������ ����
            fileT->open(QIODevice::WriteOnly);
            // ������� ��������� ���� � ���������� ��������
            vrem.open(QIODevice::ReadOnly); // ������� ��� ������

            // ������� ������ � ����������� ����� �� �������� �����
            from = new QTextStream(&vrem);
            to = new QTextStream(fileT);

            // ����������� �� ������ � �����
            QString line2;
            do
            {
                line2 = from->readLine();
                (*to) << line2 << "\n";
            }
            while (!line2.isNull());

            // ������� �����
            fileT->close();
            vrem.close();

            // ������ ������ �� ������ ������
            delete from;
            delete to;

            // ������ ��������� ����
            vrem.remove();

            // ������ ��������� �� ����
            delete fileT;

            // ���������� ����� �����
            lineCount = lineCount - 1;

            // ���������� ����� ����� � �������
            ui->table->setRowCount(lineCount);

            // ������ ���������
            ui->table->clearSelection();

        }
        // �� ��������
        else
        {
            QMessageBox::information(this,"�������� ����", "�� ������� ������� ���� ������");
        }
    }
    // ���� ������ � ������� �� ��������
    else
    {
        // ������� ������ �� ����� ������ file ��� ������������� ����� � ������ ������
        fileT = new QFile(QApplication::applicationDirPath()+"/data" + "/" + "Tables");
        if(fileT->open(QIODevice::WriteOnly))
        {
            // ������� ���� � ������� ����
            fileT->close();

            // ������ ��������� �� ������ �����������
            delete[] masCopy;
            // ������ ��������� � ��������� ������
            ui->table->setRowCount(0);

            // ������� �����������, ��� ���������, ���� ������ cancel
            this->reject();

            // ������ , ��� ������ �� ��������
            QMessageBox::information(this,"�������� ����", "� ��� ��� �� ����� ���������� ����");
        }
        // �� ��������
        else
        {
            QMessageBox::information(this,"�������� ����", "�� ������� ������� ���� ������");
        }
    }
}
