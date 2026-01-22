#include "Agenda.h"
#include "AgendaVisitor.h"
#include "InfoVisitor.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
Agenda::Agenda(Calendario* cal, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layoutAgenda = new QHBoxLayout(this);
    //creo il lato sx per il calendario
    calendarWidget = new QCalendarWidget;
    layoutAgenda->addWidget(calendarWidget, 2);
    calendario = cal; //collego il campo dati al calendario in memoria
    connect(calendario,&Calendario::aggiuntoEvento,this,&Agenda::dataConImpegni); //collego il segnale di aggiunta evento
    connect(calendarWidget, &QCalendarWidget::clicked, this, &Agenda::giornoSelezionato); //collego il segnale di selezione data
    //creo il container dx per le informazioni deglì eventi
    QWidget* infoContainer = new QWidget(this);
    QVBoxLayout* infoLayout = new QVBoxLayout(infoContainer);
    //lista eventi del giorno
    eventiDelGiorno = new QListWidget;
    connect(eventiDelGiorno,&QListWidget::itemClicked,this,&Agenda::cambioEvento);//collego la selezione di un evento dalla lista del giorno
    infoLayout->addWidget(eventiDelGiorno, 1);
    //informazioni evento
    QWidget* containerDettagliEvento = new QWidget;
    dettagliEvento = new QFormLayout(containerDettagliEvento);
    infoLayout->addWidget(containerDettagliEvento,1);
    layoutAgenda->addWidget(infoContainer, 1);
    giornoSelezionato(QDate::currentDate());
}
void Agenda::clearView(){
    while(dettagliEvento->rowCount()>0){//rimuovo riga per riga ogni campo, se ce ne sono
        dettagliEvento->removeRow(0); //ogni removeRow ricompatta i dettagliEvento
    }
}
void Agenda::giornoSelezionato(const QDate& data){
    eventiDelGiorno->clear(); //pulisco la lista degli eventi
    clearView(); //pulisco la vista
    QVector<Evento*> impegniGiorno = calendario->getImpegni(data); //prendo tutti gli impegni della data selezionata
    AgendaVisitor VST(eventiDelGiorno);
    for(int i=0; i<impegniGiorno.size(); ++i){        //visito gli eventi
        impegniGiorno.at(i)->acceptVisitor(VST);
    }
    if(eventiDelGiorno->count()==0){ //se la data non ha eventi, metto un placeholder per segnalarlo
        QListWidgetItem* placeholder = new QListWidgetItem("Nessun Evento",eventiDelGiorno);
        placeholder->setFlags(Qt::ItemIsSelectable);
    }
    dataConImpegni(data);
}
void Agenda::dataConImpegni(const QDate& data){ //attivato quando si aggiunge un impegno a una data, cambio colore per segnalare
    QTextCharFormat format;
    int num_impegni = calendario->getImpegni(data).size();
    format.setBackground(num_impegni == 0 ? Qt::white : QColor(217,101,43));
    calendarWidget->setDateTextFormat(data, format);
}
void Agenda::cambioEvento(QListWidgetItem* item){ //quando cliccato un evento, mostro i suoi dettagli
    clearView();//ripulisco le informazioni vecchie
    Evento* e = item->data(Qt::UserRole).value<Evento*>(); //recupero il puntatore dalla lista degli eventi
    InfoVisitor IVST(dettagliEvento);
    e->acceptVisitor(IVST); //visito l'evento
}
void Agenda::eventoEliminato(Evento* ev, QDate data){
    calendario->removeEvento(ev);
    giornoSelezionato(data);
}

