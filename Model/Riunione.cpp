#include "Riunione.h"
#include "EventVisitor.h"
#include <QJsonObject>
#include <QJsonArray>
Riunione::Riunione(QString name,QString tg,QString dsc,QDate date,QTime start,QTime end, QString lnk):
    Attivita(name,tg,dsc,date,start,end), link(lnk){}
QString Riunione::getLink() const {return link; }
QVector<QString> Riunione::getPartecipanti() const {return partecipanti;}
void Riunione::setLink(QString l) {link = l;}
void Riunione::setPartecipanti(QVector<QString>& p) { //sostituisco l'intero vettore dei partecipanti
    partecipanti.clear();
    partecipanti = p;
}
void Riunione::addPartecipante(QString p){partecipanti.push_back(p);} //aggiungo un singolo partecipante
void Riunione::removePartecipante(QString p){
    partecipanti.removeAll(p); //funzione di QList che rimuove tutti gli elementi uguali a p
}
void Riunione::acceptVisitor(EventVisitor& visitor){
    visitor.visit(*this);
}
QJsonObject Riunione::toJson() const{
    QJsonObject output = this->Attivita::toJson();
    output["Link"] = link;
    QJsonArray part;
    for(const QString& p : partecipanti){
        part += p;
    }
    output["Partecipanti"] = part;
    output["Tipo"] = 2;
    return output;
}
