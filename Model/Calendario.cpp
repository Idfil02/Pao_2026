#include "Calendario.h"
void Calendario::addEvento(Evento& e) {impegni.push_back(&e);}
void Calendario::removeEvento(Evento& e){
    impegni.removeAll(e); //rimuove tutti gli eventi uguali a e;
}
