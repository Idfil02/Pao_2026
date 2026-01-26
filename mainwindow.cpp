#include "mainwindow.h"
#include "View/Agenda/Agenda.h"
#include "View/DeadlineWindow/DeadlineWindow.h"
#include "View/Menu/Menu.h"
#include "View/editvisitor.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Set window properties
    setWindowTitle("Agenda - PAO 2026");
    // Create main tab widget
    tabWidgets = new QTabWidget(this);
    setCentralWidget(tabWidgets);
    cal = new Calendario(this);
    // Create and add Agenda tab
    agendaTab = new Agenda(cal,this);
    tabWidgets->addTab(agendaTab, "Agenda");
    // Create and add Deadlines tab
    deadlinesTab = new DeadlineWindow(cal,this);
    tabWidgets->addTab(deadlinesTab, "Scadenze");
    connect(deadlinesTab, &DeadlineWindow::eventoEliminato, agendaTab, &Agenda::eventoEliminato);
    //Aggiunta del Menu
    Menu* menu = new Menu(cal, deadlinesTab, this);
    addToolBar(Qt::TopToolBarArea, menu);
    this->setContextMenuPolicy(Qt::PreventContextMenu);
    connect(menu, &Menu::agendaLoaded, deadlinesTab, [this](){
        QVector<Evento*> impegni = cal->getImpegni();
        for(int i=0; i<impegni.size(); ++i){
            auto ev = dynamic_cast<Deadline*>(impegni.at(i));
            if(ev){ //voglio inserire nella lista solo le scadenze
                deadlinesTab->addDeadline(ev);
            }
        }
        deadlinesTab->viewRefresh();
    });
    connect(deadlinesTab, &DeadlineWindow::richiestaEdit, this, &MainWindow::richiestaEdit);
    connect(agendaTab, &Agenda::richiestaEdit, this, &MainWindow::richiestaEdit);
}

void MainWindow::richiestaEdit(Evento* ev){
    QWidget* editPage = new QWidget(tabWidgets);
    tabWidgets->addTab(editPage, "Modifica Evento");
    tabWidgets->setCurrentWidget(editPage);
    QFormLayout* layout = new QFormLayout(editPage);
    EditVisitor* EDITOR = new EditVisitor(layout, editPage);
    ev->acceptVisitor(*EDITOR);
    connect(EDITOR, &EditVisitor::eventoModificato, this, &MainWindow::eventoModificato);
}
void MainWindow::eventoModificato(const QDate& dataPrec, const QDate& newData){
    tabWidgets->removeTab(tabWidgets->currentIndex());
    deadlinesTab->viewRefresh();
    agendaTab->giornoSelezionato(dataPrec);
    agendaTab->giornoSelezionato(newData);
}
