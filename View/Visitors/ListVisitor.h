#ifndef LISTVISITOR_H
#define LISTVISITOR_H
#include "Model/EventVisitor.h"
#include <QHBoxLayout>
#include <QListWidget>

class ListVisitor : public EventVisitor{
private:
    QListWidget* listaEventi;
    QWidget* buildListItem(Evento*,QHBoxLayout*);
    virtual void buildButtons(QHBoxLayout*, Evento *ev) = 0;
public:
    ListVisitor(QListWidget*);
    ~ListVisitor() = default;
    virtual void visit(Deadline&) override;
    virtual void visit(Attivita&) override;
    virtual void visit(Riunione&) override;
    virtual void visit(Appuntamento&) override;
};

#endif // LISTVISITOR_H
