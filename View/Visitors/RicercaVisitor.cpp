#include "RicercaVisitor.h"
#include <QLabel>
#include <QPushButton>

RicercaVisitor::RicercaVisitor(QListWidget* listaParent, ListaEventi* ricerca):
    ListVisitor(listaParent), listaRicerca(ricerca){}

//metodo di utility per la visuallazzione dei bottoni a lato dei singoli eventi listati
void RicercaVisitor::buildButtons(QHBoxLayout* layout, Evento* ev){
    ListaEventi* listaLocale = listaRicerca;
    QPushButton* tastoGoTO = new QPushButton(QIcon(":/Icons/View/Icons/goto.svg"),"");
    tastoGoTO->setStyleSheet("background-color: green");
    QPushButton* tastoEdit = new QPushButton(QIcon(":/Icons/View/Icons/edit.svg"),"");
    tastoEdit->setStyleSheet("background-color: cyan");
    QPushButton* tastoElimina = new QPushButton(QIcon(":/Icons/View/Icons/deleteIcon.svg"),"");
    tastoElimina->setStyleSheet("background-color: red");
    QWidget* btnContainer = new QWidget;
    QHBoxLayout* btnLayout = new QHBoxLayout(btnContainer);
    btnLayout->addWidget(tastoGoTO, 1);
    btnLayout->addWidget(tastoEdit,1);
    btnLayout->addWidget(tastoElimina,1);
    layout->addWidget(btnContainer,3);
    QObject::connect(tastoGoTO, &QPushButton::clicked, listaRicerca, [listaLocale, ev](){
        listaLocale->emit goTo(ev);
    });
    QObject::connect(tastoEdit, &QPushButton::clicked, listaRicerca, [listaLocale, ev](){
        listaLocale->emit richiestaEdit(ev);
    });
    QObject::connect(tastoElimina, &QPushButton::clicked, listaRicerca,[listaLocale, ev](){
        listaLocale->emit eventoEliminato(ev, ev->getData());
    });
}

