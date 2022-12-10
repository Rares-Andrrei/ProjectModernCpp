#include "logIn.h"

logIn::logIn(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.enterButton, SIGNAL(clicked()), SLOT(onEnterButtonClicked()));
}

void logIn::onEnterButtonClicked()
{
    QString username = ui.l_username->text();
    QString password = ui.l_password->text();

    //verificari dupa ce se fac rutele cu serverul

    if (password != "123456789")
        QMessageBox::about(this, "Incorrect password", "The password is incorrect, try again");
}
