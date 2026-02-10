#include "Agenda.h"
#include "View/Visitors/AgendaVisitor.h"
#include "View/Visitors/InfoVisitor.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
Agenda::Agenda(Calendario* cal, QWidget *parent) : QWidget(parent), calendario(cal){
    QHBoxLayout* layoutAgenda = new QHBoxLayout(this);
    //creo il lato sx per il calendario
    calendarWidget = new QCalendarWidget;
    layoutAgenda->addWidget(calendarWidget, 2);
    //creo il container dx per le informazioni degli eventi
    QWidget* infoContainer = new QWidget(this);
    QVBoxLayout* infoLayout = new QVBoxLayout(infoContainer);
    layoutAgenda->addWidget(infoContainer, 1);

    //lista eventi del giorno
    eventiDelGiorno = new QListWidget;
    infoLayout->addWidget(eventiDelGiorno, 1);

    //informazioni evento
    QWidget* containerDettagliEvento = new QWidget;
    dettagliEvento = new QFormLayout(containerDettagliEvento);
    infoLayout->addWidget(containerDettagliEvento,1);

    initConnections();

    calendarWidget->setSelectedDate(QDate::currentDate());
}


void Agenda::clearInfo(){
    while(dettagliEvento->rowCount()>0){//rimuovo riga per riga ogni campo, se ce ne sono
        dettagliEvento->removeRow(0); //ogni removeRow ricompatta i dettagliEvento
    }
}


void Agenda::giornoSelezionato(const QDate& data){
    eventiDelGiorno->clear(); //pulisco la lista degli eventi
    clearInfo(); //pulisco la vista
    QVector<Evento*> impegniGiorno = calendario->getImpegni(data); //prendo tutti gli impegni della data selezionata
    AgendaVisitor VST(eventiDelGiorno, this);
    for(int i=0; i<impegniGiorno.size(); ++i){        //visito gli eventi
        impegniGiorno.at(i)->acceptVisitor(VST);
    }

    if(eventiDelGiorno->count()==0){ //se la data non ha eventi, metto un placeholder per segnalarlo
        QListWidgetItem* placeholder = new QListWidgetItem("Nessun Evento", eventiDelGiorno);
        placeholder->setFlags(Qt::ItemIsEnabled);
    }

    dataConImpegni(data);
    calendarWidget->setSelectedDate(data);
}


void Agenda::dataConImpegni(const QDate& data) const{ //attivato quando si aggiunge un impegno a una data, cambio colore per segnalare
    QTextCharFormat* format = new QTextCharFormat;
    int num_impegni = calendario->getImpegni(data).size();
    format->setBackground(num_impegni == 0 ? Qt::white : QColor(217,101,43));
    calendarWidget->setDateTextFormat(data, *format);
}


void Agenda::cambioEvento(QListWidgetItem* item){ //quando cliccato un evento, mostro i suoi dettagli
    clearInfo();//ripulisco le informazioni vecchie
    Evento* e = item->data(Qt::UserRole).value<Evento*>(); //recupero il puntatore dalla lista degli eventi
    if(e){
        InfoVisitor IVST(dettagliEvento);
        e->acceptVisitor(IVST); //visito l'evento
    }
}


void Agenda::initConnections(){
    connect(calendario,&Calendario::aggiuntoEvento,this,&Agenda::giornoSelezionato);
    connect(calendarWidget, &QCalendarWidget::clicked, this, &Agenda::giornoSelezionato);
    connect(eventiDelGiorno,&QListWidget::itemClicked,this,&Agenda::cambioEvento);
}
