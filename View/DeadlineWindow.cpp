#include "DeadlineWindow.h"

DeadlineWindow::DeadlineWindow(Calendario* cal, QWidget *parent) : QWidget(parent)
{
    //prende tutte le attività che sono scadenze e le aggiunge al calendario
    QVector<Evento*> impegni = cal->getImpegni();
    for(int i=0; i<impegni.size(); ++i){
        if(dynamic_cast<Deadline*>(impegni[i])){
            deadlines.append(static_cast<Deadline*>(impegni[i]));
        }
    }
    QVBoxLayout* layoutDeadline = new QVBoxLayout(this);
    //crea la lista delle scadenze
    scadenze = new QListWidget;
    layoutDeadline->addWidget(scadenze);
    //crea i dettagli delle scadenze
    dettagliDeadline = new QTextEdit;
    dettagliDeadline->setReadOnly(true);
    dettagliDeadline->setPlaceholderText("Descrizione Scadenza");
    layoutDeadline->addWidget(dettagliDeadline);
    connect(scadenze, &QListWidget::itemClicked, this, &DeadlineWindow::scadenzaSelezionata);
    viewRefresh();
}

void DeadlineWindow::viewRefresh(){
    scadenze->clear();
    for(int i=0; i<deadlines.size(); ++i){
        Deadline* scad = deadlines[i];
        QListWidgetItem* item = new QListWidgetItem(scad->getNome());
        item->setData(Qt::UserRole,QVariant::fromValue(scad));
        scadenze->addItem(item);
    }
}
void DeadlineWindow::scadenzaSelezionata(QListWidgetItem* item){
    dettagliDeadline->clear();
    Deadline* d = item->data(Qt::UserRole).value<Deadline*>();
    dettagliDeadline->setText(d->getDesc());
}
