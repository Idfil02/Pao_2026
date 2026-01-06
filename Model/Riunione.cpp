#include "Riunione.h"

QString Riunione::getLink() const {return link; }
QVector<QString> Riunione::getPartecipanti() const {return partecipanti;}
void Riunione::setLink(QString l) {link = l;}
void Riunione::setPartecipanti(QVector<QString>& p) {
    partecipanti.clear();
    partecipanti = p;
}
void Riunione::addPartecipante(QString p){partecipanti.push_back(p);}
void Riunione::removePartecipante(QString p){
    partecipanti.removeAll(p); //funzione di QList che rimuove tutti gli elementi uguali a p
}
