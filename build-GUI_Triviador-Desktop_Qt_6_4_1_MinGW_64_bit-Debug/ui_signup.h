/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUp
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *s_username;
    QLineEdit *s_password;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *s_name;
    QLineEdit *s_confirmPassword;
    QLabel *label_4;
    QFrame *frame;

    void setupUi(QWidget *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName("SignUp");
        SignUp->resize(506, 341);
        SignUp->setMinimumSize(QSize(506, 341));
        SignUp->setMaximumSize(QSize(506, 341));
        SignUp->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(SignUp);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 60, 161, 18));
        label->setStyleSheet(QString::fromUtf8("font: 700 11pt \"SimSun\";\n"
"background-color: rgba(148,188,138,255);\n"
"color: rgb(0, 0, 0);\n"
""));
        label_2 = new QLabel(SignUp);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 100, 161, 18));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 11pt \"SimSun\";\n"
"background-color: rgba(148,188,138,255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
""));
        label_3 = new QLabel(SignUp);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 140, 161, 18));
        label_3->setStyleSheet(QString::fromUtf8("font: 700 11pt \"SimSun\";\n"
"background-color: rgba(148,188,138,255);\n"
"color: rgb(0, 0, 0);\n"
""));
        s_username = new QLineEdit(SignUp);
        s_username->setObjectName("s_username");
        s_username->setGeometry(QRect(270, 90, 191, 28));
        s_password = new QLineEdit(SignUp);
        s_password->setObjectName("s_password");
        s_password->setGeometry(QRect(270, 130, 191, 28));
        pushButton = new QPushButton(SignUp);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(130, 250, 101, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("SimSun")});
        font.setPointSize(11);
        pushButton->setFont(font);
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2 = new QPushButton(SignUp);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(290, 250, 101, 51));
        pushButton_2->setFont(font);
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        s_name = new QLineEdit(SignUp);
        s_name->setObjectName("s_name");
        s_name->setGeometry(QRect(270, 50, 191, 28));
        s_confirmPassword = new QLineEdit(SignUp);
        s_confirmPassword->setObjectName("s_confirmPassword");
        s_confirmPassword->setGeometry(QRect(270, 170, 191, 28));
        label_4 = new QLabel(SignUp);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(80, 180, 191, 18));
        label_4->setStyleSheet(QString::fromUtf8("font: 700 11pt \"SimSun\";\n"
"background-color: rgba(148,188,138,255);\n"
"color: rgb(0, 0, 0);\n"
""));
        frame = new QFrame(SignUp);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(-11, -1, 531, 351));
        frame->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/signInBack.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        s_username->raise();
        s_password->raise();
        pushButton->raise();
        pushButton_2->raise();
        s_name->raise();
        s_confirmPassword->raise();
        label_4->raise();

        retranslateUi(SignUp);

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QWidget *SignUp)
    {
        SignUp->setWindowTitle(QCoreApplication::translate("SignUp", "SIGN UP", nullptr));
        label->setText(QCoreApplication::translate("SignUp", "Name :", nullptr));
        label_2->setText(QCoreApplication::translate("SignUp", "Username : ", nullptr));
        label_3->setText(QCoreApplication::translate("SignUp", "Password :", nullptr));
        pushButton->setText(QCoreApplication::translate("SignUp", "ENTER", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SignUp", "LOG IN", nullptr));
        label_4->setText(QCoreApplication::translate("SignUp", "Confirm Password :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
