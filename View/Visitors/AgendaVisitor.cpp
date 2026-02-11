#include "AgendaVisitor.h"
#include <QLabel>
#include <QPushButton>

AgendaVisitor::AgendaVisitor(QListWidget* list, Agenda* agendaParent):
    eventiDelGiorno(list), agenda(agendaParent){}

//metodo di utility per la visulazzazione di un evento nella lista dell'agenda
QWidget* AgendaVisitor::buildListItem(Evento* ev, QHBoxLayout* layout){
    QWidget* eventItem = new QWidget;
    eventItem->setLayout(layout);
    layout->setContentsMargins(2, 2, 2, 2);
    QLabel* nome = new QLabel(ev->getNome());    //inserisco titolo dell'evento
    layout->addWidget(nome,3);
    return eventItem;
}

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

void AgendaVisitor::visit(Deadline& scadenza){
    QListWidgetItem* listItem = new QListWidgetItem(eventiDelGiorno);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&scadenza, layout);
    buildButtons(layout,&scadenza);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&scadenza)));  //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(scadenza.getCompletato() ? QColor(165,214,167) : QColor(225,0,0));
    listItem->setSizeHint(evItem->sizeHint());
    eventiDelGiorno->setItemWidget(listItem, evItem);
}

void AgendaVisitor::visit(Attivita& att){
    QListWidgetItem* listItem = new QListWidgetItem(eventiDelGiorno);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&att, layout);
    QString orarioStr = att.getOraInizio().toString("HH:mm")+"-"+att.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(orarioStr);
    layout->addWidget(orario,3);
    buildButtons(layout,&att);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&att)));   //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(QColor(0,204,204));
    listItem->setSizeHint(evItem->sizeHint());
    eventiDelGiorno->setItemWidget(listItem, evItem);
}

void AgendaVisitor::visit(Riunione& riun){
    QListWidgetItem* listItem = new QListWidgetItem(eventiDelGiorno);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&riun, layout);
    QString orarioStr = riun.getOraInizio().toString("HH:mm")+"-"+riun.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(orarioStr);
    layout->addWidget(orario,3);
    buildButtons(layout,&riun);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&riun)));  //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(QColor(224,224,224));
    listItem->setSizeHint(evItem->sizeHint());
    eventiDelGiorno->setItemWidget(listItem, evItem);
}

void AgendaVisitor::visit(Appuntamento& app){
    QListWidgetItem* listItem = new QListWidgetItem(eventiDelGiorno);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&app, layout);
    QString orarioStr = app.getOraInizio().toString("HH:mm")+"-"+app.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(orarioStr);
    layout->addWidget(orario,3);
    buildButtons(layout,&app);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&app)));   //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(QColor(224,224,224));
    listItem->setSizeHint(evItem->sizeHint());
    eventiDelGiorno->setItemWidget(listItem, evItem);
}
