#include "DeadlineWindow.h"
#include <QLabel>
#include <QHBoxLayout>
DeadlineWindow::DeadlineWindow(Calendario* cal, QWidget *parent) : QWidget(parent)
{
    //prende tutte le attività che sono scadenze e le aggiunge al vettore interno
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
    dettagliDeadline->setPlaceholderText("Nessuna Descrizione per la scadenza selezionata"); //se per caso la scadenza non ha descrizone
    layoutDeadline->addWidget(dettagliDeadline);
    connect(scadenze, &QListWidget::itemClicked, this, &DeadlineWindow::scadenzaSelezionata);//connetto il segnale allo slot per mostrare le informazioni
    viewRefresh();//visualizzo la lista
}
QWidget* DeadlineWindow::buildDeadlineItem(Deadline* d){
    //creo l'oggetto
    QWidget* deadlineItem = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(deadlineItem);
    layout->setContentsMargins(1, 1, 1, 1);
    //aggiungo il nome della scadenza d
    QLabel* nome = new QLabel(d->getNome());
    layout->addWidget(nome);
    //aggiungo la data di scadenza di d
    QString scad = "Scadenza: " + d->getData().toString("dd/MM/yyyy");
    QLabel* termine = new QLabel(scad);
    layout->addWidget(termine);
    return deadlineItem;
}
void DeadlineWindow::viewRefresh(){
    //pulisco la lista
    scadenze->clear();
    //rigenero gli oggetti per ogni elemento del vettore delle scadenze
    for(int i=0; i<deadlines.size(); ++i){
        //costruisco un nuovo elemento della lista a partire dalla Deadline
        Deadline* scad = deadlines[i];
        QListWidgetItem* item = new QListWidgetItem;
        QWidget* dItem = buildDeadlineItem(scad);
        if(scad->getCompletato()){
            item->setBackground(QColor(165,214,167));//se è completata la segno di verde
        }else{
            item->setBackground(Qt::gray);//se non è completata in grigio
        }
        item->setData(Qt::UserRole,QVariant::fromValue(scad));//allego il puntatore
        //aggiungo l'oggetto alla lista
        scadenze->addItem(item);
        scadenze->setItemWidget(item, dItem);
    }
}
void DeadlineWindow::scadenzaSelezionata(QListWidgetItem* item){
    dettagliDeadline->clear();//pulisco la descrizione
    Deadline* d = item->data(Qt::UserRole).value<Deadline*>();//recupero l'oggetto collegato all'elemento selezionato
    dettagliDeadline->setText(d->getDesc());//metto la descrizione della Deadline nell'area di testo
}
