/********************************************************************************
** Form generated from reading UI file 'dialogsave.ui'
**
** Created: Sun 12. Sep 01:25:13 2021
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSAVE_H
#define UI_DIALOGSAVE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSave
{
public:
    QPushButton *btnSave;
    QPushButton *btnCancel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *lblName;
    QLineEdit *txtName;

    void setupUi(QDialog *DialogSave)
    {
        if (DialogSave->objectName().isEmpty())
            DialogSave->setObjectName(QString::fromUtf8("DialogSave"));
        DialogSave->resize(370, 63);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/cat"), QSize(), QIcon::Normal, QIcon::Off);
        DialogSave->setWindowIcon(icon);
        btnSave = new QPushButton(DialogSave);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(130, 30, 75, 23));
        btnSave->setFocusPolicy(Qt::ClickFocus);
        btnCancel = new QPushButton(DialogSave);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(220, 30, 75, 23));
        btnCancel->setFocusPolicy(Qt::NoFocus);
        layoutWidget = new QWidget(DialogSave);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 284, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lblName = new QLabel(layoutWidget);
        lblName->setObjectName(QString::fromUtf8("lblName"));

        horizontalLayout->addWidget(lblName);

        txtName = new QLineEdit(layoutWidget);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setMinimumSize(QSize(225, 0));
        txtName->setMaximumSize(QSize(225, 16777215));
        txtName->setFocusPolicy(Qt::StrongFocus);
        txtName->setMaxLength(25);

        horizontalLayout->addWidget(txtName);


        retranslateUi(DialogSave);

        QMetaObject::connectSlotsByName(DialogSave);
    } // setupUi

    void retranslateUi(QDialog *DialogSave)
    {
        DialogSave->setWindowTitle(QApplication::translate("DialogSave", "\320\241\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("DialogSave", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("DialogSave", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("DialogSave", "\320\230\320\274\321\217 \320\270\320\263\321\200\321\213:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogSave: public Ui_DialogSave {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSAVE_H
