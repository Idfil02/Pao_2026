#ifndef DEADLINE_H
#define DEADLINE_H
#include <QString>
#include <QDate>
#include "Evento.h"
class Deadline : public Evento{
public:
    bool completato;
private:
    Deadline(QString,QString,QString,QDate);
    bool getCompletato() const;
    void setCompletato(bool);
};
#endif // DEADLINE_H
