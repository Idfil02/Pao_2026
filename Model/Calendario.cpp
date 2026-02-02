#include "Calendario.h"

Calendario::Calendario(QObject* parent): QObject(parent){}

void Calendario::clear() { //sostituisco l'intero vettore
    qDeleteAll(impegni);
    impegni.clear();
}


void Calendario::addEvento(Evento* e){ //aggiungo un singolo evento
    impegni.push_back(e);
    QString tag = e->getTag();
    if(tags[tag]==0){
        tags.insert(tag, 1);
    }else{
        tags[tag]++;
    }
    emit aggiuntoEvento(e->getData());
}


void Calendario::removeEvento(Evento* e) { //rimuovo singolo evento
    impegni.removeAll(e);
    QString t = e->getTag();
    if(tags.contains(t)){
        tags[t]--;
        if(tags[t] <= 0){
            tags.remove(t);
        }
    }
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
QList<QString> Calendario::getTags() const {
    return tags.keys();
}
