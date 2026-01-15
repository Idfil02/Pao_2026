#include "AgendaVisitor.h"
#include <QLabel>
#include <QHBoxLayout>
AgendaVisitor::AgendaVisitor(QListWidget* list):
    eventiDelGiorno(list){}
QWidget* AgendaVisitor::buildListItem(Evento* ev){
    QWidget* eventItem = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(eventItem);
    layout->setContentsMargins(1, 0, 1, 0);
    QLabel* nome = new QLabel(ev->getNome()); //inserisco titolo dell'evento
    layout->addWidget(nome);
    if(!dynamic_cast<Deadline*>(ev)){ // se non è una Deadline allora mostro anche l'orario dell'impegno
        Attivita* att = static_cast<Attivita*>(ev); //sono sicuro che non è deadline e quindi sono sicuro avrà orario di inizio e fine
        QString time = att->getOraInizio().toString("HH:mm")+"-"+att->getOraFine().toString("HH:mm");
        QLabel* dx = new QLabel(time);
        layout->addWidget(dx);
    }
    return eventItem;
}
void AgendaVisitor::visit(Deadline& scadenza){
    Evento* event = &scadenza;
    QListWidgetItem* item = new QListWidgetItem;
    QWidget* evItem = buildListItem(event);
    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(255,51,51));
    eventiDelGiorno->addItem(item);
    eventiDelGiorno->setItemWidget(item, evItem);
}
void AgendaVisitor::visit(Attivita& att){
    Evento* event = &att;
    QListWidgetItem* item = new QListWidgetItem;
    QWidget* evItem = buildListItem(event);
    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(0,204,204));
    eventiDelGiorno->addItem(item);
    eventiDelGiorno->setItemWidget(item, evItem);
}
void AgendaVisitor::visit(Riunione& riunione){
    Evento* event = &riunione;
    QListWidgetItem* item = new QListWidgetItem;
    QWidget* evItem = buildListItem(event);
    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(224,224,224));
    eventiDelGiorno->addItem(item);
    eventiDelGiorno->setItemWidget(item, evItem);
}
void AgendaVisitor::visit(Appuntamento& app){
    Evento* event = &app;
    QListWidgetItem* item = new QListWidgetItem;
    QWidget* evItem = buildListItem(event);
    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(QColor(224,224,224));
    eventiDelGiorno->addItem(item);
    eventiDelGiorno->setItemWidget(item, evItem);
}
