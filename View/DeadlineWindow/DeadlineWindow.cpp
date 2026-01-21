#include "DeadlineWindow.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
DeadlineWindow::DeadlineWindow(Calendario* cal, QWidget *parent) : QWidget(parent), calendario(cal)
{
    //prende tutte le attività che sono scadenze e le aggiunge al vettore interno
    QVector<Evento*> impegni = cal->getImpegni();
    for(int i=0; i<impegni.size(); ++i){
        if(dynamic_cast<Deadline*>(impegni[i])){ //voglio inserire nella lista solo le scadenze
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
    dettagliDeadline->setPlaceholderText("Selezionare una scadenza per visualizzare i dettagli"); //se per caso la scadenza non ha descrizone
    layoutDeadline->addWidget(dettagliDeadline);
    viewRefresh();//visualizzo la lista
}
QWidget* DeadlineWindow::buildDeadlineItem(Deadline* d){
    //creo l'oggetto
    QWidget* deadlineItem = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(deadlineItem);
    layout->setContentsMargins(1, 2, 1, 2);
    //creo la spunta
    QCheckBox* checkbox = new QCheckBox;
    checkbox->setChecked(d->getCompletato());
    layout->addWidget(checkbox);
    //quando cliccata la checkbox modifico la scadenza e aggiorno
    connect(checkbox, &QCheckBox::checkStateChanged, this, [this,d](Qt::CheckState stato){
        d->setCompletato(stato);
        viewRefresh();
    });
    //aggiungo il nome della scadenza d
    QLabel* nome = new QLabel(d->getNome());
    layout->addWidget(nome,2);
    //aggiungo la data di scadenza di d
    QString scad = "Scadenza: " + d->getData().toString("dd/MM/yyyy");
    QLabel* termine = new QLabel(scad);
    layout->addWidget(termine,2);
    //aggiungo pulsante per l'eliminazione
    QPushButton* tastoElimina = new QPushButton("Elimina");
    tastoElimina->setStyleSheet("background-color: red");
    connect(tastoElimina, &QPushButton::clicked, this, [this,d](){
        this->deadlines.removeOne(d);
        this->calendario->removeEvento(*d);
        viewRefresh();
        dettagliDeadline->clear();
    });
    layout->addWidget(tastoElimina);
    return deadlineItem;
}

void DeadlineWindow::viewRefresh(){
    //pulisco la lista
    scadenze->clear();
    //rigenero gli oggetti per ogni elemento del vettore delle scadenze
    for(int i=0; i<deadlines.size(); ++i){
        //costruisco un nuovo elemento della lista a partire dalla Deadline
        Deadline* scad = deadlines.at(i);
        QListWidgetItem* item = new QListWidgetItem(scadenze);
        QWidget* dItem = buildDeadlineItem(scad);
        item->setBackground(scad->getCompletato() ? QColor(165,214,167) : Qt::gray);
        item->setData(Qt::UserRole,QVariant::fromValue(scad));//allego il puntatore
        //aggiungo l'oggetto alla lista
        scadenze->setItemWidget(item, dItem);
        connect(scadenze, &QListWidget::itemClicked, this, [this](QListWidgetItem* item){
            dettagliDeadline->clear();//pulisco la descrizione
            Deadline* d = item->data(Qt::UserRole).value<Deadline*>();//recupero l'oggetto collegato all'elemento selezionato
            dettagliDeadline->setText(d->getDesc());
        });//connetto il segnale allo slot per mostrare le informazioni
    }
}
