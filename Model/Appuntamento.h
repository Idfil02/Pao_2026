#ifndef APPUNTAMENTO_H
#define APPUNTAMENTO_H
#include "Attivita.h"
class Appuntamento : public Attivita{
private:
    QString luogo;
    QString contatto;
public:
    Appuntamento(QString,QString,QString,QDate,QTime,QTime,QString,QString);
    QString getLuogo() const;
    QString getContatto() const;
    void setLuogo(QString);
    void setContatto(QString);
};
#endif // APPUNTAMENTO_H
