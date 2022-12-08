#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logInWindow.reset(new LogIn());
    signUpWindow.reset(new SignUp());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_3_clicked()
{
    logInWindow->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    signUpWindow->show();
}

