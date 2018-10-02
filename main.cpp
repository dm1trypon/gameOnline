#include "widget.h"
#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Client c("192.168.0.105", 8080);

    return a.exec();
}
