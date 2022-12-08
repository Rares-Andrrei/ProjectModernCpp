#include "signup.h"
#include "ui_signup.h"

#include<QString>
#include <QMessageBox>

SignUp::SignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_pushButton_clicked()
{
    QString name= ui->s_name->text();
    QString username = ui->s_username->text();
    QString password = ui->s_password->text();
    QString confirmPassword=  ui->s_confirmPassword->text();

    //daca username ul nu e unic, eroare
    //daca parola nu e la fel ca confimPassword, eroare

    if (password!=confirmPassword)
        QMessageBox::about(this, "Sign up error", "The passwords do not match");
    else
        QMessageBox::about(this, "Sign up", "The account is created successfully, now you can log in");

}


void SignUp::on_pushButton_2_clicked()
{

}

