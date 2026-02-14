#include "View/Visitors/ListVisitor.h"
#include <QLabel>
ListVisitor::ListVisitor(QListWidget* listaParent): listaEventi(listaParent){}
QWidget* ListVisitor::buildListItem(Evento* ev, QHBoxLayout* layout){
    QWidget* eventItem = new QWidget;
    eventItem->setLayout(layout);
    layout->setContentsMargins(1, 1, 1, 1);
    QLabel* nome = new QLabel(ev->getNome());
    layout->addWidget(nome,3);
    return eventItem;
}

void ListVisitor::visit(Deadline& scadenza){
    QListWidgetItem* listItem = new QListWidgetItem(listaEventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&scadenza, layout);
    layout->addStretch(3);
    buildButtons(layout,&scadenza);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&scadenza)));  //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(scadenza.getCompletato() ? QColor(165,214,167) : QColor(225,0,0));
    listItem->setSizeHint(evItem->sizeHint());
    listaEventi->setItemWidget(listItem, evItem);
}

void ListVisitor::visit(Attivita& att){
    QListWidgetItem* listItem = new QListWidgetItem(listaEventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&att, layout);
    QString orarioStr = att.getOraInizio().toString("HH:mm")+"-"+att.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(orarioStr);
    layout->addWidget(orario,3);
    buildButtons(layout,&att);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&att)));   //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(QColor(127, 165, 245));
    listItem->setSizeHint(evItem->sizeHint());
    listaEventi->setItemWidget(listItem, evItem);
}

void ListVisitor::visit(Riunione& riun){
    QListWidgetItem* listItem = new QListWidgetItem(listaEventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&riun, layout);
    QString orarioStr = riun.getOraInizio().toString("HH:mm")+"-"+riun.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(orarioStr);
    layout->addWidget(orario,3);
    buildButtons(layout,&riun);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&riun)));  //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(QColor(203, 156, 230));
    listItem->setSizeHint(evItem->sizeHint());
    listaEventi->setItemWidget(listItem, evItem);
}

void ListVisitor::visit(Appuntamento& app){
    QListWidgetItem* listItem = new QListWidgetItem(listaEventi);
    QHBoxLayout* layout = new QHBoxLayout;
    QWidget* evItem = buildListItem(&app, layout);
    QString orarioStr = app.getOraInizio().toString("HH:mm")+"-"+app.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(orarioStr);
    layout->addWidget(orario,3);
    buildButtons(layout,&app);
    listItem->setData(Qt::UserRole, QVariant::fromValue(static_cast<Evento*>(&app)));   //cast esplicito a Evento in quanto Qvariant non converte automaticamente i sottotipi
    listItem->setBackground(QColor(224, 197, 117));
    listItem->setSizeHint(evItem->sizeHint());
    listaEventi->setItemWidget(listItem, evItem);
}
