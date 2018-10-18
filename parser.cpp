#include "parser.h"
#include "linksignal.h"

#include <QJsonDocument>
#include <QJsonObject>

Parser::Parser()
{
    connect(&LinkSignal::Instance(), &LinkSignal::signalWorkWithJson, this, &Parser::slotProcessParse);
    connect(&LinkSignal::Instance(), &LinkSignal::signalJsonOnConnection, this, &Parser::slotAddToJson);
    connect(&LinkSignal::Instance(), &LinkSignal::signalJsonOnMove, this, &Parser::slotAddToJson);
    connect(&LinkSignal::Instance(), &LinkSignal::signalGetNickName, this, &Parser::slotSetNickName);
}

void Parser::slotProcessParse(QString data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsObj = jsonDoc.object();
    if (jsObj.value(TYPE) == CLIENTS_LIST)
    {
        bool find = false;
        QJsonObject objClients;
        QJsonArray arrClients = jsObj[CLIENTS_LIST].toArray();
        foreach (const QJsonValue & value, arrClients)
        {
            QJsonObject objArr = value.toObject();
            foreach (const QJsonValue & _value, _arrClients)
            {
                QJsonObject _objArr = _value.toObject();
                if (objArr.value(NICKNAME) == _objArr.value(NICKNAME))
                {
                    find = true;
                    break;
                }
            }

            if ((!find) && (_nickName != objArr.value(NICKNAME).toString()))
            {
                _arrClients.push_back(objArr);
                LinkSignal::Instance().createEnemyPlayer(static_cast<qreal>(objArr.value(POSX).toString().toInt()), static_cast<qreal>(objArr.value(POSY).toString().toInt()));
                find = false;
            }
//            if (!find && !onFind(jsObj))
//            {
//                _arrClients.push_back(objArr);
//                LinkSignal::Instance().createEnemyPlayer(objArr.value(POSX).toString().toInt(), objArr.value(POSY).toString().toInt());
//                find = false;
//            }
        }
    }
    if ((jsObj.value(TYPE) == MOVE) && onFind(jsObj))
    {
        LinkSignal::Instance().moveEnemyPlayer(jsObj.value(POSX).toString().toInt(), jsObj.value(POSY).toString().toInt());
    }
}

void Parser::slotAddToJson(qreal posX, qreal posY, QString type)
{
    QJsonDocument document;
    QJsonObject root = document.object();
    root.insert(TYPE, type);
    root.insert(NICKNAME, _nickName);
    root.insert(POSX, QString::number(posX));
    root.insert(POSY, QString::number(posY));
    document.setObject(root);
    QString strJson(document.toJson(QJsonDocument::Compact));
    LinkSignal::Instance().compactJson(strJson);
}

void Parser::slotSetNickName(QString nickName)
{
    _nickName = nickName;
}

bool Parser::onFind(QJsonObject jsObj)
{
    return jsObj.value(NICKNAME).toString() != _nickName;
}
