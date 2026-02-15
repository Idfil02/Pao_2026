#ifndef RICERCAVISITOR_H
#define RICERCAVISITOR_H
#include <QListWidget>
#include <QHBoxLayout>
#include "View/ListaEventi/ListaEventi.h"
#include "View/Visitors/ListVisitor.h"

class RicercaVisitor : public ListVisitor
{
private:
    ListaEventi* listaRicerca;
    void buildButtons(QHBoxLayout*, Evento *ev) override;
public:
    RicercaVisitor(QListWidget*, ListaEventi*);
    ~RicercaVisitor() = default;
};

#endif // RICERCAVISITOR_H
