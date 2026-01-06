#ifndef RIUNIONE_H
#define RIUNIONE_H
#include "Attivita.h"
#include <QVector>
class Riunione : public Attivita {
private:
    QString link;
    QVector<QString> partecipanti;
public:
    QString getLink() const;
    QVector<QString> getPartecipanti() const;
    void setLink(QString);
    void setPartecipanti(QVector<QString>&);
    void addPartecipante(QString);
    void removePartecipante(QString);
};
#endif // RIUNIONE_H
