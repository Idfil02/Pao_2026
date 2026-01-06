#include "Calendario.h"
void Calendario::setEventi(const QVector<Evento*>& evs){
    impegni.clear();
    impegni = evs;
}
void Calendario::addEvento(Evento& e) {impegni.push_back(&e);}
void Calendario::removeEvento(const Evento& e){
    for(int i=0; i<impegni.size(); ++i){
        if(*(impegni[i])==e){
            delete impegni[i];
            impegni.remove(i);
        }
    }
}
