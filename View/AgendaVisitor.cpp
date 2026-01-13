#include "AgendaVisitor.h"
AgendaVisitor::AgendaVisitor(QListWidget* list):
    eventiDelGiorno(list){}
void AgendaVisitor::visit(Deadline& scadenza){
    Evento* event = &scadenza;
    QListWidgetItem* item = new QListWidgetItem(event->getNome());
    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(Qt::red);
    eventiDelGiorno->addItem(item);
}
void AgendaVisitor::visit(Attivita& att){
    Evento* event = &att;
    QListWidgetItem* item = new QListWidgetItem(event->getNome());
    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(Qt::cyan);
    eventiDelGiorno->addItem(item);
}
void AgendaVisitor::visit(Riunione& riunione){
    Evento* event = &riunione;
    QListWidgetItem* item = new QListWidgetItem(event->getNome());
    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(Qt::yellow);
    eventiDelGiorno->addItem(item);
}
void AgendaVisitor::visit(Appuntamento& app){
    Evento* event = &app;
    QListWidgetItem* item = new QListWidgetItem(event->getNome());
    item->setData(Qt::UserRole, QVariant::fromValue(event));
    item->setBackground(Qt::green);
    eventiDelGiorno->addItem(item);
}
