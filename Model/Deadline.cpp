#include "Deadline.h"
#include "EventVisitor.h"
#include <QJsonObject>
Deadline::Deadline(QString name,QString tg,QString dsc,QDate date, bool c):
    Evento(name,tg,dsc,date), completato(c){}

bool Deadline::getCompletato() const {return completato;}
void Deadline::setCompletato(bool c) {completato = c;}
void Deadline::acceptVisitor(EventVisitor& visitor){
    visitor.visit(*this);
}

QJsonObject Deadline::toJson() const{
    QJsonObject output = this->Evento::toJson();
    output["Completato"] = completato;
    output["Tipo"] = 0;
    return output;
}
