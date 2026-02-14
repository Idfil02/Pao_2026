#include "Calendario.h"

Calendario::Calendario(QObject* parent): QObject(parent){}

void Calendario::clear() { //svuoto l'intero vettore
    qDeleteAll(impegni);
    impegni.clear();
    tags.clear();
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

QVector<Evento*> Calendario::getImpegniByData(const QDate& data) const{
    QVector<Evento*> impegniGiorno;
    for(int i=0; i<impegni.size(); ++i){
        if(impegni.at(i)->getData() == data){
            impegniGiorno.append(impegni.at(i));
        }
    }
    return impegniGiorno;
}

QVector<Evento*> Calendario::getImpegniByNome(const QString& nome) const{
    if(nome.isEmpty()){
        return impegni;
    }
    QVector<Evento*> impegniByNome;
    for(int i=0; i<impegni.size(); ++i){
        Evento* ev = impegni.at(i);
        if(ev->getNome().contains(nome)){
            impegniByNome.push_back(ev);
        }
    }
    return impegniByNome;
}

QVector<Evento*> Calendario::getImpegniByTag(const QString& tag) const{
    QVector<Evento*> impegniByTag;
    for(int i=0; i<impegni.size(); ++i){
        if(impegni.at(i)->getTag() == tag){
            impegniByTag.push_back(impegni.at(i));
        }
    }
    return impegniByTag;
}

QList<QString> Calendario::getTags() const {
    return tags.keys();
}
void Calendario::refreshTags(){
    tags.clear();
    for(int i=0; i<impegni.size(); i++){
        QString tag = impegni[i]->getTag();
        if(tags[tag]==0){
            tags.insert(tag, 1);
        }else{
            tags[tag]++;
        }
    }
}
