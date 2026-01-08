#include "Agenda.h"

Agenda::Agenda(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layoutAgenda = new QHBoxLayout(this);

    calendario = new QCalendarWidget;
    layoutAgenda->addWidget(calendario, 2);

    splitterGiorno = new QSplitter(Qt::Vertical);

    eventiDelGiorno = new QListWidget;
    eventiDelGiorno->addItem("Evento di Prova #1");
    eventiDelGiorno->addItem("Evento di Prova #2");
    splitterGiorno->addWidget(eventiDelGiorno);
    splitterGiorno->setStretchFactor(0, 2);

    dettagliEvento = new QTextEdit;
    dettagliEvento->setPlaceholderText("Qui ci va la descrizione dell'evento");
    splitterGiorno->addWidget(dettagliEvento);
    splitterGiorno->setStretchFactor(1, 2);

    layoutAgenda->addWidget(splitterGiorno, 2);
}
