#ifndef APPUNTAMENTO_H
#define APPUNTAMENTO_H
#include "Attivita.h"
class Appuntamento : public Attivita{
private:
    QString luogo;
    QString contatto;
public:
    QString setLuogo() const;
    QString setContatto() const;
    QString getLuogo(QString);
    QString getContatto(QString);
};
#endif // APPUNTAMENTO_H
