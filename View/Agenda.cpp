#include "Agenda.h"

Agenda::Agenda(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layoutAgenda = new QHBoxLayout(this);

    calendarWidget = new QCalendarWidget;
    layoutAgenda->addWidget(calendarWidget, 2);

    calendario= new Calendario(this);
    connect(calendario,&Calendario::aggiuntoEvento,this,&Agenda::dataConImpegni);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, &Agenda::cambioData);

    splitterGiorno = new QSplitter(Qt::Vertical);

    eventiDelGiorno = new QListWidget;
    splitterGiorno->addWidget(eventiDelGiorno);
    splitterGiorno->setStretchFactor(0, 2);

    dettagliEvento = new QTextEdit;
    dettagliEvento->setPlaceholderText("Qui ci va la descrizione dell'evento");
    splitterGiorno->addWidget(dettagliEvento);
    splitterGiorno->setStretchFactor(1, 2);

    layoutAgenda->addWidget(splitterGiorno, 2);
}
void Agenda::dataConImpegni(const QDate& data){
    QTextCharFormat format;
    format.setBackground(Qt::cyan);
    format.setFontWeight(QFont::Bold);
    calendarWidget->setDateTextFormat(data, format);
}
void Agenda::cambioData(){
    QDate data = calendarWidget->selectedDate();
    viewUpdate(data);
}
void Agenda::viewUpdate(const QDate& data){
    eventiDelGiorno->clear();
    QVector<Evento*> impegniGiorno = calendario->getImpegni(data);
    for(int i=0; i<impegniGiorno.size(); ++i){
        eventiDelGiorno->addItem(impegniGiorno[i]->getNome());
    }
}
