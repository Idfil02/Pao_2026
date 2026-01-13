#include "Attivita.h"
#include "EventVisitor.h"
Attivita::Attivita(QString name,QString tg,QString desc,QDate date,QTime start,QTime end):
    Evento(name,tg,desc,date),oraInizio(start),oraFine(end){}
QTime Attivita::getOraInizio() const {return oraInizio;}
QTime Attivita::getOraFine() const {return oraFine;}
void Attivita::setOraInizio(QTime oi){oraInizio = oi;}
void Attivita::setOraFine(QTime of){oraFine = of;}
void Attivita::acceptVisitor(EventVisitor& visitor){
    visitor.visit(*this);
}
