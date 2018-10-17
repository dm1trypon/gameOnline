#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QJsonArray>

const QString CLIENTS_LIST = "clientsList";
const QString TYPE = "type";
const QString CONNECTION = "connection";
const QString MOVE = "move";
const QString NICKNAME = "nickName";
const QString POSX = "posX";
const QString POSY = "posY";

class Parser : public QObject
{
    Q_OBJECT
public:
    Parser();
private slots:
    void slotProcessParse(QString data);
    void slotAddToJson(qreal posX, qreal posY, QString type);
    void slotSetNickName(QString nickName);
private:
    QString _nickName;
    QJsonArray _arrClients;
    bool onFind(QJsonObject jsObj);
};

#endif // PARSER_H
