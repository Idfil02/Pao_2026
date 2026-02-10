#ifndef LISTVISITOR_H
#define LISTVISITOR_H
#include <QListWidget>
#include <QHBoxLayout>
#include "Model/EventVisitor.h"
#include "View/ListaEventi/listaeventi.h"

class ListVisitor : public EventVisitor
{
private:
    QListWidget* eventi;
    QWidget* buildListItem(Evento*,QHBoxLayout*);
    ListaEventi* lista;
    void buildButtons(QHBoxLayout*, Evento *ev);
public:
    ListVisitor(QListWidget*, ListaEventi*);
    virtual void visit(Deadline&) override;
    virtual void visit(Attivita&) override;
    virtual void visit(Riunione&) override;
    virtual void visit(Appuntamento&) override;
};

#endif // LISTVISITOR_H
