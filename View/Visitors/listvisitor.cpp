#include "listvisitor.h"
#include <QLabel>
#include <QPushButton>
ListVisitor::ListVisitor(QListWidget* evs, ListaEventi* listaParent):
    eventi(evs), lista(listaParent){}

QWidget* ListVisitor::buildListItem(Evento* ev, QHBoxLayout* layout){
    QWidget* eventItem = new QWidget;
    eventItem->setLayout(layout);
    layout->setContentsMargins(2, 2, 2, 2);
    QLabel* nome = new QLabel(ev->getNome());    //inserisco titolo dell'evento
    layout->addWidget(nome,3);
    return eventItem;
}
void ListVisitor::buildButtons(QHBoxLayout* layout, Evento* ev){
    ListaEventi* listaLocale = lista;

    QPushButton* tastoGoTO = new QPushButton(QIcon(":/Icons/View/Icons/goto.svg"),"");
    tastoGoTO->setStyleSheet("background-color: green");

    QPushButton* tastoEdit = new QPushButton(QIcon(":/Icons/View/Icons/edit.svg"),"");
    tastoEdit->setStyleSheet("background-color: cyan");

    layout->addWidget(tastoGoTO, 1);
    layout->addWidget(tastoEdit,1);
    QObject::connect(tastoGoTO, &QPushButton::clicked, lista, [listaLocale, ev](){
        listaLocale->emit goTo(ev);
    });
    QObject::connect(tastoEdit, &QPushButton::clicked, lista, [listaLocale, ev](){
        listaLocale->emit richiestaEdit(ev);
    });
}
void ListVisitor::visit(Deadline& scadenza){
    Evento* event = &scadenza;
    QListWidgetItem* item = new QListWidgetItem(eventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(event, layout);
    layout->addStretch(3);
    buildButtons(layout,event);
    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(scadenza.getCompletato() ? QColor(165,214,167) : QColor(225,0,0));
    item->setSizeHint(evItem->sizeHint());
    eventi->setItemWidget(item, evItem);
}


void ListVisitor::visit(Attivita& att){
    Evento* event = &att;
    QListWidgetItem* item = new QListWidgetItem(eventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(event, layout);

    QString time = att.getOraInizio().toString("HH:mm")+"-"+att.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    layout->addWidget(orario,3);
    buildButtons(layout,event);

    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(0,204,204));
    item->setSizeHint(evItem->sizeHint());
    eventi->setItemWidget(item, evItem);
}


void ListVisitor::visit(Riunione& riunione){
    Evento* event = &riunione;
    QListWidgetItem* item = new QListWidgetItem(eventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(event, layout);

    QString time = riunione.getOraInizio().toString("HH:mm")+"-"+riunione.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    layout->addWidget(orario,3);
    buildButtons(layout,event);

    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(224,224,224));
    item->setSizeHint(evItem->sizeHint());
    eventi->setItemWidget(item, evItem);
}


void ListVisitor::visit(Appuntamento& app){
    Evento* event = &app;
    QListWidgetItem* item = new QListWidgetItem(eventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(event, layout);

    QString time = app.getOraInizio().toString("HH:mm")+"-"+app.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    layout->addWidget(orario,3);
    buildButtons(layout,event);

    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(224,224,224));
    item->setSizeHint(evItem->sizeHint());
    eventi->setItemWidget(item, evItem);
}
