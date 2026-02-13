#ifndef AGENDAVISITOR_H
#define AGENDAVISITOR_H
#include "View/Agenda/Agenda.h"
#include "View/Visitors/ListVisitor.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QTextEdit>

class AgendaVisitor : public ListVisitor{
private:
    Agenda* agenda;
    void buildButtons(QHBoxLayout*, Evento *ev) override;
public:
    AgendaVisitor(QListWidget*, Agenda*);
};

#endif // AGENDAVISITOR_H

