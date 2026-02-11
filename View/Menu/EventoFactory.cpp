#include "EventoFactory.h"
#include "Model/Deadline.h"
#include "Model/Attivita.h"
#include "Model/Riunione.h"
#include "Model/Appuntamento.h"
#include <QJsonArray>

EventoFactory::EventoFactory() {}

bool EventoFactory::BuildEvento(Calendario* cal, QJsonObject obj){
    int tipo = obj["Tipo"].toInt();
    switch(tipo){
    case tipoEvento::deadline:{
        if(obj["Nome"].toString().isEmpty() || obj["Nome"].toString().isNull() || !QDate::fromString(obj["Data"].toString()).isValid()){
            return false;
        }
        Deadline* newEvento = new Deadline(obj["Nome"].toString(),
                                       obj["Tag"].toString(),
                                       obj["Desc"].toString(),
                                       QDate::fromString(obj["Data"].toString()),
                                       obj["Completato"].toInt());
        cal->addEvento(newEvento);
        break;}
    case tipoEvento::attivita:{
        if(obj["Nome"].toString().isEmpty() || obj["Nome"].toString().isNull() || !QDate::fromString(obj["Data"].toString()).isValid()
            || !QTime::fromString(obj["OraInizio"].toString()).isValid() || !QTime::fromString(obj["OraFine"].toString()).isValid())
            return false;
        Attivita* newEvento = new Attivita(obj["Nome"].toString(),
                                       obj["Tag"].toString(),
                                       obj["Desc"].toString(),
                                       QDate::fromString(obj["Data"].toString()),
                                       QTime::fromString(obj["OraInizio"].toString()),
                                       QTime::fromString(obj["OraFine"].toString()));
        cal->addEvento(newEvento);
        break;}
    case tipoEvento::riunione:{
        if(obj["Nome"].toString().isEmpty() || obj["Nome"].toString().isNull() || !QDate::fromString(obj["Data"].toString()).isValid()
            || !QTime::fromString(obj["OraInizio"].toString()).isValid() || !QTime::fromString(obj["OraFine"].toString()).isValid() || obj["Partecipanti"].toArray().isEmpty())
            return false;
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
        if(obj["Nome"].toString().isEmpty() || obj["Nome"].toString().isNull() || !QDate::fromString(obj["Data"].toString()).isValid()
            || !QTime::fromString(obj["OraInizio"].toString()).isValid() || !QTime::fromString(obj["OraFine"].toString()).isValid()
            || obj["Luogo"].toString().isEmpty() || obj["Luogo"].toString().isNull())
            return false;
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
