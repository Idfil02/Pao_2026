#include "Menu.h"
#include <QToolButton>
#include <QMenu>
#include <QMessageBox>
Menu::Menu(QWidget *parent) : QToolBar("Menu", parent){
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
    this->addWidget(save);

    QAction* import = new QAction(QIcon(":/Icons/View/Icons/upload.svg"),"Importa", this);
    this->addAction(import);

    QAction* preferenze = new QAction(QIcon(":/Icons/View/Icons/settings.svg"),"Preferenze", this);
    this->addAction(preferenze);

    save->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    connect(addNew, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "CREAZIONE EVENTO", "NUOVO EVENTO CLICCATO");
    });
    connect(saveJSON, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "ESPORTAZIONE", "ESPORTAZIONE IN FORMATO JSON");
    });
    connect(saveXML, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "ESPORTAZIONE", "ESPORTAZIONE IN FORMATO XML");
    });
    connect(import, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "IMPORTAZIONE", "IMPORTAZIONE AGENDA");
    });
    connect(preferenze, &QAction::triggered, this, [this](){
        QMessageBox::information(this, "ESPORTAZIONE", "SCELTA IMPOSTAZIONI");
    });
}
