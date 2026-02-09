#include "mainwindow.h"
#include "View/Visitors/Editvisitor.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
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
    // aggiunta tab lista eventi
    eventsTab = new ListaEventi(cal, this);
    tabWidgets->addTab(eventsTab, "Cerca Evento");
    //Aggiunta del Menu
    menu = new Menu(cal, deadlinesTab, this);
    addToolBar(Qt::TopToolBarArea, menu);
    this->setContextMenuPolicy(Qt::PreventContextMenu);
    initConnections();
}


void MainWindow::richiestaCreate(Evento* ev){
    QWidget* editPage = new QWidget(tabWidgets);
    tabWidgets->addTab(editPage, "Aggiungi Evento");
    tabWidgets->setCurrentWidget(editPage);
    QFormLayout* layout = new QFormLayout(editPage);
    EditVisitor* EDITOR = new EditVisitor(layout, editPage);
    ev->acceptVisitor(*EDITOR);
    connect(EDITOR, &EditVisitor::eventoModificato, this, [this, ev](){
        this->cal->addEvento(ev);
        this->eventoModificato(ev->getData(),ev->getData());
        auto t = dynamic_cast<Deadline*>(ev);
        if(t){
            this->deadlinesTab->addDeadline(t);
        }
    });
    connect(EDITOR, &EditVisitor::eventoAnnullato, this, [this](){
        tabWidgets->removeTab(tabWidgets->currentIndex());
    });
}


void MainWindow::richiestaEdit(Evento* ev){
    QWidget* editPage = new QWidget(tabWidgets);
    tabWidgets->addTab(editPage, "Modifica Evento");
    tabWidgets->setCurrentWidget(editPage);
    QFormLayout* layout = new QFormLayout(editPage);
    EditVisitor* EDITOR = new EditVisitor(layout, editPage);
    ev->acceptVisitor(*EDITOR);
    connect(EDITOR, &EditVisitor::eventoModificato, this, &MainWindow::eventoModificato);
    connect(EDITOR, &EditVisitor::eventoAnnullato, this, [this](){
        tabWidgets->removeTab(tabWidgets->currentIndex());
    });
}


void MainWindow::eventoModificato(const QDate& dataPrec, const QDate& newData){
    tabWidgets->removeTab(tabWidgets->currentIndex());
    deadlinesTab->viewRefresh();
    agendaTab->giornoSelezionato(dataPrec);
    agendaTab->giornoSelezionato(newData);
    eventsTab->tagsUpdate();
    eventsTab->refresh(cal->getImpegni());
}


void MainWindow::eventoEliminato(Evento* ev, const QDate& data){
    Deadline* scad = dynamic_cast<Deadline*>(ev);
    if(scad){ //se è una scadenza la devo togliere anche dal vettore di scadenze
        deadlinesTab->deleteDeadline(scad);
        deadlinesTab->viewRefresh();
    }
    cal->removeEvento(ev);
    agendaTab->giornoSelezionato(data);
    eventsTab->tagsUpdate();
    eventsTab->refresh(cal->getImpegni());
}


void MainWindow::initConnections(){
    connect(agendaTab, &Agenda::eventoEliminato, this, &MainWindow::eventoEliminato);
    connect(agendaTab, &Agenda::richiestaEdit, this, &MainWindow::richiestaEdit);

    connect(deadlinesTab, &DeadlineWindow::eventoEliminato, this, &MainWindow::eventoEliminato);
    connect(deadlinesTab, &DeadlineWindow::deadlineModificata, agendaTab, &Agenda::giornoSelezionato);
    connect(deadlinesTab, &DeadlineWindow::richiestaEdit, this, &MainWindow::richiestaEdit);

    connect(eventsTab, &ListaEventi::eventoEliminato, this, &MainWindow::eventoEliminato);
    connect(eventsTab, &ListaEventi::richiestaEdit, this, &MainWindow::richiestaEdit);
    connect(eventsTab, &ListaEventi::goTo, this, [this](Evento* ev){
        tabWidgets->setCurrentWidget(agendaTab);
        agendaTab->giornoSelezionato(ev->getData());
    });
    connect(menu, &Menu::agendaLoaded, this, [this](){
        deadlinesTab->clearDeadlines();
        QVector<Evento*> impegni = cal->getImpegni();
        for(int i=0; i<impegni.size(); ++i){
            auto ev = dynamic_cast<Deadline*>(impegni.at(i));
            if(ev){ //voglio inserire nella lista solo le scadenze
                deadlinesTab->addDeadline(ev);
            }
        }
        deadlinesTab->viewRefresh();
        eventsTab->tagsUpdate();
        eventsTab->refresh(cal->getImpegni());
    });
    connect(menu, &Menu::createNew, this, &MainWindow::richiestaCreate);
}
