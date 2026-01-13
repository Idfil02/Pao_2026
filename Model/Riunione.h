#ifndef RIUNIONE_H
#define RIUNIONE_H
#include "Attivita.h"
#include <QVector>
class Riunione : public Attivita {
private:
    QString link;
    QVector<QString> partecipanti;
public:
    Riunione(QString,QString,QString,QDate,QTime,QTime,QString);
    QString getLink() const;
    QVector<QString> getPartecipanti() const;
    void setLink(QString);
    void setPartecipanti(QVector<QString>&);
    void addPartecipante(QString);
    void removePartecipante(QString);
    virtual void acceptVisitor(EventVisitor&) override;
};
#endif // RIUNIONE_H
