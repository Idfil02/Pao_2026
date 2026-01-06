#include "Evento.h"

QString Evento::getNome() const {return nome;}
QString Evento::getTag() const {return tag;}
QString Evento::getDesc() const {return desc;}
QDate Evento::getData() const {return data;}
void Evento::setNome(const QString& n) {nome = n;}
void Evento::setTag(const QString& t) {tag = t;}
void Evento::setDesc(const QString& d) {desc = d;}
void Evento::setData(const QDate& D) {data = D;}
bool Evento::operator==(const Evento& e){
    return nome==e.getNome() &&
           tag==e.getTag() &&
           desc==e.getDesc() &&
           data==e.getData();
}
