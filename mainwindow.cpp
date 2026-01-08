#include "mainwindow.h"
#include <QCalendarWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QTabWidget>
#include <QSplitter>
#include <QHBoxLayout>
#include <QWidget>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    QTabWidget* tabWidgets = new QTabWidget(this);
    setWindowTitle("Agenda - PAO 2026");
    setCentralWidget(tabWidgets);

//TAB CALENDARIO + EVENTI
    QWidget* tabCalendario = new QWidget;
    QHBoxLayout* layoutAgenda = new QHBoxLayout(tabCalendario);

    QCalendarWidget* calendario = new QCalendarWidget; //Calendario [sx]
    layoutAgenda->addWidget(calendario, 2);

    QSplitter* splitterGiorno = new QSplitter(Qt::Vertical); //Eventi del giorno + Dettagli Evento [dx]

    QListWidget* eventiDelGiorno = new QListWidget;
    eventiDelGiorno->addItem("Evento di Prova #1");
    eventiDelGiorno->addItem("Evento di Prova #2");
    splitterGiorno->addWidget(eventiDelGiorno);
    splitterGiorno->setStretchFactor(0, 2);

    QTextEdit* dettagliEvento = new QTextEdit;
    dettagliEvento->setPlaceholderText("Qui ci va la descrizione dell'evento");
    splitterGiorno->addWidget(dettagliEvento);
    splitterGiorno->setStretchFactor(1, 2);

    layoutAgenda->addWidget(splitterGiorno, 2);

    tabWidgets->addTab(tabCalendario, "Agenda");

//TAB DEADLINE
    QWidget* tabDeadline = new QWidget;
    QVBoxLayout* layoutDeadline = new QVBoxLayout(tabDeadline);

    QListWidget* scadenze = new QListWidget; //lista delle scadenze [sopra]
    layoutDeadline->addWidget(scadenze);

    QTextEdit* dettagliDeadline = new QTextEdit; //dettagli della deadline [sotto]
    dettagliDeadline->setReadOnly(true);
    dettagliDeadline->setPlaceholderText("Descrizione Scadenza");
    layoutDeadline->addWidget(dettagliDeadline);

    tabWidgets->addTab(tabDeadline, "Scadenze");
}

