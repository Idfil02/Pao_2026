#include "mainwindow.h"
/*#include "Model/Attivita.h"
#include "Model/Deadline.h"
#include "Model/Appuntamento.h"
#include "Model/Riunione.h"*/
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
    // Create and add Agenda tab
    Agenda* agendaTab = new Agenda(calendario,this);
    tabWidgets->addTab(agendaTab, "Agenda");
    // Create and add Deadlines tab
    DeadlineWindow* deadlinesTab = new DeadlineWindow(calendario,this);
    tabWidgets->addTab(deadlinesTab, "Scadenze");
    connect(deadlinesTab, &DeadlineWindow::eventoEliminato, agendaTab, &Agenda::eventoEliminato);
    //Aggiunta del Menu
    Menu* menu = new Menu(calendario, this);
    addToolBar(Qt::TopToolBarArea, menu);
    connect(menu, &Menu::agendaLoaded, deadlinesTab, [calendario,deadlinesTab](){
        QVector<Evento*> impegni = calendario->getImpegni();
        for(int i=0; i<impegni.size(); ++i){
            if(dynamic_cast<Deadline*>(impegni[i])){ //voglio inserire nella lista solo le scadenze
                deadlinesTab->addDeadline(static_cast<Deadline*>(impegni.at(i)));
            }
        }
        deadlinesTab->viewRefresh();
    });
}

