#include "mainwindow.h"
#include "View/Visitors/EditVisitor.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    setWindowTitle("Agenda - PAO 2026");
    cal = new Calendario(this);
    // Creazione tabs
    tabWidgets = new QTabWidget(this);
    setCentralWidget(tabWidgets);
    agendaTab = new Agenda(cal,this);
    tabWidgets->addTab(agendaTab, "&1) Agenda");
    deadlinesTab = new DeadlineWindow(cal,this);
    tabWidgets->addTab(deadlinesTab, "&2) Scadenze");
    eventsTab = new ListaEventi(cal, this);
    tabWidgets->addTab(eventsTab, "&3) Cerca Evento");
    //Aggiunta del Menu
    menu = new Menu(cal, agendaTab, deadlinesTab, this);
    addToolBar(Qt::TopToolBarArea, menu);
    this->setContextMenuPolicy(Qt::PreventContextMenu);
    //connessione dei segnali
    initConnections();
}

void MainWindow::richiestaCreate(Evento* ev){
    QWidget* editPage = new QWidget(tabWidgets);
    QString tabName = "&"+(QString::number(tabWidgets->count()+1)+") Aggiungi Evento");
    tabWidgets->addTab(editPage,tabName);
    tabWidgets->setCurrentWidget(editPage);
    QFormLayout* layout = new QFormLayout(editPage);
    EditVisitor* editor = new EditVisitor(layout, editPage);
    ev->acceptVisitor(*editor);
    connect(editor, &EditVisitor::eventoModificato, this, [this, ev](){
        if(ev){
            //aggiunta evento al calendario e refresh visualizzazione
            this->cal->addEvento(ev);
            //se deadline viene aggiunta nella tab deadlines
            auto t = dynamic_cast<Deadline*>(ev);
            if(t){
                this->deadlinesTab->addDeadline(t);
            }
            this->modificaEvento(ev->getData(),ev->getData());
        }
        else{
            QMessageBox::critical(this, "ERRORE","Non è stato possibile creare l'evento");
        }
    });
    connect(editor, &EditVisitor::eventoAnnullato, this, [this](){
        //chiusura finestra di creazione evento
        tabWidgets->removeTab(tabWidgets->currentIndex());
    });
}

void MainWindow::richiestaEdit(Evento* ev){
    QWidget* editPage = new QWidget(tabWidgets);
    QString tabName = "&"+(QString::number(tabWidgets->count()+1)+") Modfica Evento");
    tabWidgets->addTab(editPage, tabName);
    tabWidgets->setCurrentWidget(editPage);
    QFormLayout* layout = new QFormLayout(editPage);
    EditVisitor* editor = new EditVisitor(layout, editPage);
    ev->acceptVisitor(*editor);
    connect(editor, &EditVisitor::eventoModificato, this, &MainWindow::modificaEvento);
    connect(editor, &EditVisitor::eventoAnnullato, this, [this](){
        //chiusura finestra di creazione evento
        tabWidgets->removeTab(tabWidgets->currentIndex());
    });
}

void MainWindow::modificaEvento(const QDate& dataPrec, const QDate& newData){
    //chiusura finestra di creazione-edit
    tabWidgets->removeTab(tabWidgets->currentIndex());
    //aggiornamento visualizzazione eventi
    deadlinesTab->viewRefresh();
    agendaTab->giornoSelezionato(dataPrec);
    agendaTab->giornoSelezionato(newData);
    cal->refreshTags();
    eventsTab->tagsUpdate();
    eventsTab->refresh(cal->getImpegni());
}

void MainWindow::eliminaEvento(Evento* ev, const QDate& data){
    Deadline* scad = dynamic_cast<Deadline*>(ev);
    if(scad){ //se è una scadenza la devo togliere anche dal vettore di scadenze
        deadlinesTab->deleteDeadline(scad);
        deadlinesTab->viewRefresh();
    }
    //rimozione evento dal calendario e refresh visualizzazione
    cal->removeEvento(ev);
    agendaTab->giornoSelezionato(data);
    eventsTab->tagsUpdate();
    eventsTab->refresh(cal->getImpegni());
}

void MainWindow::initConnections(){
    //connessione segnali tab agenda
    connect(agendaTab, &Agenda::eventoEliminato, this, &MainWindow::eliminaEvento);
    connect(agendaTab, &Agenda::richiestaEdit, this, &MainWindow::richiestaEdit);
    connect(agendaTab, &Agenda::richiestaCreate, this, &MainWindow::richiestaCreate);
    //connessione segnali tab deadlines
    connect(deadlinesTab, &DeadlineWindow::eventoEliminato, this, &MainWindow::eliminaEvento);
    connect(deadlinesTab, &DeadlineWindow::richiestaEdit, this, &MainWindow::richiestaEdit);
    connect(deadlinesTab, &DeadlineWindow::deadlineModificata, agendaTab, &Agenda::giornoSelezionato);
    //connessione segnali tab lista eventi
    connect(eventsTab, &ListaEventi::eventoEliminato, this, &MainWindow::eliminaEvento);
    connect(eventsTab, &ListaEventi::richiestaEdit, this, &MainWindow::richiestaEdit);
    connect(eventsTab, &ListaEventi::goTo, this, [this](Evento* ev){
        //focus sull evento nell'agenda
        tabWidgets->setCurrentWidget(agendaTab);
        agendaTab->giornoSelezionato(ev->getData());
    });
    //connesione segnali menu
    connect(menu, &Menu::agendaLoaded, this, [this](){
        //refresh tab secondarie dopo il caricamento del calendario
        deadlinesTab->clearDeadlines();
        QVector<Evento*> impegni = cal->getImpegni();
        int i = 0;
        for(; i<impegni.size(); ++i){
            auto ev = dynamic_cast<Deadline*>(impegni.at(i));
            if(ev){ //voglio inserire nella lista solo le scadenze
                deadlinesTab->addDeadline(ev);
            }
        }
        deadlinesTab->viewRefresh();
        eventsTab->tagsUpdate();
        eventsTab->refresh(cal->getImpegni());
        while(tabWidgets->count()>3){
            tabWidgets->removeTab(3);
        }
        agendaTab->giornoSelezionato(i == 0 ? QDate::currentDate() : impegni.at(i-1)->getData());
    });
    connect(menu, &Menu::createNew, this, &MainWindow::richiestaCreate);
}
