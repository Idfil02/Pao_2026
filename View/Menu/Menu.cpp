#include "Menu.h"
#include "eventofactory.h"
#include <QToolButton>
#include <QMenu>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>
Menu::Menu(Calendario* cal, QWidget *parent) : QToolBar("Menu", parent),calendario(cal){
    this->setMovable(false);
    this->setFloatable(false);

    QAction* addNew = new QAction(QIcon(":/Icons/View/Icons/addnew.svg"),"Nuovo", this);
    this->addAction(addNew);

    QToolButton* save = new QToolButton;
    save->setText("Salva");
    save->setIcon(QIcon(":/Icons/View/Icons/download.svg"));
    QMenu* esportazione = new QMenu("Salva", this);
    QAction* saveJSON = new QAction("Salva in JSON", esportazione);
    QAction* saveXML = new QAction("Salva in XML", esportazione);
    esportazione->addAction(saveJSON);
    esportazione->addAction(saveXML);
    save->setMenu(esportazione);
    save->setPopupMode(QToolButton::InstantPopup);
    save->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->addWidget(save);

    QAction* import = new QAction(QIcon(":/Icons/View/Icons/upload.svg"),"Importa", this);
    this->addAction(import);

    QAction* preferenze = new QAction(QIcon(":/Icons/View/Icons/settings.svg"),"Preferenze", this);
    this->addAction(preferenze);


    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    connect(addNew, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "CREAZIONE EVENTO", "NUOVO EVENTO CLICCATO");
    });
    connect(saveJSON, &QAction::triggered, this, [this](){
        QString percorso = QFileDialog::getSaveFileName(this,"ESPORTAZIONE AGENDA", QDir::homePath()+"/agendaExport.json");
        if(percorso.isEmpty()){
            QMessageBox::information(this, "ESPORTAZIONE", "L'OPERAZIONE DI ESPORTAZIONE E' STATA ANNULLATA");
            return;
        }
        QFile output(percorso);
        QVector<Evento*> eventi = calendario->getImpegni();
        QJsonArray eventiOutput;
        if(!output.open(QFile::WriteOnly)){
            QMessageBox::critical(this, "ESPORTAZIONE", "ERRORE NELL'ESPORTAZIONE IN FORMATO JSON");
            return;
        }
        for(int i=0; i<eventi.size(); ++i){
            Evento* ev = eventi.at(i);
            eventiOutput.append(ev->toJson());
        }
        QJsonDocument eventiJson(eventiOutput);
        output.write(eventiJson.toJson());
        output.close();
        QMessageBox::information(this, "ESPORTAZIONE", "ESPORTAZIONE IN FORMATO JSON NEL FILE:\n" + percorso);
    });
    connect(saveXML, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "ESPORTAZIONE", "ESPORTAZIONE IN FORMATO XML");
    });
    connect(import, &QAction::triggered, this, [this](){
        QString percorso = QFileDialog::getOpenFileName(this, "IMPORTAZIONE FILE", QDir::homePath());
        if(percorso.isEmpty()){
            QMessageBox::information(this, "IMPORTAZIONE", "L'OPERAZIONE DI IMPORTAZIONE E' STATA ANNULLATA");
            return;
        }
        QFile input(percorso);
        if(!input.open(QFile::ReadOnly)){
            QMessageBox::critical(this, "IMPORTAZIONE", "ERRORE NELL'APERTURA DEL FILE:\n" + percorso);
            return;
        }
        QJsonDocument eventiInput = QJsonDocument::fromJson(input.readAll());
        QJsonArray eventi = eventiInput.array();
        EventoFactory evFactory;
        calendario->clear();
        for(int i=0; i<eventi.size(); ++i){
            QJsonObject ev = (eventi.at(i)).toObject();
            evFactory.BuildEvento(calendario, ev);
        }
        QMessageBox::information(this, "IMPORTAZIONE", "IMPORTAZIONE AGENDA TERMINATA");
        emit agendaLoaded();
    });
    connect(preferenze, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "ESPORTAZIONE", "SCELTA IMPOSTAZIONI");
    });
}
