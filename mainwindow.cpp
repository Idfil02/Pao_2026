#include "mainwindow.h"
#include "Model/Attivita.h"
#include "Model/Deadline.h"
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

    // Create and add Agenda tab
    Agenda* agendaTab = new Agenda(this);
    tabWidgets->addTab(agendaTab, "Agenda");

    // Create and add Deadlines tab
    DeadlineWindow* deadlinesTab = new DeadlineWindow(this);
    tabWidgets->addTab(deadlinesTab, "Scadenze");

    //Aggiunta del Menu
    Menu* menu = new Menu;
    addToolBar(Qt::TopToolBarArea, menu);

    Evento* e1 = new Deadline("SCADENZA","TAG#1","DESC#1",QDate(2026,01,20));
    Evento* e2 = new Attivita("ATTIVITA","TAG#2","DESC#2",QDate(2026,01,20),QTime(12,00),QTime(13,00));
    agendaTab->getCalendar()->addEvento(e1);
    agendaTab->getCalendar()->addEvento(e2);
}

