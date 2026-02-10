#include "DeadlineWindow.h"
#include "View/Visitors//InfoVisitor.h"
#include "qtextedit.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>

DeadlineWindow::DeadlineWindow(Calendario* cal, QWidget *parent) : QWidget(parent), calendario(cal){
    QVBoxLayout* layoutDeadline = new QVBoxLayout(this);
    scadenze = new QListWidget;
    layoutDeadline->addWidget(scadenze,1);
    //crea i dettagli delle scadenze
    dettagliDeadline = new QWidget(this);
    dettagliLayout = new QFormLayout(dettagliDeadline);
    layoutDeadline->addWidget(dettagliDeadline,1);
    viewRefresh();//visualizzo la lista
}

QWidget* DeadlineWindow::buildDeadlineItem(Deadline* d){
    QWidget* deadlineItem = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout(deadlineItem);
    layout->setContentsMargins(2, 2, 2, 2);
    //creo la spunta
    QCheckBox* checkbox = new QCheckBox;
    checkbox->setChecked(d->getCompletato());
    layout->addWidget(checkbox);
    //aggiungo il nome della scadenza d
    QLabel* nome = new QLabel(d->getNome());
    layout->addWidget(nome,2);
    //aggiungo la data di scadenza di d
    QString scad = "Scadenza: " + d->getData().toString("dd/MM/yyyy");
    QLabel* termine = new QLabel(scad);
    layout->addWidget(termine,2);
    //aggiungo pulsante per la modifica
    QPushButton* tastoEdit = new QPushButton(QIcon(":/Icons/View/Icons/edit.svg"),"");
    tastoEdit->setStyleSheet("background-color: cyan");
    layout->addWidget(tastoEdit);
    //aggiungo pulsante per l'eliminazione
    QPushButton* tastoElimina = new QPushButton(QIcon(":/Icons/View/Icons/deleteIcon.svg"),"\0");
    tastoElimina->setStyleSheet("background-color: red");
    layout->addWidget(tastoElimina);
    //quando viene cliccata la checkbox modifico la scadenza d e aggiorno la visualizzazione
    connect(checkbox, &QCheckBox::checkStateChanged, this, [this,d](Qt::CheckState stato){
        d->setCompletato(stato);
        viewRefresh();
        emit deadlineModificata(d->getData());
    });
    connect(tastoEdit, &QPushButton::clicked, this, [this,d](){
        emit richiestaEdit(d);
    });
    connect(tastoElimina, &QPushButton::clicked, this, [this,d](){
        clearInfo();
        deleteDeadline(d);
        emit eventoEliminato(d,d->getData());
    });
    return deadlineItem;
}

void DeadlineWindow::viewRefresh(){
    clearInfo();
    scadenze->clear();
    //rigenero la lista delle scadenze visualizzate a partire dal vettore deadlines aggiornato
    for(int i=0; i<deadlines.size(); ++i){
        Deadline* scad = deadlines.at(i);
        QListWidgetItem* item = new QListWidgetItem(scadenze);
        QWidget* dItem = buildDeadlineItem(scad);
        item->setBackground(scad->getCompletato() ? QColor(165,214,167) : Qt::gray);
        item->setData(Qt::UserRole,QVariant::fromValue(scad));//allego il puntatore
        scadenze->setItemWidget(item, dItem);
    }
    //visualizzazione dettagli in caso lista vuota
    if(dettagliLayout->count() == 0){
        QTextEdit* placeholder = new QTextEdit;
        placeholder->setReadOnly(true);
        placeholder->setPlaceholderText("Selezionare scadenza per maggiori informazioni");
        dettagliLayout->addRow(placeholder);
    }
    //connetto il segnale allo slot per mostrare le informazioni
    connect(scadenze, &QListWidget::itemClicked, this, [this](QListWidgetItem* item){
        clearInfo();
        Deadline* d = item->data(Qt::UserRole).value<Deadline*>();//recupero l'oggetto collegato all'elemento selezionato
        if(d){
            InfoVisitor visitor(dettagliLayout);
            d->acceptVisitor(visitor);
        }
    });
}

//pulisce i dettagli della deadline
void DeadlineWindow::clearInfo(){
    while(dettagliLayout->count()){
        dettagliLayout->removeRow(0);
    }
}

void DeadlineWindow::addDeadline(Deadline* d){
    deadlines.append(d);
}

void DeadlineWindow::clearDeadlines(){
    deadlines.clear();
}

void DeadlineWindow::deleteDeadline(Deadline* d){
    deadlines.removeAll(d);
}
