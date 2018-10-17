#include "widget.h"
#include "client.h"
#include "parser.h"

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption ipOption(QStringList() << "i" << "ip", "Ip for websocket", "ip");
    QCommandLineOption portOption(QStringList() << "p" << "port", "Port for websocket", "port");
    parser.addOption(ipOption);
    parser.addOption(portOption);
    parser.process(a);

    if (!parser.isSet(ipOption))
    {
        qDebug() << "IP is not set!";
        return -1;
    }

    if (!parser.isSet(portOption))
    {
        qDebug() << "Port is not set!";
        return -1;
    }

    QString _ip = parser.value(ipOption);
    int _port = parser.value(portOption).toInt();
    quint16 port = static_cast<quint16>(_port);
    qDebug() << "IP: " << _ip << " PORT:" << _port;
    Widget w;
    w.show();
    Client c(_ip, port);
    Parser p;
    return a.exec();
}
