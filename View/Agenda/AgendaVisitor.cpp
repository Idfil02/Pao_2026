#include "AgendaVisitor.h"
#include <QLabel>
#include <QHBoxLayout>
AgendaVisitor::AgendaVisitor(QListWidget* list):
    eventiDelGiorno(list){}
QWidget* AgendaVisitor::buildListItem(Evento* ev){
    QWidget* eventItem = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(eventItem);
    layout->setContentsMargins(1, 0, 1, 0);
    QLabel* nome = new QLabel(ev->getNome());    //inserisco titolo dell'evento
    layout->addWidget(nome,1);
    return eventItem;
}
void AgendaVisitor::visit(Deadline& scadenza){
    Evento* event = &scadenza;
    QListWidgetItem* item = new QListWidgetItem(eventiDelGiorno);
    QWidget* evItem = buildListItem(event);

    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(scadenza.getCompletato() ? QColor(165,214,167) : QColor(225,0,0));

    eventiDelGiorno->setItemWidget(item, evItem);
}
void AgendaVisitor::visit(Attivita& att){
    Evento* event = &att;
    QListWidgetItem* item = new QListWidgetItem(eventiDelGiorno);
    QWidget* evItem = buildListItem(event);

    QString time = att.getOraInizio().toString("HH:mm")+"-"+att.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    (evItem->layout())->addWidget(orario);

    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(0,204,204));

    eventiDelGiorno->setItemWidget(item, evItem);
}
void AgendaVisitor::visit(Riunione& riunione){
    Evento* event = &riunione;
    QListWidgetItem* item = new QListWidgetItem(eventiDelGiorno);
    QWidget* evItem = buildListItem(event);

    QString time = riunione.getOraInizio().toString("HH:mm")+"-"+riunione.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    evItem->layout()->addWidget(orario);

    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(224,224,224));

    eventiDelGiorno->setItemWidget(item, evItem);
}
void AgendaVisitor::visit(Appuntamento& app){
    Evento* event = &app;
    QListWidgetItem* item = new QListWidgetItem(eventiDelGiorno);
    QWidget* evItem = buildListItem(event);

    QString time = app.getOraInizio().toString("HH:mm")+"-"+app.getOraFine().toString("HH:mm");
    QLabel* orario = new QLabel(time);
    evItem->layout()->addWidget(orario);

    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(224,224,224));

    eventiDelGiorno->setItemWidget(item, evItem);
}
