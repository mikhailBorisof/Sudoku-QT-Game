/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Tue 14. Sep 05:38:33 2021
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTableWidget *table_1;
    QFrame *lineVFirst;
    QFrame *lineVSecond;
    QFrame *lineHSecond;
    QFrame *lineHFirst;
    QTableWidget *table_2;
    QTableWidget *table_3;
    QTableWidget *table_4;
    QTableWidget *table_5;
    QTableWidget *table_6;
    QTableWidget *table_7;
    QTableWidget *table_8;
    QTableWidget *table_9;
    QLabel *lblLevel;
    QWidget *layoutWidget;
    QVBoxLayout *vLayoutHello;
    QLabel *lblHello;
    QLabel *lblName;
    QLabel *lblVibor;
    QPushButton *btnSoEasy;
    QPushButton *btnEasy;
    QPushButton *btnNormal;
    QPushButton *btnHard;
    QPushButton *btnSoHard;
    QFrame *lineHButton;
    QPushButton *btnOpen;
    QWidget *layoutWidget1;
    QHBoxLayout *hLayoutName;
    QLabel *lblGameName;
    QLineEdit *txtGameName;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(445, 491);
        Widget->setMaximumSize(QSize(900, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/cat"), QSize(), QIcon::Normal, QIcon::Off);
        Widget->setWindowIcon(icon);
        table_1 = new QTableWidget(Widget);
        if (table_1->columnCount() < 3)
            table_1->setColumnCount(3);
        if (table_1->rowCount() < 3)
            table_1->setRowCount(3);
        table_1->setObjectName(QString::fromUtf8("table_1"));
        table_1->setGeometry(QRect(30, 30, 125, 125));
        table_1->setMinimumSize(QSize(120, 120));
        table_1->setMaximumSize(QSize(1200, 1200));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        table_1->setFont(font);
        table_1->setFocusPolicy(Qt::NoFocus);
        table_1->setLayoutDirection(Qt::LeftToRight);
        table_1->setFrameShape(QFrame::NoFrame);
        table_1->setFrameShadow(QFrame::Plain);
        table_1->setLineWidth(6);
        table_1->setMidLineWidth(6);
        table_1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_1->setShowGrid(true);
        table_1->setGridStyle(Qt::SolidLine);
        table_1->setSortingEnabled(true);
        table_1->setRowCount(3);
        table_1->setColumnCount(3);
        table_1->horizontalHeader()->setVisible(false);
        table_1->horizontalHeader()->setHighlightSections(false);
        table_1->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        table_1->verticalHeader()->setVisible(false);
        table_1->verticalHeader()->setHighlightSections(false);
        lineVFirst = new QFrame(Widget);
        lineVFirst->setObjectName(QString::fromUtf8("lineVFirst"));
        lineVFirst->setGeometry(QRect(155, 30, 3, 383));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lineVFirst->setFont(font1);
        lineVFirst->setFrameShadow(QFrame::Plain);
        lineVFirst->setLineWidth(3);
        lineVFirst->setFrameShape(QFrame::VLine);
        lineVSecond = new QFrame(Widget);
        lineVSecond->setObjectName(QString::fromUtf8("lineVSecond"));
        lineVSecond->setGeometry(QRect(288, 30, 3, 383));
        lineVSecond->setFont(font1);
        lineVSecond->setFrameShadow(QFrame::Plain);
        lineVSecond->setLineWidth(3);
        lineVSecond->setFrameShape(QFrame::VLine);
        lineHSecond = new QFrame(Widget);
        lineHSecond->setObjectName(QString::fromUtf8("lineHSecond"));
        lineHSecond->setGeometry(QRect(30, 288, 383, 3));
        lineHSecond->setFrameShadow(QFrame::Plain);
        lineHSecond->setLineWidth(3);
        lineHSecond->setFrameShape(QFrame::HLine);
        lineHFirst = new QFrame(Widget);
        lineHFirst->setObjectName(QString::fromUtf8("lineHFirst"));
        lineHFirst->setGeometry(QRect(30, 155, 383, 3));
        lineHFirst->setFrameShadow(QFrame::Plain);
        lineHFirst->setLineWidth(3);
        lineHFirst->setFrameShape(QFrame::HLine);
        table_2 = new QTableWidget(Widget);
        if (table_2->columnCount() < 3)
            table_2->setColumnCount(3);
        if (table_2->rowCount() < 3)
            table_2->setRowCount(3);
        table_2->setObjectName(QString::fromUtf8("table_2"));
        table_2->setGeometry(QRect(163, 30, 125, 125));
        table_2->setMinimumSize(QSize(120, 120));
        table_2->setMaximumSize(QSize(1200, 1200));
        table_2->setFont(font);
        table_2->setFocusPolicy(Qt::NoFocus);
        table_2->setFrameShape(QFrame::NoFrame);
        table_2->setFrameShadow(QFrame::Plain);
        table_2->setLineWidth(6);
        table_2->setMidLineWidth(6);
        table_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_2->setShowGrid(true);
        table_2->setGridStyle(Qt::SolidLine);
        table_2->setSortingEnabled(true);
        table_2->setRowCount(3);
        table_2->setColumnCount(3);
        table_2->horizontalHeader()->setVisible(false);
        table_2->horizontalHeader()->setHighlightSections(false);
        table_2->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        table_2->verticalHeader()->setVisible(false);
        table_2->verticalHeader()->setHighlightSections(false);
        table_3 = new QTableWidget(Widget);
        if (table_3->columnCount() < 3)
            table_3->setColumnCount(3);
        if (table_3->rowCount() < 3)
            table_3->setRowCount(3);
        table_3->setObjectName(QString::fromUtf8("table_3"));
        table_3->setGeometry(QRect(293, 30, 125, 125));
        table_3->setMinimumSize(QSize(120, 120));
        table_3->setMaximumSize(QSize(1200, 1200));
        table_3->setFont(font);
        table_3->setFocusPolicy(Qt::NoFocus);
        table_3->setFrameShape(QFrame::NoFrame);
        table_3->setFrameShadow(QFrame::Plain);
        table_3->setLineWidth(6);
        table_3->setMidLineWidth(6);
        table_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_3->setShowGrid(true);
        table_3->setGridStyle(Qt::SolidLine);
        table_3->setSortingEnabled(true);
        table_3->setRowCount(3);
        table_3->setColumnCount(3);
        table_3->horizontalHeader()->setVisible(false);
        table_3->horizontalHeader()->setHighlightSections(false);
        table_3->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        table_3->verticalHeader()->setVisible(false);
        table_3->verticalHeader()->setHighlightSections(false);
        table_4 = new QTableWidget(Widget);
        if (table_4->columnCount() < 3)
            table_4->setColumnCount(3);
        if (table_4->rowCount() < 3)
            table_4->setRowCount(3);
        table_4->setObjectName(QString::fromUtf8("table_4"));
        table_4->setGeometry(QRect(30, 163, 125, 125));
        table_4->setMinimumSize(QSize(120, 120));
        table_4->setMaximumSize(QSize(1200, 1200));
        table_4->setFont(font);
        table_4->setFocusPolicy(Qt::NoFocus);
        table_4->setFrameShape(QFrame::NoFrame);
        table_4->setFrameShadow(QFrame::Plain);
        table_4->setLineWidth(6);
        table_4->setMidLineWidth(6);
        table_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_4->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_4->setShowGrid(true);
        table_4->setGridStyle(Qt::SolidLine);
        table_4->setSortingEnabled(true);
        table_4->setRowCount(3);
        table_4->setColumnCount(3);
        table_4->horizontalHeader()->setVisible(false);
        table_4->horizontalHeader()->setHighlightSections(false);
        table_4->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        table_4->verticalHeader()->setVisible(false);
        table_4->verticalHeader()->setHighlightSections(false);
        table_5 = new QTableWidget(Widget);
        if (table_5->columnCount() < 3)
            table_5->setColumnCount(3);
        if (table_5->rowCount() < 3)
            table_5->setRowCount(3);
        table_5->setObjectName(QString::fromUtf8("table_5"));
        table_5->setGeometry(QRect(163, 163, 125, 125));
        table_5->setMinimumSize(QSize(120, 120));
        table_5->setMaximumSize(QSize(1200, 1200));
        table_5->setFont(font);
        table_5->setFocusPolicy(Qt::NoFocus);
        table_5->setFrameShape(QFrame::NoFrame);
        table_5->setFrameShadow(QFrame::Plain);
        table_5->setLineWidth(6);
        table_5->setMidLineWidth(6);
        table_5->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_5->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_5->setShowGrid(true);
        table_5->setGridStyle(Qt::SolidLine);
        table_5->setSortingEnabled(true);
        table_5->setRowCount(3);
        table_5->setColumnCount(3);
        table_5->horizontalHeader()->setVisible(false);
        table_5->horizontalHeader()->setHighlightSections(false);
        table_5->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        table_5->verticalHeader()->setVisible(false);
        table_5->verticalHeader()->setHighlightSections(false);
        table_6 = new QTableWidget(Widget);
        if (table_6->columnCount() < 3)
            table_6->setColumnCount(3);
        if (table_6->rowCount() < 3)
            table_6->setRowCount(3);
        table_6->setObjectName(QString::fromUtf8("table_6"));
        table_6->setGeometry(QRect(293, 163, 125, 125));
        table_6->setMinimumSize(QSize(120, 120));
        table_6->setMaximumSize(QSize(1200, 1200));
        table_6->setFont(font);
        table_6->setFocusPolicy(Qt::NoFocus);
        table_6->setFrameShape(QFrame::NoFrame);
        table_6->setFrameShadow(QFrame::Plain);
        table_6->setLineWidth(6);
        table_6->setMidLineWidth(6);
        table_6->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_6->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_6->setShowGrid(true);
        table_6->setGridStyle(Qt::SolidLine);
        table_6->setSortingEnabled(true);
        table_6->setRowCount(3);
        table_6->setColumnCount(3);
        table_6->horizontalHeader()->setVisible(false);
        table_6->horizontalHeader()->setHighlightSections(false);
        table_6->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        table_6->verticalHeader()->setVisible(false);
        table_6->verticalHeader()->setHighlightSections(false);
        table_7 = new QTableWidget(Widget);
        if (table_7->columnCount() < 3)
            table_7->setColumnCount(3);
        if (table_7->rowCount() < 3)
            table_7->setRowCount(3);
        table_7->setObjectName(QString::fromUtf8("table_7"));
        table_7->setGeometry(QRect(30, 293, 125, 125));
        table_7->setMinimumSize(QSize(120, 120));
        table_7->setMaximumSize(QSize(1200, 1200));
        table_7->setFont(font);
        table_7->setFocusPolicy(Qt::NoFocus);
        table_7->setFrameShape(QFrame::NoFrame);
        table_7->setFrameShadow(QFrame::Plain);
        table_7->setLineWidth(6);
        table_7->setMidLineWidth(6);
        table_7->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_7->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_7->setShowGrid(true);
        table_7->setGridStyle(Qt::SolidLine);
        table_7->setSortingEnabled(true);
        table_7->setRowCount(3);
        table_7->setColumnCount(3);
        table_7->horizontalHeader()->setVisible(false);
        table_7->horizontalHeader()->setHighlightSections(false);
        table_7->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        table_7->verticalHeader()->setVisible(false);
        table_7->verticalHeader()->setHighlightSections(false);
        table_8 = new QTableWidget(Widget);
        if (table_8->columnCount() < 3)
            table_8->setColumnCount(3);
        if (table_8->rowCount() < 3)
            table_8->setRowCount(3);
        table_8->setObjectName(QString::fromUtf8("table_8"));
        table_8->setGeometry(QRect(163, 293, 125, 125));
        table_8->setMinimumSize(QSize(120, 120));
        table_8->setMaximumSize(QSize(1200, 1200));
        table_8->setFont(font);
        table_8->setFocusPolicy(Qt::NoFocus);
        table_8->setFrameShape(QFrame::NoFrame);
        table_8->setFrameShadow(QFrame::Plain);
        table_8->setLineWidth(6);
        table_8->setMidLineWidth(6);
        table_8->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_8->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_8->setShowGrid(true);
        table_8->setGridStyle(Qt::SolidLine);
        table_8->setSortingEnabled(true);
        table_8->setRowCount(3);
        table_8->setColumnCount(3);
        table_8->horizontalHeader()->setVisible(false);
        table_8->horizontalHeader()->setHighlightSections(false);
        table_8->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        table_8->verticalHeader()->setVisible(false);
        table_8->verticalHeader()->setHighlightSections(false);
        table_9 = new QTableWidget(Widget);
        if (table_9->columnCount() < 3)
            table_9->setColumnCount(3);
        if (table_9->rowCount() < 3)
            table_9->setRowCount(3);
        table_9->setObjectName(QString::fromUtf8("table_9"));
        table_9->setGeometry(QRect(293, 293, 125, 125));
        table_9->setMinimumSize(QSize(120, 120));
        table_9->setMaximumSize(QSize(1200, 1200));
        table_9->setFont(font);
        table_9->setFocusPolicy(Qt::NoFocus);
        table_9->setFrameShape(QFrame::NoFrame);
        table_9->setFrameShadow(QFrame::Plain);
        table_9->setLineWidth(6);
        table_9->setMidLineWidth(6);
        table_9->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_9->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_9->setShowGrid(true);
        table_9->setGridStyle(Qt::SolidLine);
        table_9->setSortingEnabled(true);
        table_9->setRowCount(3);
        table_9->setColumnCount(3);
        table_9->horizontalHeader()->setVisible(false);
        table_9->horizontalHeader()->setHighlightSections(false);
        table_9->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        table_9->verticalHeader()->setVisible(false);
        table_9->verticalHeader()->setHighlightSections(false);
        lblLevel = new QLabel(Widget);
        lblLevel->setObjectName(QString::fromUtf8("lblLevel"));
        lblLevel->setGeometry(QRect(210, 0, 231, 16));
        QFont font2;
        font2.setPointSize(10);
        lblLevel->setFont(font2);
        lblLevel->setFrameShape(QFrame::Box);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 411, 341));
        vLayoutHello = new QVBoxLayout(layoutWidget);
        vLayoutHello->setSpacing(6);
        vLayoutHello->setContentsMargins(11, 11, 11, 11);
        vLayoutHello->setObjectName(QString::fromUtf8("vLayoutHello"));
        vLayoutHello->setContentsMargins(0, 0, 0, 0);
        lblHello = new QLabel(layoutWidget);
        lblHello->setObjectName(QString::fromUtf8("lblHello"));
        QFont font3;
        font3.setPointSize(25);
        font3.setBold(true);
        font3.setWeight(75);
        lblHello->setFont(font3);
        lblHello->setAlignment(Qt::AlignCenter);

        vLayoutHello->addWidget(lblHello);

        lblName = new QLabel(layoutWidget);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setFont(font3);
        lblName->setAlignment(Qt::AlignCenter);

        vLayoutHello->addWidget(lblName);

        lblVibor = new QLabel(layoutWidget);
        lblVibor->setObjectName(QString::fromUtf8("lblVibor"));
        QFont font4;
        font4.setPointSize(13);
        lblVibor->setFont(font4);
        lblVibor->setAlignment(Qt::AlignCenter);

        vLayoutHello->addWidget(lblVibor);

        btnSoEasy = new QPushButton(layoutWidget);
        btnSoEasy->setObjectName(QString::fromUtf8("btnSoEasy"));

        vLayoutHello->addWidget(btnSoEasy);

        btnEasy = new QPushButton(layoutWidget);
        btnEasy->setObjectName(QString::fromUtf8("btnEasy"));

        vLayoutHello->addWidget(btnEasy);

        btnNormal = new QPushButton(layoutWidget);
        btnNormal->setObjectName(QString::fromUtf8("btnNormal"));

        vLayoutHello->addWidget(btnNormal);

        btnHard = new QPushButton(layoutWidget);
        btnHard->setObjectName(QString::fromUtf8("btnHard"));

        vLayoutHello->addWidget(btnHard);

        btnSoHard = new QPushButton(layoutWidget);
        btnSoHard->setObjectName(QString::fromUtf8("btnSoHard"));

        vLayoutHello->addWidget(btnSoHard);

        lineHButton = new QFrame(layoutWidget);
        lineHButton->setObjectName(QString::fromUtf8("lineHButton"));
        lineHButton->setFont(font1);
        lineHButton->setFrameShadow(QFrame::Plain);
        lineHButton->setLineWidth(3);
        lineHButton->setFrameShape(QFrame::HLine);

        vLayoutHello->addWidget(lineHButton);

        btnOpen = new QPushButton(layoutWidget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));

        vLayoutHello->addWidget(btnOpen);

        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 430, 261, 22));
        hLayoutName = new QHBoxLayout(layoutWidget1);
        hLayoutName->setSpacing(6);
        hLayoutName->setContentsMargins(11, 11, 11, 11);
        hLayoutName->setObjectName(QString::fromUtf8("hLayoutName"));
        hLayoutName->setContentsMargins(0, 0, 0, 0);
        lblGameName = new QLabel(layoutWidget1);
        lblGameName->setObjectName(QString::fromUtf8("lblGameName"));

        hLayoutName->addWidget(lblGameName);

        txtGameName = new QLineEdit(layoutWidget1);
        txtGameName->setObjectName(QString::fromUtf8("txtGameName"));
        txtGameName->setEnabled(false);
        txtGameName->setMinimumSize(QSize(225, 20));
        txtGameName->setMaximumSize(QSize(225, 20));
        txtGameName->setMaxLength(25);
        txtGameName->setAlignment(Qt::AlignCenter);

        hLayoutName->addWidget(txtGameName);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Sudoku", 0, QApplication::UnicodeUTF8));
        lblLevel->setText(QApplication::translate("Widget", "\320\243\321\200\320\276\320\262\320\265\320\275\321\214:", 0, QApplication::UnicodeUTF8));
        lblHello->setText(QApplication::translate("Widget", "\320\224\320\276\320\261\321\200\320\276 \320\277\320\276\320\266\320\260\320\273\320\276\320\262\320\260\321\202\321\214 ", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("Widget", "\320\222 \320\270\320\263\321\200\321\203 \320\241\321\203\320\264\320\276\320\272\321\203", 0, QApplication::UnicodeUTF8));
        lblVibor->setText(QApplication::translate("Widget", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265 \321\203\321\200\320\276\320\262\320\265\320\275\321\214 \321\201\320\273\320\276\320\266\320\275\320\276\321\201\321\202\320\270 :", 0, QApplication::UnicodeUTF8));
        btnSoEasy->setText(QApplication::translate("Widget", "\320\236\321\207\320\265\320\275\321\214 \320\273\320\265\320\263\320\272\320\270\320\271 ", 0, QApplication::UnicodeUTF8));
        btnEasy->setText(QApplication::translate("Widget", "\320\233\320\265\320\263\320\272\320\270\320\271 ", 0, QApplication::UnicodeUTF8));
        btnNormal->setText(QApplication::translate("Widget", "\320\241\321\200\320\265\320\264\320\275\320\270\320\271", 0, QApplication::UnicodeUTF8));
        btnHard->setText(QApplication::translate("Widget", "\320\241\320\273\320\276\320\266\320\275\321\213\320\271", 0, QApplication::UnicodeUTF8));
        btnSoHard->setText(QApplication::translate("Widget", "\320\236\321\207\320\265\320\275\321\214 \321\201\320\273\320\276\320\266\320\275\321\213\320\271", 0, QApplication::UnicodeUTF8));
        btnOpen->setText(QApplication::translate("Widget", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\201\320\276\321\205\321\200\320\260\320\275\320\275\321\221\320\275\321\203\321\216 \320\270\320\263\321\200\321\203", 0, QApplication::UnicodeUTF8));
        lblGameName->setText(QApplication::translate("Widget", "\320\230\320\263\321\200\320\260:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
