#include "Agenda.h"
#include "View/Visitors/AgendaVisitor.h"
#include "View/Visitors/InfoVisitor.h"
#include "qmenu.h"
#include "qpushbutton.h"
#include "qtoolbutton.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>

Agenda::Agenda(Calendario* cal, QWidget *parent) : QWidget(parent), calendario(cal){
    QHBoxLayout* layoutAgenda = new QHBoxLayout(this);
    //creo il lato sx per il calendario
    calendarWidget = new QCalendarWidget;
    calendarWidget->setSelectedDate(QDate::currentDate());
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
    //inizializzazione connessioni
    initConnections();
}

void Agenda::clearInfo(){
    while(dettagliEvento->rowCount()>0){//rimuovo riga per riga ogni campo, se ce ne sono
        dettagliEvento->removeRow(0); //ogni removeRow ricompatta i dettagliEvento
    }
}

void Agenda::giornoSelezionato(const QDate& data){
    eventiDelGiorno->clear(); //pulisco la lista degli eventi
    clearInfo(); //pulisco la vista
    QVector<Evento*> impegniGiorno = calendario->getImpegniByData(data); //prendo tutti gli impegni della data selezionata
    AgendaVisitor av(eventiDelGiorno, this);
    for(int i=0; i<impegniGiorno.size(); ++i){        //visito gli eventi
        impegniGiorno.at(i)->acceptVisitor(av);
    }
    if(eventiDelGiorno->count()==0){ //se la data non ha eventi, metto un placeholder per segnalarlo
        QListWidgetItem* placeholder = new QListWidgetItem("Nessun Evento", eventiDelGiorno);
        placeholder->setFlags(Qt::ItemIsEnabled);
    }
    QListWidgetItem* nuovoEvento = new QListWidgetItem(eventiDelGiorno);
    QToolButton* addNew = new QToolButton;
    addNew->setIcon(QIcon(":/Icons/View/Icons/addnew.svg"));
    addNew->setToolButtonStyle(Qt::ToolButtonIconOnly);
    QMenu* addMenu = new QMenu("Nuovo", this);
    QAction* addAppuntamento = new QAction("Appuntamento",addMenu);
    QAction* addAttivita = new QAction("Attivita",addMenu);
    QAction* addDeadline = new QAction("Deadline",addMenu);
    QAction* addRiunione = new QAction("Riunione",addMenu);
    addMenu->addAction(addAppuntamento);
    addMenu->addAction(addAttivita);
    addMenu->addAction(addDeadline);
    addMenu->addAction(addRiunione);
    addNew->setMenu(addMenu);
    addNew->setPopupMode(QToolButton::InstantPopup);
    addNew->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    //CONNETTERE SEGNALI BOTTONI


    eventiDelGiorno->setItemWidget(nuovoEvento, addNew);
    calendarWidget->setSelectedDate(data);
    dataConImpegni(data);
}

void Agenda::dataConImpegni(const QDate& data) const{ //attivato quando si aggiunge un impegno a una data, cambio colore per segnalare
    QTextCharFormat* format = new QTextCharFormat;
    int numImpegni = calendario->getImpegniByData(data).size();
    format->setBackground(numImpegni == 0 ? Qt::white : QColor(217,101,43));
    calendarWidget->setDateTextFormat(data, *format);
}

void Agenda::decoloraCalendario() const {
    QTextCharFormat* format = new QTextCharFormat;
    format->setBackground(Qt::white);
    calendarWidget->setDateTextFormat(QDate(), *format);
}

void Agenda::cambioEvento(QListWidgetItem* item){ //quando cliccato un evento, mostro i suoi dettagli
    clearInfo();//ripulisco le informazioni vecchie
    Evento* e = item->data(Qt::UserRole).value<Evento*>(); //recupero il puntatore dalla lista degli eventi
    if(e){
        InfoVisitor iv(dettagliEvento);
        e->acceptVisitor(iv); //visito l'evento
    }
}

void Agenda::initConnections(){
    connect(calendario,&Calendario::aggiuntoEvento,this,&Agenda::giornoSelezionato);
    connect(calendarWidget, &QCalendarWidget::clicked, this, &Agenda::giornoSelezionato);
    connect(eventiDelGiorno,&QListWidget::itemClicked,this,&Agenda::cambioEvento);
}
