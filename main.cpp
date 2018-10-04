#include "widget.h"
#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Client c("127.0.0.1", 8080);
    return a.exec();
}
