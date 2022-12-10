#include "signUp.h"

signUp::signUp(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.enterButton, SIGNAL(clicked()), SLOT(onEnterButtonClicked()));
}

void signUp::onEnterButtonClicked()
{
    QString name = ui.s_name->text();
    QString username = ui.s_username->text();
    QString password = ui.s_password->text();
    QString confirmPassword = ui.s_confirmPassword->text();

    //daca username ul nu e unic, eroare
    //daca parola nu e la fel ca confimPassword, eroare

    if (password != confirmPassword)
        QMessageBox::about(this, "Sign up error", "The passwords do not match");
    else
        QMessageBox::about(this, "Sign up", "The account is created successfully, now you can log in");
}
