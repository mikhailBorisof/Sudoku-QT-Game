/********************************************************************************
** Form generated from reading UI file 'dialogopen.ui'
**
** Created: Tue 10. Aug 01:12:23 2021
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGOPEN_H
#define UI_DIALOGOPEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogOpen
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTableWidget *table;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnDelete;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOpen;
    QPushButton *btnCancel;

    void setupUi(QDialog *DialogOpen)
    {
        if (DialogOpen->objectName().isEmpty())
            DialogOpen->setObjectName(QString::fromUtf8("DialogOpen"));
        DialogOpen->resize(464, 386);
        DialogOpen->setMinimumSize(QSize(464, 386));
        DialogOpen->setMaximumSize(QSize(464, 386));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/cat"), QSize(), QIcon::Normal, QIcon::Off);
        DialogOpen->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(DialogOpen);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        table = new QTableWidget(DialogOpen);
        table->setObjectName(QString::fromUtf8("table"));

        verticalLayout->addWidget(table);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnDelete = new QPushButton(DialogOpen);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));

        horizontalLayout->addWidget(btnDelete);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOpen = new QPushButton(DialogOpen);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));

        horizontalLayout->addWidget(btnOpen);

        btnCancel = new QPushButton(DialogOpen);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setEnabled(true);

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(DialogOpen);

        QMetaObject::connectSlotsByName(DialogOpen);
    } // setupUi

    void retranslateUi(QDialog *DialogOpen)
    {
        DialogOpen->setWindowTitle(QApplication::translate("DialogOpen", "\320\236\321\202\320\272\321\200\321\213\321\202\320\270\320\265", 0, QApplication::UnicodeUTF8));
        btnDelete->setText(QApplication::translate("DialogOpen", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\270\320\263\321\200\321\203", 0, QApplication::UnicodeUTF8));
        btnOpen->setText(QApplication::translate("DialogOpen", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("DialogOpen", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogOpen: public Ui_DialogOpen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGOPEN_H
