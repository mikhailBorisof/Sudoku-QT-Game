#include "dialogsave.h" // заголовочный файл класса формы сохранения
#include "ui_dialogsave.h" // файл формы окна сохранения

// конструктор формы
DialogSave::DialogSave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSave)
{
    ui->setupUi(this);
    // подсказка под lineEdit
    ui->txtName->setToolTip("Имя не должно иметь длину более 25 знаков\nи содержать следующих символов: <>:\"|?*/");
    // изменить курсор, указывающий, что виджет может принимать и отображать ввод текста
    ui->txtName->setCursor(Qt::IBeamCursor);
}
// деструктор формы
DialogSave::~DialogSave()
{
    delete ui;
}
// событие показа формы сохранения
void DialogSave::showEvent(QShowEvent *)
{
    // без фокуса на кнопку отмена , чтоб не сбило остальные фокусы
    ui->btnCancel->setFocusPolicy( Qt::NoFocus);
    // принимает фокус щелчка мыши
    ui->btnSave->setFocusPolicy(Qt::ClickFocus);
    // делает, чтоб сразу можно было печатать в поле
    ui->txtName->setFocusPolicy( Qt::StrongFocus);
}
// нажали на кнопку сохранить
void DialogSave::on_btnSave_clicked()
{
    bool clear = true; // строка хороша и ее можно отправлять

    // пустая = плохо
    if( ui->txtName->text().isEmpty())
    {
        clear = false; // строка не хороша
        QMessageBox::warning(this,"Сохранение", "Нельзя дать игре пустое имя ");
    }

    // имя зарезервировано системой
    if(1 == isLegalFileName(ui->txtName->text()) && clear)
    {
        clear = false; // строка не хороша
        QMessageBox::warning(this,"Сохранение",
                             ui->txtName->text() + "\nЭто имя зарезервировано для использования операционной системой.\nВыберите другое имя и повторите попытку.");
    }

    // недопустимые символы
    if(2 == isLegalFileName(ui->txtName->text()) && clear)
    {
        clear = false;
        QMessageBox::warning(this,"Сохранение", ui->txtName->text() + "\nНедопустимое имя игры" );
    }

    // если такой файл уже есть
    if(clear  && QFile::QFile(QApplication::applicationDirPath()+"/data" + "/" + ui->txtName->text()).exists())
    {
        clear = false;
        QMessageBox::warning(this,"Сохранение", "Игра с таким именем уже существует. Введите другое имя" );


        ui->txtName->setSelection(0,ui->txtName->text().length()); // выделаяет строку введенную
    }

    // строка не хороша
    if(!clear)  // выделаяет строку введенную
        ui->txtName->setSelection(0,ui->txtName->text().length());

    // строка хороша
    if( clear)
    {
        emit sendData(ui->txtName->text()); // отправляем строку
        // emit опционален и ничего не значит
        // за исключением подсказки для разработчика, о  том, что это сигнал отправленный куда-то
        // void Widget::savingGame(QString fileName) <- сюда отправляет

        ui->txtName->setText("");
        this->accept(); // говорим модальности, что приняли
    }
}
// нажали на кнопку отмена
void DialogSave::on_btnCancel_clicked()
{
    // очистим строку, перед отменой
    ui->txtName->clear();

    // говорим модальности, что отклонили
    this->reject();
}
// функция проверки имени файла на соответствование имени/пути в WINDOWS
int DialogSave::isLegalFileName(QString name)
{
    // cтрока недопустимых символов
    QString illegal = "<>:\"|?*/" ;
    // зарезервированными именами устройств
    QString reserved_device_names [24] =
    {
        "CON" , "PRN" , "AUX" , "NUL" , "COM0" , "COM1" , "COM2" , "COM3"
        , "COM4" , "COM5" , "COM6" , "COM7" , "COM8" , "COM9" , "LPT0" ,"LPT1"
        , "LPT2" , "LPT3" ,  "LPT4" , "LPT5" , "LPT6" , "LPT7" , "LPT8" , "LPT9"
    };
    // обьяснение
    /*
      Большинство часто употребляемых
    символов разрешается использовать в имени файла.
    Имя файла не должно содержать „<” (знак меньше),
     „>” (знак больше), „:” (двоеточие), „«”
    (двойные кавычки), „/” (слеш), „\” (обратный слеш),
    „|” (вертикальная черта), „?” (вопросительный знак),
    „*” (звездочка), а также не может заканчиваться точкой или пробелом.
     Файлы также нельзя называть зарезервированными именами устройств

    В именах каталогов и файлов не должны
    встречаться символы ASCII, численные
    значения которых попадают в интервал 1-31,
    а также любой из перечисленных ниже символов:
    "<>:\"|?*"
    */

    for(int c = 0 ; c < name.length() ; c++)
    {
        // проверим наличие контрольных символов
        if(name[c].toAscii() > 0 && name[c].toAscii() < 32 )  return 2; // недопустимые символы

        // проверим наличие контрольных символов
        if(illegal.contains(name[c])) return 2; // недопустимые символы
    }

    for(int c = 0 ; c < 24 ; c++)
    {
        // наличие строки без учета регистра
        if(name.contains(reserved_device_names[c],Qt::CaseInsensitive) ) return 1; // это имя зарезервировано для использования операционной системой.\n Выберите другое имя и повторите попытку.
        if(name.contains("\\",Qt::CaseInsensitive)) return 2; // недопустимые символы
    }

    // Проверка наличия завершающих точек или пробелов
    if ( name.right(1) == "." || name.right (1)==" " )
        return 2;// Возвращает подстроку, содержащую n крайних правых символов строки

    return 0;  // все ок хорошая строка
}
