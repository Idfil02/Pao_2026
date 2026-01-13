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
    calendario= cal;
    connect(calendario,&Calendario::aggiuntoEvento,this,&Agenda::dataConImpegni);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, &Agenda::viewUpdate);
    //creo il container dx per le informazioni deglì eventi
    QWidget* infoContainer = new QWidget(this);
    QVBoxLayout* infoLayout = new QVBoxLayout(infoContainer);
    //lista eventi del giorno
    eventiDelGiorno = new QListWidget;
    connect(eventiDelGiorno,&QListWidget::itemClicked,this,&Agenda::cambioEvento);
    infoLayout->addWidget(eventiDelGiorno, 1);
    //informazioni evento
    QWidget* containerDettagliEvento = new QWidget;
    dettagliEvento = new QFormLayout(containerDettagliEvento);
    infoLayout->addWidget(containerDettagliEvento,1);
    layoutAgenda->addWidget(infoContainer, 1);
    viewUpdate();
}
void Agenda::clearView(){
    while(dettagliEvento->count()>0){
        QLayoutItem* item = dettagliEvento->takeAt(0);
        item->widget()->deleteLater();
        delete item;
    }
}
void Agenda::viewUpdate(){
    clearView();
    eventiDelGiorno->clear();
    QDate data = calendarWidget->selectedDate();
    QVector<Evento*> impegniGiorno = calendario->getImpegni(data);
    AgendaVisitor VST(eventiDelGiorno);
    for(int i=0; i<impegniGiorno.size(); ++i){
        impegniGiorno.at(i)->acceptVisitor(VST);
    }
    if(eventiDelGiorno->count()==0){
        QListWidgetItem* placeholder = new QListWidgetItem("Nessun Evento per la giornata selezionata");
        placeholder->setFlags(Qt::ItemIsSelectable);
        eventiDelGiorno->addItem(placeholder);
    }
}
void Agenda::dataConImpegni(const QDate& data){
    QTextCharFormat format;
    format.setBackground(Qt::blue);
    format.setFontWeight(QFont::Bold);
    calendarWidget->setDateTextFormat(data, format);
}
void Agenda::cambioEvento(QListWidgetItem* item){
    clearView();
    Evento* e = item->data(Qt::UserRole).value<Evento*>();
    if(e){
        InfoVisitor IVST(dettagliEvento);
        e->acceptVisitor(IVST);
    }
}

