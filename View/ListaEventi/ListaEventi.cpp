#include "ListaEventi.h"
#include "View/Visitors/RicercaVisitor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ListaEventi::ListaEventi(Calendario* cal,QWidget* parent):
    QWidget(parent), calendario(cal){
    QVBoxLayout* layout = new QVBoxLayout(this);
    searchBar = new QWidget(this);
    QHBoxLayout* searchLayout = new QHBoxLayout(searchBar);
    tagList = new QComboBox(searchBar);
    searchLayout->addWidget(tagList, 0);
    searchText = new QLineEdit(searchBar);
    searchText->setPlaceholderText("Cerca Evento...");
    searchText->setClearButtonEnabled(true);
    searchLayout->addWidget(searchText,1);
    searchBtn = new QPushButton(searchBar);
    searchBtn->setIcon(style()->standardIcon(QStyle::SP_FileDialogContentsView));
    searchLayout->addWidget(searchBtn,0);
    layout->addWidget(searchBar);
    listaEventi = new QListWidget(this);
    layout->addWidget(listaEventi,3);
    initConnections();
    tagsUpdate();
    refresh(calendario->getImpegni());
}

void ListaEventi::tagsUpdate(){
    tagList->clear();
    tags.clear();
    tagList->addItem("Tutti");
    tags = calendario->getTags();
    for(int i=0; i<tags.size(); ++i){
        tagList->addItem(tags.at(i));
    }
}

void ListaEventi::refresh(const QVector<Evento*>& evs){
    listaEventi->clear();
    RicercaVisitor RV(listaEventi, this);
    for(int i=0; i<evs.size(); i++){
        Evento* e = evs.at(i);
        if(e){
            e->acceptVisitor(RV);
        }
    }
}

QVector<Evento*>ListaEventi::filtraNome(QVector<Evento*>& in, const QString& nome) const{
    if(!nome.isEmpty()){
        for(int i=in.size()-1;i>=0; i--){ //dalla fine all'inizio per evitare che in.erase() salti un elemento quando incremento i;
            if(!((in.at(i))->getNome()).contains(nome)){
                in.erase(in.begin()+i);
            }
        }
    }
    return in;
}

QVector<Evento*> ListaEventi::filtraTag(QVector<Evento*>& in, const QString& tag) const {
    if(tag == "Tutti") return calendario->getImpegni();
    if(!tag.isEmpty()){
        for(int i=in.size()-1;i>=0; i--){ //dalla fine all'inizio per evitare che in.erase() salti un elemento quando incremento i;
            if(in.at(i)->getTag() != tag){
                in.erase(in.begin()+i);
            }
        }
    }
    return in;
}

void ListaEventi::initConnections(){
    connect(searchBtn, &QPushButton::clicked, this, [this](){
        QVector<Evento*> inizioRicerca = calendario->getImpegni();
        QVector<Evento*> filtratoTag = filtraTag(inizioRicerca, tagList->currentText());
        QVector<Evento*> risultato = filtraNome(filtratoTag, searchText->text());
        refresh(risultato);
    });
}
