#include "Evento.h"
#include <QJsonObject>

Evento::Evento(QString name,QString tg, QString dsc,QDate date):
    nome(name),tag(tg), desc(dsc), data(date){}

QString Evento::getNome() const {return nome;}

QString Evento::getTag() const {return tag;}

QString Evento::getDesc() const {return desc;}

QDate Evento::getData() const {return data;}

void Evento::setNome(const QString &n) {nome = n;}

void Evento::setTag(const QString& t) {tag = t;}

void Evento::setDesc(const QString& d) {desc = d;}

void Evento::setData(const QDate& D) {data = D;}

QJsonObject Evento::toJson() const{
    QJsonObject output;
    output["Nome"] = nome;
    output["Tag"] = tag;
    output["Desc"] = desc;
    output["Data"] = data.toString();
    return output;
}


void Evento::toXml(QXmlStreamWriter& w) const{
    w.writeStartElement("evento");
    w.writeTextElement("nome",nome);
    w.writeTextElement("tag",tag);
    w.writeTextElement("desc",desc);
    w.writeTextElement("data",data.toString());
    w.writeEndElement();
}

