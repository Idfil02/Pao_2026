#include "mainwindow.h"
#include "Model/Attivita.h"
#include "Model/Deadline.h"
#include "Model/Appuntamento.h"
#include "Model/Riunione.h"
#include "View/Agenda/Agenda.h"
#include "View/DeadlineWindow/DeadlineWindow.h"
#include "View/Menu/Menu.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Set window properties
    setWindowTitle("Agenda - PAO 2026");
    // Create main tab widget
    QTabWidget* tabWidgets = new QTabWidget(this);
    setCentralWidget(tabWidgets);
    Calendario* calendario = new Calendario(this);
    Evento* e1 = new Deadline("COMPLETARE PROGETTO","TAG#1","DESC#1",QDate(2026,01,20));
    Evento* e2 = new Attivita("ATTIVITA","TAG#2","DESC#2",QDate(2026,01,20),QTime(12,00),QTime(13,00));
    Evento* e3 = new Deadline("CONSEGNARE RELAZIONE","TAG#2","DESC#3",QDate(2026,01,22));
    Evento* e4 = new Appuntamento("DOTTORE","TAG#2","DESC#2",QDate(2026,02,10),QTime(12,00),QTime(13,00),"INDIRIZZO OSPEDALE","123456");
    Deadline* e5 = new Deadline("PAGARE TASSE","TAG#3","DESC#4",QDate(2026,01,23));
    Riunione* e6 = new Riunione("RIUNIONE","TAG#2","DESC#2",QDate(2026,02,26),QTime(12,00),QTime(13,00),"https://www.google.com");
    QVector<QString> part = {"PERSONA 1", "PERSONA 2","PERSONA 3"};
    e6->setPartecipanti(part);
    e5->setCompletato(true);
    // Create and add Agenda tab
    Agenda* agendaTab = new Agenda(calendario,this);
    tabWidgets->addTab(agendaTab, "Agenda");
    calendario->addEvento(e1);
    calendario->addEvento(e2);
    calendario->addEvento(e3);
    calendario->addEvento(e4);
    calendario->addEvento(e5);
    calendario->addEvento(e6);
    // Create and add Deadlines tab
    DeadlineWindow* deadlinesTab = new DeadlineWindow(calendario,this);
    tabWidgets->addTab(deadlinesTab, "Scadenze");
    connect(deadlinesTab, &DeadlineWindow::eventoEliminato, agendaTab, &Agenda::eventoEliminato);
    //Aggiunta del Menu
    Menu* menu = new Menu(calendario, this);
    addToolBar(Qt::TopToolBarArea, menu);
}

