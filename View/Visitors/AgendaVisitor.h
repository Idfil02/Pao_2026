#ifndef AGENDAVISITOR_H
#define AGENDAVISITOR_H
#include "Model/EventVisitor.h"
#include "View/Agenda/Agenda.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QTextEdit>

class AgendaVisitor : public EventVisitor{
private:
    QListWidget* eventiDelGiorno;
    Agenda* agenda;
    QWidget* buildListItem(Evento*,QHBoxLayout*);
    void buildButtons(QHBoxLayout*, Evento *ev);
public:
    AgendaVisitor(QListWidget*, Agenda*);
    virtual void visit(Deadline&) override;
    virtual void visit(Attivita&) override;
    virtual void visit(Riunione&) override;
    virtual void visit(Appuntamento&) override;
};

#endif // AGENDAVISITOR_H

