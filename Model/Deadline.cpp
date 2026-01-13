#include "Deadline.h"
#include "EventVisitor.h"
Deadline::Deadline(QString name,QString tg,QString dsc,QDate date):
    Evento(name,tg,dsc,date),completato(0){}

bool Deadline::getCompletato() const {return completato;}
void Deadline::setCompletato(bool c) {completato = c;}
void Deadline::acceptVisitor(EventVisitor& visitor){
    visitor.visit(*this);
}
