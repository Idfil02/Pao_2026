#include "Agenda.h"
#include "AgendaVisitor.h"
#include "InfoVisitor.h"
#include <QFormLayout>
#include <QLabel>
Agenda::Agenda(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layoutAgenda = new QHBoxLayout(this);

    calendarWidget = new QCalendarWidget;
    layoutAgenda->addWidget(calendarWidget, 2);

    calendario= new Calendario(this);
    connect(calendario,&Calendario::aggiuntoEvento,this,&Agenda::dataConImpegni);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, &Agenda::viewUpdate);

    splitterGiorno = new QSplitter(Qt::Vertical);

    eventiDelGiorno = new QListWidget;
    connect(eventiDelGiorno,&QListWidget::itemClicked,this,&Agenda::cambioEvento);
    splitterGiorno->addWidget(eventiDelGiorno);
    splitterGiorno->setStretchFactor(0, 2);

    QWidget* containerDettagliEvento = new QWidget;
    dettagliEvento = new QFormLayout;
    containerDettagliEvento->setLayout(dettagliEvento);
    splitterGiorno->addWidget(containerDettagliEvento);
    splitterGiorno->setStretchFactor(1, 2);

    layoutAgenda->addWidget(splitterGiorno, 2);
}
void Agenda::clearView(){
    if(!dettagliEvento) return;
    QLayoutItem *child;
    while ((child = dettagliEvento->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }
}
void Agenda::dataConImpegni(const QDate& data){
    QTextCharFormat format;
    format.setBackground(Qt::blue);
    format.setFontWeight(QFont::Bold);
    calendarWidget->setDateTextFormat(data, format);
}
void Agenda::viewUpdate(){
    eventiDelGiorno->clear();
    QDate data = calendarWidget->selectedDate();
    QVector<Evento*> impegniGiorno = calendario->getImpegni(data);
    AgendaVisitor VST(eventiDelGiorno);
    for(int i=0; i<impegniGiorno.size(); ++i){
        impegniGiorno.at(i)->acceptVisitor(VST);
    }
}
void Agenda::cambioEvento(QListWidgetItem* item){
    clearView();
    Evento* e = item->data(Qt::UserRole).value<Evento*>();
    if(e){
        InfoVisitor IVST(dettagliEvento);
        e->acceptVisitor(IVST);
    }
}

