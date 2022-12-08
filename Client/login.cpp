#include "login.h"
#include "ui_login.h"

#include<QString>
#include <QMessageBox>

LogIn::LogIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_pushButton_clicked()
{
    QString username = ui->l_username->text();
    QString password = ui->l_password->text();

    //daca nu se gaseste username ul in baza de date trebuie facut sign up
    //daca parola nu e corecta, eroare

    if (password!="123456789")
        QMessageBox::about(this, "Incorrect password", "The password is incorrect, try again");
}


void LogIn::on_pushButton_2_clicked()
{

}

