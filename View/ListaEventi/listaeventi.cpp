#include "listaeventi.h"
#include <QVBoxLayout>
ListaEventi::ListaEventi(Calendario* cal,QWidget* parent):
    QWidget(parent), calendario(cal){
    QVBoxLayout* layout = new QVBoxLayout(this);

    listaEventi = new QListWidget;
    layout->addWidget(listaEventi);

    infoEvento = new QWidget(this);
    infoEventoLayout = new QFormLayout;
    layout->addWidget(infoEvento);

    tags = calendario->getTags();
    refresh();
}

void ListaEventi::tagsUpdate(){
    tags.clear();
    tags = calendario->getTags();
}
void ListaEventi::clearInfo(){
    while(infoEventoLayout->count()){
        infoEventoLayout->removeRow(0);
    }
}
void ListaEventi::refresh(){
    clearInfo();
    listaEventi->clear();
    QVector<Evento*> eventi = calendario->getImpegni();
}

