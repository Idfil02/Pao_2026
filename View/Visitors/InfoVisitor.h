#ifndef INFOVISITOR_H
#define INFOVISITOR_H
#include "Model/EventVisitor.h"
#include <QFormLayout>

class InfoVisitor : public EventVisitor{
private:
    QFormLayout* dettagliEvento;
public:
    explicit InfoVisitor(QFormLayout*);
    virtual void visit(Deadline&) override;
    virtual void visit(Attivita&) override;
    virtual void visit(Riunione&) override;
    virtual void visit(Appuntamento&) override;
};

#endif // INFOVISITOR_H
