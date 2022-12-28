#include "gui.h"
#include "Route.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Route routes;
    gui w(routes);
    w.show();
    return a.exec();
}
