#ifndef ATTIVITA_H
#define ATTIVITA_H
#include "Evento.h"
#include <QTime>
class Attivita : public Evento{
private:
    QTime oraInizio;
    QTime oraFine;
public:
    Attivita() = default;
    Attivita(QString,QString,QString,QDate,QTime,QTime);
    QTime getOraInizio() const;
    QTime getOraFine() const;
    void setOraInizio(QTime);
    void setOraFine(QTime);
    virtual void acceptVisitor(EventVisitor&) override;
    QJsonObject toJson() const override;
    virtual void toXml(QXmlStreamWriter&) const override;
};
#endif // ATTIVITA_H
