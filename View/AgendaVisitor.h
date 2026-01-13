#ifndef AGENDAVISITOR_H
#define AGENDAVISITOR_H
#include "Model/EventVisitor.h"
#include <QListWidget>
#include <QTextEdit>
class AgendaVisitor : public EventVisitor{
private:
    QListWidget* eventiDelGiorno;
    QWidget* buildListItem(Evento*);
public:
    explicit AgendaVisitor(QListWidget*);
    virtual void visit(Deadline&) override;
    virtual void visit(Attivita&) override;
    virtual void visit(Riunione&) override;
    virtual void visit(Appuntamento&) override;
};

#endif // AGENDAVISITOR_H

