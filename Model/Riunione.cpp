#include "Riunione.h"
#include "EventVisitor.h"
#include <QJsonObject>
#include <QJsonArray>
Riunione::Riunione(QString name,QString tg,QString dsc,QDate date,QTime start,QTime end, QString lnk):
    Attivita(name,tg,dsc,date,start,end), link(lnk){}
QString Riunione::getLink() const {return link; }
QVector<QString> Riunione::getPartecipanti() const {return partecipanti;}
void Riunione::setLink(QString l) {link = l;}
void Riunione::setPartecipanti(QVector<QString>& p) { //sostituisco l'intero vettore dei partecipanti
    partecipanti.clear();
    partecipanti = p;
}
void Riunione::acceptVisitor(EventVisitor& visitor){
    visitor.visit(*this);
}
QJsonObject Riunione::toJson() const{
    QJsonObject output = this->Attivita::toJson();
    output["Link"] = link;
    QJsonArray part;
    for(const QString& p : partecipanti){
        part += p;
    }
    output["Partecipanti"] = part;
    output["Tipo"] = 2;
    return output;
}
void Riunione::toXml(QXmlStreamWriter& w) const{
    w.writeStartElement("riunione");
    w.writeTextElement("nome",getNome());
    w.writeTextElement("tag",getTag());
    w.writeTextElement("desc",getDesc());
    w.writeTextElement("data",getData().toString());
    w.writeTextElement("ora_inizio",getOraInizio().toString());
    w.writeTextElement("ora_fine",getOraFine().toString());
    w.writeTextElement("link",link);
    w.writeStartElement("partecipanti");
    for (const QString& p : partecipanti){
        w.writeTextElement("persona",p);
    }
    w.writeEndElement();
    w.writeEndElement();
}
