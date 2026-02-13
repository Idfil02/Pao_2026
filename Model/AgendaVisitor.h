#ifndef AGENDAVISITOR_H
#define AGENDAVISITOR_H
#include "Model/EventVisitor.h"
#include <QListWidget>
class AgendaVisitor : public EventVisitor{
private:
    QListWidget* eventiDelGiorno;
public:
    explicit AgendaVisitor(QListWidget* list);
    virtual void visit(Deadline&) override;
    virtual void visit(Attivita&) override;
    virtual void visit(Riunione&) override;
    virtual void visit(Appuntamento&) override;
};

#endif // AGENDAVISITOR_H
