#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "login.h"
#include "signup.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<LogIn> logInWindow;
    std::shared_ptr<SignUp> signUpWindow;
};
#endif // MAINWINDOW_H