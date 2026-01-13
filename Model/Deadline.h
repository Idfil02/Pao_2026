#ifndef DEADLINE_H
#define DEADLINE_H
#include <QString>
#include <QDate>
#include "Evento.h"
class Deadline : public Evento{
private:
    bool completato;
public:
    Deadline(QString,QString,QString,QDate);
    bool getCompletato() const;
    void setCompletato(bool);
    virtual void acceptVisitor(EventVisitor&) override;
};
#endif // DEADLINE_H
