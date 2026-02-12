#include "AgendaVisitor.h"
#include <QLabel>
#include <QPushButton>

AgendaVisitor::AgendaVisitor(QListWidget* list, Agenda* agendaParent):
    ListVisitor(list), agenda(agendaParent){}

//metodo di utility per la visuallazzione dei bottoni a lato dei singoli eventi listati
void AgendaVisitor::buildButtons(QHBoxLayout* layout, Evento* ev){
    Agenda* agendaLocale = agenda;
    QPushButton* tastoEdit = new QPushButton(QIcon(":/Icons/View/Icons/edit.svg"),"");
    tastoEdit->setStyleSheet("background-color: cyan");
    QPushButton* tastoElimina = new QPushButton(QIcon(":/Icons/View/Icons/deleteIcon.svg"),"");
    tastoElimina->setStyleSheet("background-color: red");
    layout->addWidget(tastoEdit,1);
    layout->addWidget(tastoElimina,1);
    QObject::connect(tastoEdit, &QPushButton::clicked, agenda, [agendaLocale, ev](){
        agendaLocale->emit richiestaEdit(ev);
    });
    QObject::connect(tastoElimina, &QPushButton::clicked, agenda,[agendaLocale, ev](){
        agendaLocale->emit eventoEliminato(ev, ev->getData());
    });
}


