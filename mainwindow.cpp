#include "mainwindow.h"
#include "View/Agenda.h"
#include "View/DeadlineWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Set window properties
    setWindowTitle("Agenda - PAO 2026");

    // Create main tab widget
    tabWidgets = new QTabWidget(this);
    setCentralWidget(tabWidgets);

    // Create and add Agenda tab
    agendaTab = new Agenda(this);
    tabWidgets->addTab(agendaTab, "Agenda");

    // Create and add Deadlines tab
    deadlinesTab = new DeadlineWindow(this);
    tabWidgets->addTab(deadlinesTab, "Scadenze");
}

