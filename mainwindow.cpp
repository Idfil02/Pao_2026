#include "mainwindow.h"
#include "Model/Attivita.h"
#include "Model/Deadline.h"
#include "Model/Appuntamento.h"
#include "Model/Riunione.h"
#include "View/Agenda.h"
#include "View/DeadlineWindow.h"
#include "View/Menu.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Set window properties
    setWindowTitle("Agenda - PAO 2026");
    // Create main tab widget
    QTabWidget* tabWidgets = new QTabWidget(this);
    setCentralWidget(tabWidgets);
    Calendario* calendario = new Calendario(this);

    // Create and add Agenda tab
    Agenda* agendaTab = new Agenda(calendario,this);
    tabWidgets->addTab(agendaTab, "Agenda");
    Evento* e1 = new Deadline("SCADENZA","TAG#1","DESC#1",QDate(2026,01,20));
    Evento* e2 = new Attivita("ATTIVITA","TAG#2","DESC#2",QDate(2026,01,20),QTime(12,00),QTime(13,00));
    Evento* e3 = new Deadline("SCADENZA #2","TAG#2","DESC#3",QDate(2026,01,22));
    Evento* e4 = new Appuntamento("UROLOGO","TAG#2","DESC#2",QDate(2026,02,10),QTime(12,00),QTime(13,00),"VIA CAZZI 15","123456");
    Evento* e5 = new Deadline("SCADENZA #3","TAG#3","DESC#4",QDate(2026,01,23));
    Riunione* e6 = new Riunione("RIUNIONE","TAG#2","DESC#2",QDate(2026,02,26),QTime(12,00),QTime(13,00),"https://www.google.com");
    QVector<QString> part = {"PERSONA 1", "PERSONA 2","PERSONA 3"};
    e6->setPartecipanti(part);
    agendaTab->getCalendar()->addEvento(e1);
    agendaTab->getCalendar()->addEvento(e2);
    agendaTab->getCalendar()->addEvento(e3);
    agendaTab->getCalendar()->addEvento(e4);
    agendaTab->getCalendar()->addEvento(e5);
    agendaTab->getCalendar()->addEvento(e6);
    // Create and add Deadlines tab
    DeadlineWindow* deadlinesTab = new DeadlineWindow(calendario,this);
    tabWidgets->addTab(deadlinesTab, "Scadenze");

    //Aggiunta del Menu
    Menu* menu = new Menu;
    addToolBar(Qt::TopToolBarArea, menu);


}

