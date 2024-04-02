#include "dialogsave.h" // ������������ ���� ������ ����� ����������
#include "ui_dialogsave.h" // ���� ����� ���� ����������

// ����������� �����
DialogSave::DialogSave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSave)
{
    ui->setupUi(this);
    // ��������� ��� lineEdit
    ui->txtName->setToolTip("��� �� ������ ����� ����� ����� 25 ������\n� ��������� ��������� ��������: <>:\"|?*/");
    // �������� ������, �����������, ��� ������ ����� ��������� � ���������� ���� ������
    ui->txtName->setCursor(Qt::IBeamCursor);
}
// ���������� �����
DialogSave::~DialogSave()
{
    delete ui;
}
// ������� ������ ����� ����������
void DialogSave::showEvent(QShowEvent *)
{
    // ��� ������ �� ������ ������ , ���� �� ����� ��������� ������
    ui->btnCancel->setFocusPolicy( Qt::NoFocus);
    // ��������� ����� ������ ����
    ui->btnSave->setFocusPolicy(Qt::ClickFocus);
    // ������, ���� ����� ����� ���� �������� � ����
    ui->txtName->setFocusPolicy( Qt::StrongFocus);
}
// ������ �� ������ ���������
void DialogSave::on_btnSave_clicked()
{
    bool clear = true; // ������ ������ � �� ����� ����������

    // ������ = �����
    if( ui->txtName->text().isEmpty())
    {
        clear = false; // ������ �� ������
        QMessageBox::warning(this,"����������", "������ ���� ���� ������ ��� ");
    }

    // ��� ��������������� ��������
    if(1 == isLegalFileName(ui->txtName->text()) && clear)
    {
        clear = false; // ������ �� ������
        QMessageBox::warning(this,"����������",
                             ui->txtName->text() + "\n��� ��� ��������������� ��� ������������� ������������ ��������.\n�������� ������ ��� � ��������� �������.");
    }

    // ������������ �������
    if(2 == isLegalFileName(ui->txtName->text()) && clear)
    {
        clear = false;
        QMessageBox::warning(this,"����������", ui->txtName->text() + "\n������������ ��� ����" );
    }

    // ���� ����� ���� ��� ����
    if(clear  && QFile::QFile(QApplication::applicationDirPath()+"/data" + "/" + ui->txtName->text()).exists())
    {
        clear = false;
        QMessageBox::warning(this,"����������", "���� � ����� ������ ��� ����������. ������� ������ ���" );


        ui->txtName->setSelection(0,ui->txtName->text().length()); // ��������� ������ ���������
    }

    // ������ �� ������
    if(!clear)  // ��������� ������ ���������
        ui->txtName->setSelection(0,ui->txtName->text().length());

    // ������ ������
    if( clear)
    {
        emit sendData(ui->txtName->text()); // ���������� ������
        // emit ���������� � ������ �� ������
        // �� ����������� ��������� ��� ������������, �  ���, ��� ��� ������ ������������ ����-��
        // void Widget::savingGame(QString fileName) <- ���� ����������

        ui->txtName->setText("");
        this->accept(); // ������� �����������, ��� �������
    }
}
// ������ �� ������ ������
void DialogSave::on_btnCancel_clicked()
{
    // ������� ������, ����� �������
    ui->txtName->clear();

    // ������� �����������, ��� ���������
    this->reject();
}
// ������� �������� ����� ����� �� ���������������� �����/���� � WINDOWS
int DialogSave::isLegalFileName(QString name)
{
    // c����� ������������ ��������
    QString illegal = "<>:\"|?*/" ;
    // ������������������ ������� ���������
    QString reserved_device_names [24] =
    {
        "CON" , "PRN" , "AUX" , "NUL" , "COM0" , "COM1" , "COM2" , "COM3"
        , "COM4" , "COM5" , "COM6" , "COM7" , "COM8" , "COM9" , "LPT0" ,"LPT1"
        , "LPT2" , "LPT3" ,  "LPT4" , "LPT5" , "LPT6" , "LPT7" , "LPT8" , "LPT9"
    };
    // ����������
    /*
      ����������� ����� �������������
    �������� ����������� ������������ � ����� �����.
    ��� ����� �� ������ ��������� �<� (���� ������),
     �>� (���� ������), �:� (���������), ���
    (������� �������), �/� (����), �\� (�������� ����),
    �|� (������������ �����), �?� (�������������� ����),
    �*� (���������), � ����� �� ����� ������������� ������ ��� ��������.
     ����� ����� ������ �������� ������������������ ������� ���������

    � ������ ��������� � ������ �� ������
    ����������� ������� ASCII, ���������
    �������� ������� �������� � �������� 1-31,
    � ����� ����� �� ������������� ���� ��������:
    "<>:\"|?*"
    */

    for(int c = 0 ; c < name.length() ; c++)
    {
        // �������� ������� ����������� ��������
        if(name[c].toAscii() > 0 && name[c].toAscii() < 32 )  return 2; // ������������ �������

        // �������� ������� ����������� ��������
        if(illegal.contains(name[c])) return 2; // ������������ �������
    }

    for(int c = 0 ; c < 24 ; c++)
    {
        // ������� ������ ��� ����� ��������
        if(name.contains(reserved_device_names[c],Qt::CaseInsensitive) ) return 1; // ��� ��� ��������������� ��� ������������� ������������ ��������.\n �������� ������ ��� � ��������� �������.
        if(name.contains("\\",Qt::CaseInsensitive)) return 2; // ������������ �������
    }

    // �������� ������� ����������� ����� ��� ��������
    if ( name.right(1) == "." || name.right (1)==" " )
        return 2;// ���������� ���������, ���������� n ������� ������ �������� ������

    return 0;  // ��� �� ������� ������
}
