#include "Menu.h"
#include "eventofactory.h"
#include "XmlParser.h"
#include <QToolButton>
#include <QMenu>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>
Menu::Menu(Calendario* cal, DeadlineWindow* scad, QWidget *parent) : QToolBar("Menu", parent),calendario(cal),scadenze(scad){
    this->setMovable(false);
    this->setFloatable(false);

    QAction* addNew = new QAction(QIcon(":/Icons/View/Icons/addnew.svg"),"&Nuovo",this);
    addNew->setShortcut(Qt::Key_N|Qt::CTRL);
    this->addAction(addNew);

    QToolButton* save = new QToolButton;
    save->setText("&Salva");
    save->setIcon(QIcon(":/Icons/View/Icons/download.svg"));
    QMenu* esportazione = new QMenu("Salva", this);
    save->setShortcut(Qt::Key_S | Qt::CTRL);
    QAction* saveJSON = new QAction("Salva in JSON", esportazione);
    QAction* saveXML = new QAction("Salva in XML", esportazione);
    esportazione->addAction(saveJSON);
    esportazione->addAction(saveXML);
    save->setMenu(esportazione);
    save->setPopupMode(QToolButton::InstantPopup);
    save->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->addWidget(save);

    QAction* import = new QAction(QIcon(":/Icons/View/Icons/upload.svg"),"Importa", this);
    import->setText("&Importa");
    import->setShortcut(Qt::Key_I | Qt::CTRL);
    this->addAction(import);

    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    connect(addNew, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "CREAZIONE EVENTO", "NUOVO EVENTO CLICCATO");
        /*Evento* a = new Attivita("pipo","pupo","papo",QDate::currentDate(),QTime::currentTime(),QTime::fromMSecsSinceStartOfDay(300));
        Evento* b = new Deadline("culo","anus","patongs",QDate::currentDate(),true);
        calendario->addEvento(a);
        calendario->addEvento(b); TEST*/
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
        QString percorso = QFileDialog::getSaveFileName(this,"ESPORTAZIONE AGENDA", QDir::homePath()+"/agendaExport.xml");
        if (percorso.isEmpty()){
            QMessageBox::information(this, "ESPORTAZIONE", "L'OPERAZIONE DI ESPORTAZIONE E' STATA ANNULLATA");
            return;
        }
        if(XmlParser::saveToXml(percorso,*calendario)){
            QMessageBox::information(this, "ESPORTAZIONE", "ESPORTAZIONE IN FORMATO XML NEL FILE:\n" + percorso);
        }
        else {
            QMessageBox::critical(this, "ESPORTAZIONE", "ERRORE NELL'ESPORTAZIONE IN FORMATO XML");
        }
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
        if(eventiInput.isNull()){
            QMessageBox::critical(this, "IMPORTAZIONE", "ERRORE NELL'APERTURA DEL FILE:\n" + percorso);
            return;
        }
        QJsonArray eventi = eventiInput.array();
        EventoFactory evFactory;
        scadenze->clearDeadlines();
        calendario->clear();
        for(int i=0; i<eventi.size(); ++i){
            QJsonObject ev = (eventi.at(i)).toObject();
            evFactory.BuildEvento(calendario, ev);
        }
        QMessageBox::information(this, "IMPORTAZIONE", "IMPORTAZIONE AGENDA TERMINATA");
        emit agendaLoaded();
    });
}
