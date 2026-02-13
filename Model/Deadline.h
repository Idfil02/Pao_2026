#ifndef DEADLINE_H
#define DEADLINE_H
#include <QString>
#include <QDate>
#include "Evento.h"

class Deadline : public Evento{
private:
    bool completato;
public:
    Deadline() = default;
    Deadline(QString,QString,QString,QDate,bool c=false);
    bool getCompletato() const;
    void setCompletato(bool);
    virtual void acceptVisitor(EventVisitor&) override;
    virtual QJsonObject toJson() const override;
    virtual void toXml(QXmlStreamWriter&) const override;
};
#endif // DEADLINE_H
