#include "Appuntamento.h"
#include "EventVisitor.h"
#include <QJsonObject>
Appuntamento::Appuntamento(QString name,QString tg,QString desc,QDate date,QTime start,QTime end,QString place,QString cont):
    Attivita(name,tg,desc,date,start,end), luogo(place), contatto(cont){}
QString Appuntamento::getLuogo() const {return luogo;}
QString Appuntamento::getContatto() const {return contatto;}
void Appuntamento::setLuogo(QString l){luogo = l;}
void Appuntamento::setContatto(QString c){contatto = c;}
void Appuntamento::acceptVisitor(EventVisitor& visitor){
    visitor.visit(*this);
}
QJsonObject Appuntamento::toJson() const{
    QJsonObject output = this->Attivita::toJson();
    output["Luogo"] = luogo;
    output["Contatto"] = contatto;
    output["Tipo"] = 3;
    return output;
}
void Appuntamento::toXml(QXmlStreamWriter& w) const{
    w.writeStartElement("appuntamento");
    w.writeTextElement("nome",getNome());
    w.writeTextElement("tag",getTag());
    w.writeTextElement("desc",getDesc());
    w.writeTextElement("data",getData().toString());
    w.writeTextElement("ora_inizio",getOraInizio().toString());
    w.writeTextElement("ora_fine",getOraFine().toString());
    w.writeTextElement("luogo",luogo);
    w.writeTextElement("contatto",contatto);
    w.writeEndElement();
}
