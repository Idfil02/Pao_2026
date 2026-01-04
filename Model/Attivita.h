#ifndef ATTIVITA_H
#define ATTIVITA_H
#include "Evento.h"
#include <QTime>
class Attivita : public Evento{
private:
    QTime oraInizio;
    QTime oraFine;
public:
    QTime getOraInizio() const;
    QTime getOraFine() const;
    void setOraInizio(QTime);
    void setOraFine(QTime);
};
#endif // ATTIVITA_H
