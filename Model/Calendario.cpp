#include "Calendario.h"

Calendario::Calendario(QObject* parent): QObject(parent){}

void Calendario::clear() { //sostituisco l'intero vettore
    qDeleteAll(impegni);
    impegni.clear();
}


void Calendario::addEvento(Evento* e){ //aggiungo un singolo evento
    impegni.push_back(e);
    emit aggiuntoEvento(e->getData());
}


void Calendario::removeEvento(Evento* e) { //rimuovo singolo evento
    impegni.removeAll(e);
    delete e;
}


QVector<Evento*> Calendario::getImpegni() const{return impegni;}
QVector<Evento*> Calendario::getImpegni(const QDate& data) const{
    QVector<Evento*> impegniGiorno;
    for(int i=0; i<impegni.size(); ++i){
        if(impegni.at(i)->getData() == data){
            impegniGiorno.append(impegni.at(i));
        }
    }
    return impegniGiorno;
}
