/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton_2;
    QWidget *page_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(692, 650);
        MainWindow->setMinimumSize(QSize(692, 650));
        MainWindow->setMaximumSize(QSize(692, 650));
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/startMeniu.png);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 692, 650));
        page = new QWidget();
        page->setObjectName("page");
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(270, 360, 151, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("SimSun")});
        font.setPointSize(21);
        font.setBold(true);
        pushButton_2->setFont(font);
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/background.png);\n"
"color: rgb(0, 0, 0);"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        pushButton_3 = new QPushButton(page_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(270, 310, 151, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("SimSun")});
        font1.setPointSize(18);
        font1.setBold(true);
        pushButton_3->setFont(font1);
        pushButton_3->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_3->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/background.png);\n"
"color: rgb(0, 0, 0);\n"
""));
        pushButton_4 = new QPushButton(page_2);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(270, 400, 151, 61));
        pushButton_4->setFont(font1);
        pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/background.png);\n"
"color: rgb(0, 0, 0);"));
        stackedWidget->addWidget(page_2);
        pushButton_4->raise();
        pushButton_3->raise();
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "TRIVIADOR", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PLAY", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "LOG IN", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "SIGN UP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
