/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogIn
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *l_username;
    QLineEdit *l_password;
    QFrame *frame;

    void setupUi(QWidget *LogIn)
    {
        if (LogIn->objectName().isEmpty())
            LogIn->setObjectName("LogIn");
        LogIn->resize(506, 341);
        LogIn->setMinimumSize(QSize(506, 341));
        LogIn->setMaximumSize(QSize(506, 341));
        pushButton = new QPushButton(LogIn);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(130, 230, 101, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("SimSun")});
        font.setPointSize(11);
        pushButton->setFont(font);
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2 = new QPushButton(LogIn);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(280, 230, 101, 51));
        pushButton_2->setFont(font);
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        label = new QLabel(LogIn);
        label->setObjectName("label");
        label->setGeometry(QRect(110, 80, 101, 20));
        label->setStyleSheet(QString::fromUtf8("font: 700 11pt \"SimSun\";\n"
"background-color: rgba(148,188,138,255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        label_2 = new QLabel(LogIn);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 140, 101, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 11pt \"SimSun\";\n"
"background-color: rgba(148,188,138,255);\n"
"color: rgb(0, 0, 0);\n"
""));
        l_username = new QLineEdit(LogIn);
        l_username->setObjectName("l_username");
        l_username->setGeometry(QRect(230, 70, 191, 28));
        l_password = new QLineEdit(LogIn);
        l_password->setObjectName("l_password");
        l_password->setGeometry(QRect(230, 130, 191, 28));
        frame = new QFrame(LogIn);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(-11, -1, 531, 351));
        frame->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/signInBack.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        pushButton->raise();
        pushButton_2->raise();
        label->raise();
        label_2->raise();
        l_username->raise();
        l_password->raise();

        retranslateUi(LogIn);

        QMetaObject::connectSlotsByName(LogIn);
    } // setupUi

    void retranslateUi(QWidget *LogIn)
    {
        LogIn->setWindowTitle(QCoreApplication::translate("LogIn", "LOG IN", nullptr));
        pushButton->setText(QCoreApplication::translate("LogIn", "ENTER", nullptr));
        pushButton_2->setText(QCoreApplication::translate("LogIn", "SIGN UP", nullptr));
        label->setText(QCoreApplication::translate("LogIn", "Username : ", nullptr));
        label_2->setText(QCoreApplication::translate("LogIn", "Password : ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogIn: public Ui_LogIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
