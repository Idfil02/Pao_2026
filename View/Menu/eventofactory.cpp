#include "eventofactory.h"
#include "Model/Deadline.h"
#include "Model/Attivita.h"
#include "Model/Riunione.h"
#include "Model/Appuntamento.h"
#include <QJsonArray>
EventoFactory::EventoFactory() {}

void EventoFactory::BuildEvento(Calendario* cal, QJsonObject obj){
    int tipo = obj["Tipo"].toInt();
    switch(tipo){
    case tipoEvento::deadline:{
        Deadline* newEvento = new Deadline(obj["Nome"].toString(),
                                       obj["Tag"].toString(),
                                       obj["Desc"].toString(),
                                       QDate::fromString(obj["Data"].toString()),
                                       obj["Completato"].toInt());
        cal->addEvento(newEvento);
        break;}
    case tipoEvento::attivita:{
        Attivita* newEvento = new Attivita(obj["Nome"].toString(),
                                       obj["Tag"].toString(),
                                       obj["Desc"].toString(),
                                       QDate::fromString(obj["Data"].toString()),
                                       QTime::fromString(obj["OraInizio"].toString()),
                                       QTime::fromString(obj["OraFine"].toString()));
        cal->addEvento(newEvento);
        break;}
    case tipoEvento::riunione:{
        Riunione* newEvento = new Riunione(obj["Nome"].toString(),
                                       obj["Tag"].toString(),
                                       obj["Desc"].toString(),
                                       QDate::fromString(obj["Data"].toString()),
                                       QTime::fromString(obj["OraInizio"].toString()),
                                       QTime::fromString(obj["OraFine"].toString()),
                                       obj["Link"].toString());

        QVector<QString> partecipanti;
        QJsonArray p = obj["Partecipanti"].toArray();
        for(int i=0; i<p.size(); ++i){
            partecipanti.push_back((p.at(i)).toString());
        }
        newEvento->setPartecipanti(partecipanti);
        cal->addEvento(newEvento);
        break;}
    case tipoEvento::appuntamento:{
        Appuntamento* newEvento = new Appuntamento(obj["Nome"].toString(),
                                            obj["Tag"].toString(),
                                            obj["Desc"].toString(),
                                            QDate::fromString(obj["Data"].toString()),
                                            QTime::fromString(obj["OraInizio"].toString()),
                                            QTime::fromString(obj["OraFine"].toString()),
                                            obj["Luogo"].toString(),
                                            obj["Contatto"].toString());
        cal->addEvento(newEvento);
        break;}
    default:
        break;
    }
};
