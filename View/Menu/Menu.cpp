#include "Menu.h"
#include "Model/Riunione.h"
#include "Model/Appuntamento.h"
#include "EventoFactory.h"
#include "XmlParser.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>
Menu::Menu(Calendario* cal, DeadlineWindow* scad, QWidget *parent) : QToolBar("Menu", parent),calendario(cal),scadenze(scad){
    this->setMovable(false);
    this->setFloatable(false);

    addNew = new QToolButton;
    addNew->setText("&Nuovo");
    addNew->setIcon(QIcon(":/Icons/View/Icons/addnew.svg"));
    addNew->setShortcut(Qt::Key_N|Qt::CTRL);
    addMenu = new QMenu("Nuovo", this);
    addAppuntamento = new QAction("Appuntamento",addMenu);
    addAttivita = new QAction("Attivita",addMenu);
    addDeadline = new QAction("Deadline",addMenu);
    addRiunione = new QAction("Riunione",addMenu);
    addMenu->addAction(addAppuntamento);
    addMenu->addAction(addAttivita);
    addMenu->addAction(addDeadline);
    addMenu->addAction(addRiunione);
    addNew->setMenu(addMenu);
    addNew->setPopupMode(QToolButton::InstantPopup);
    addNew->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->addWidget(addNew);

    save = new QToolButton;
    save->setText("&Salva");
    save->setIcon(QIcon(":/Icons/View/Icons/download.svg"));
    save->setShortcut(Qt::Key_S | Qt::CTRL);
    menuEsportazione = new QMenu("Salva", this);
    saveJSON = new QAction("Salva in JSON", menuEsportazione);
    saveXML = new QAction("Salva in XML", menuEsportazione);
    menuEsportazione->addAction(saveJSON);
    menuEsportazione->addAction(saveXML);
    save->setMenu(menuEsportazione);
    save->setPopupMode(QToolButton::InstantPopup);
    save->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->addWidget(save);

    import = new QAction(QIcon(":/Icons/View/Icons/upload.svg"),"Importa", this);
    import->setText("&Importa");
    import->setShortcut(Qt::Key_I | Qt::CTRL);
    this->addAction(import);
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    initConnections();

}

void Menu:: initConnections(){

    connect(addAppuntamento, &QAction::triggered, this, [this](){
        Appuntamento* appuntamento = new Appuntamento();
        emit createNew(appuntamento);
    });


    connect(addAttivita, &QAction::triggered, this, [this](){
        Attivita* attivita = new Attivita();
        emit createNew(attivita);
    });


    connect(addDeadline, &QAction::triggered, this, [this](){
        Deadline* deadline = new Deadline();
        emit createNew(deadline);
    });


    connect(addRiunione, &QAction::triggered, this, [this](){
        Riunione* riunione = new Riunione();
        emit createNew(riunione);
    });


    connect(saveJSON, &QAction::triggered, this, [this](){
        QString percorso = QFileDialog::getSaveFileName(this,"ESPORTAZIONE AGENDA", QDir::homePath()+"/agendaExport.json");
        if(percorso.isEmpty()){
            QMessageBox::information(this, "ESPORTAZIONE", "L'operazione di esportazione è stata annullata");
            return;
        }

        QFile output(percorso);
        QVector<Evento*> eventi = calendario->getImpegni();
        QJsonArray eventiOutput;
        if(!output.open(QFile::WriteOnly)){
            QMessageBox::critical(this, "ESPORTAZIONE JSON", "Errore nell'esportazione in formato JSON");
            return;
        }

        for(int i=0; i<eventi.size(); ++i){
            Evento* ev = eventi.at(i);
            eventiOutput.append(ev->toJson());
        }

        QJsonDocument eventiJson(eventiOutput);
        output.write(eventiJson.toJson());
        output.close();
        QMessageBox::information(this, "ESPORTAZIONE JSON", "Esportazione in formato JSON nel file:\n" + percorso);
    });


    connect(saveXML, &QAction::triggered, this, [this](){
        QString percorso = QFileDialog::getSaveFileName(this,"ESPORTAZIONE AGENDA", QDir::homePath()+"/agendaExport.xml");
        if (percorso.isEmpty()){
            QMessageBox::information(this, "ESPORTAZIONE", "L'operazione di esportazione è stata annullata");
            return;
        }

        if(XmlParser::saveToXml(percorso,*calendario)){
            QMessageBox::information(this, "ESPORTAZIONE", "Esportazione in formato XML nel file:\n" + percorso);
        }

        else {
            QMessageBox::critical(this, "ESPORTAZIONE", "Errore durante l'esportazione del file in formato XML");
        }     
    });


    connect(import, &QAction::triggered, this, [this](){
        QString percorso = QFileDialog::getOpenFileName(this, "IMPORTAZIONE FILE", QDir::homePath());
        if(percorso.isEmpty()){
            QMessageBox::information(this, "IMPORTAZIONE", "L'operazione di importazione è stata annullata");
            return;
        }

        QFile input(percorso);
        if(!input.open(QFile::ReadOnly)){
            QMessageBox::critical(this, "IMPORTAZIONE", "Errore nell'apertura del file:\n" + percorso);
            return;
        }

        if(percorso.endsWith(".json",Qt::CaseInsensitive)){
        QJsonDocument eventiInput = QJsonDocument::fromJson(input.readAll());
        if(eventiInput.isNull()){
            QMessageBox::critical(this, "IMPORTAZIONE", "Formato del file\n" + percorso+"\n Non supportato");
            return;
        }

        QJsonArray eventi = eventiInput.array();
        EventoFactory evFactory;
        calendario->clear();
        for(int i=0; i<eventi.size(); ++i){
            QJsonObject ev = (eventi.at(i)).toObject();
            evFactory.BuildEvento(calendario, ev);
        }  
        }

        if(percorso.endsWith(".xml",Qt::CaseInsensitive)){
            input.close();
            calendario->clear();
            bool success = XmlParser::loadFromXml(percorso,*calendario);
            if (!success)
                QMessageBox::critical(this, "IMPORTAZIONE", "Errore nell'importazione del file XML:\n" + percorso);
        }

        QMessageBox::information(this, "IMPORTAZIONE", "Importazione da\n" + percorso + "\nTerminata");
        emit agendaLoaded();
    });
}
