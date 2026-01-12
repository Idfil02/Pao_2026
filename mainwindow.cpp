#include "mainwindow.h"
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

    Attivita* a1 = new Attivita("Prova", "tag", "desc",
                QDate(2026,1,13),QTime(13,00),QTime(15,00));
    agendaTab->getCalendar()->addEvento(*a1);
}

