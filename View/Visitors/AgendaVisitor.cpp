#include "AgendaVisitor.h"
#include <QLabel>
#include <QPushButton>
AgendaVisitor::AgendaVisitor(QListWidget* list, Agenda* agendaParent):
    eventiDelGiorno(list), agenda(agendaParent){}
QWidget* AgendaVisitor::buildListItem(Evento* ev, QHBoxLayout* layout){
    QWidget* eventItem = new QWidget;
    eventItem->setLayout(layout);
    layout->setContentsMargins(2, 2, 2, 2);
    QLabel* nome = new QLabel(ev->getNome());    //inserisco titolo dell'evento
    layout->addWidget(nome,3);
    return eventItem;
}


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


void AgendaVisitor::visit(Deadline& scadenza){
    Evento* event = &scadenza;
    QListWidgetItem* item = new QListWidgetItem(eventiDelGiorno);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(event, layout);
    buildButtons(layout,event);
    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(scadenza.getCompletato() ? QColor(165,214,167) : QColor(225,0,0));
    item->setSizeHint(evItem->sizeHint());
    eventiDelGiorno->setItemWidget(item, evItem);
}


void AgendaVisitor::visit(Attivita& att){
    Evento* event = &att;
    QListWidgetItem* item = new QListWidgetItem(eventiDelGiorno);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(event, layout);

    QString time = att.getOraInizio().toString("HH:mm")+"-"+att.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    layout->addWidget(orario,3);
    buildButtons(layout,event);

    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(0,204,204));
    item->setSizeHint(evItem->sizeHint());
    eventiDelGiorno->setItemWidget(item, evItem);
}


void AgendaVisitor::visit(Riunione& riunione){
    Evento* event = &riunione;
    QListWidgetItem* item = new QListWidgetItem(eventiDelGiorno);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(event, layout);

    QString time = riunione.getOraInizio().toString("HH:mm")+"-"+riunione.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    layout->addWidget(orario,3);
    buildButtons(layout,event);

    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(224,224,224));
    item->setSizeHint(evItem->sizeHint());
    eventiDelGiorno->setItemWidget(item, evItem);
}


void AgendaVisitor::visit(Appuntamento& app){
    Evento* event = &app;
    QListWidgetItem* item = new QListWidgetItem(eventiDelGiorno);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(event, layout);

    QString time = app.getOraInizio().toString("HH:mm")+"-"+app.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    layout->addWidget(orario,3);
    buildButtons(layout,event);

    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(224,224,224));
    item->setSizeHint(evItem->sizeHint());
    eventiDelGiorno->setItemWidget(item, evItem);
}
