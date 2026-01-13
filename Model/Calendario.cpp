#include "Calendario.h"

Calendario::Calendario(QObject* parent): QObject(parent){}

void Calendario::setEventi(const QVector<Evento*>& evs) {
    for(int i=0;i<impegni.size();++i){
        delete impegni[i];
    }
    impegni.clear();
    impegni = evs;
}

void Calendario::addEvento(Evento* e) {
    impegni.push_back(e);
    emit aggiuntoEvento(e->getData());
}

void Calendario::removeEvento(const Evento& e) {
    for (int i = 0; i < impegni.size(); ++i) {
        if (*(impegni[i]) == e) {
            impegni.remove(i);
            break;
        }
    }
}

QVector<Evento*> Calendario::getImpegni(const QDate& data){
    QVector<Evento*> impegniGiorno;
    for(int i=0; i<impegni.size(); ++i){
        if(impegni.at(i)->getData() == data){
            impegniGiorno.append(impegni.at(i));
        }
    }
    return impegniGiorno;
}
