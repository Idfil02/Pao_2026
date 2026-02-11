#include "ListVisitor.h"
#include <QLabel>
#include <QPushButton>

ListVisitor::ListVisitor(QListWidget* evs, ListaEventi* listaParent):
    eventi(evs), lista(listaParent){}

//metodo di utility per la visulazzazione di un evento nella lista eventi
QWidget* ListVisitor::buildListItem(Evento* ev, QHBoxLayout* layout){
    QWidget* eventItem = new QWidget;
    eventItem->setLayout(layout);
    layout->setContentsMargins(2, 2, 2, 2);
    QLabel* nome = new QLabel(ev->getNome());
    layout->addWidget(nome,3);
    return eventItem;
}

//metodo di utility per la visuallazzione dei bottoni a lato dei singoli eventi listati
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
    QListWidgetItem* listItem = new QListWidgetItem(eventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&scadenza, layout);
    layout->addStretch(3);
    buildButtons(layout,&scadenza);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&scadenza)));  //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(scadenza.getCompletato() ? QColor(165,214,167) : QColor(225,0,0));
    listItem->setSizeHint(evItem->sizeHint());
    eventi->setItemWidget(listItem, evItem);
}

void ListVisitor::visit(Attivita& att){
    QListWidgetItem* listItem = new QListWidgetItem(eventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&att, layout);
    QString time = att.getOraInizio().toString("HH:mm")+"-"+att.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    layout->addWidget(orario,3);
    buildButtons(layout,&att);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&att)));   //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(QColor(0,204,204));
    listItem->setSizeHint(evItem->sizeHint());
    eventi->setItemWidget(listItem, evItem);
}

void ListVisitor::visit(Riunione& riunione){
    QListWidgetItem* listItem = new QListWidgetItem(eventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&riunione, layout);
    QString time = riunione.getOraInizio().toString("HH:mm")+"-"+riunione.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    layout->addWidget(orario,3);
    buildButtons(layout,&riunione);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&riunione)));  //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(QColor(224,224,224));
    listItem->setSizeHint(evItem->sizeHint());
    eventi->setItemWidget(listItem, evItem);
}

void ListVisitor::visit(Appuntamento& app){
    QListWidgetItem* listItem = new QListWidgetItem(eventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&app, layout);
    QString time = app.getOraInizio().toString("HH:mm")+"-"+app.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    layout->addWidget(orario,3);
    buildButtons(layout,&app);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&app)));   //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(QColor(224,224,224));
    listItem->setSizeHint(evItem->sizeHint());
    eventi->setItemWidget(listItem, evItem);
}
