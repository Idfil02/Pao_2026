#include "InfoVisitor.h"
#include <QLabel>
#include <QTextEdit>

InfoVisitor::InfoVisitor(QFormLayout* details):dettagliEvento(details){}

void InfoVisitor::visit(Deadline& scadenza){
    //recupero informazioni evento
    QLabel* tag = new QLabel(scadenza.getTag());
    if(tag->text().isEmpty()){
        tag->setText("Nessun tag specificato");
    }
    QTextEdit* desc = new QTextEdit(scadenza.getDesc());
    desc->setPlaceholderText("Nessuna descrizione");
    desc->setReadOnly(true);
    //aggiungo tutto ai dettagli dell'evento
    dettagliEvento->addRow(tag);
    dettagliEvento->addRow(desc);
}

void InfoVisitor::visit(Attivita& att){
    //recupero informazioni evento
    QLabel* tag = new QLabel(att.getTag());
    if(tag->text().isEmpty()){
        tag->setText("Nessun tag specificato");
    }
    QTextEdit* desc = new QTextEdit(att.getDesc());
    desc->setPlaceholderText("Nessuna descrizione");
    desc->setReadOnly(true);
    //aggiungo tutto ai dettagli dell'evento
    dettagliEvento->addRow(tag);
    dettagliEvento->addRow(desc);
}

void InfoVisitor::visit(Riunione& riunione){
    //recupero informazioni evento
    QLabel* tag = new QLabel(riunione.getTag());
    if(tag->text().isEmpty()){
        tag->setText("Nessun tag specificato");
    }
    QTextEdit* desc = new QTextEdit(riunione.getDesc());
    desc->setPlaceholderText("Nessuna descrizione");
    desc->setReadOnly(true);
    QLabel* link = new QLabel(riunione.getLink());
    if(link->text().isEmpty()){
        link->setText("Nessun link specificato");
    }
    QTextEdit* partecipanti = new QTextEdit;
    QVector<QString> membri = riunione.getPartecipanti();
    QString contenuto = membri[0];
    for(int i=1; i<membri.size(); ++i){
        contenuto += "," + membri[i];
    }
    partecipanti->setPlainText(contenuto);
    partecipanti->setPlaceholderText("Nessun partecipante");
    partecipanti->setReadOnly(true);
    //aggiungo tutto ai dettagli dell'evento
    dettagliEvento->addRow(tag);
    dettagliEvento->addRow(link);
    dettagliEvento->addRow(partecipanti);
    dettagliEvento->addRow(desc);
}

void InfoVisitor::visit(Appuntamento& app){
    //recupero informazioni evento
    QLabel* tag = new QLabel(app.getTag());
    if(tag->text().isEmpty()){
        tag->setText("Nessun tag specificato");
    }
    QTextEdit* desc = new QTextEdit(app.getDesc());
    desc->setPlaceholderText("Nessuna descrizione");
    desc->setReadOnly(true);
    QLabel* luogo = new QLabel(app.getLuogo());
    if(luogo->text().isEmpty()){
        luogo->setText("Nessun luogo specificato");
    }
    QLabel* contatto = new QLabel(app.getContatto());
    if(contatto->text().isEmpty()){
        contatto->setText("Nessun contatto specificato");
    }
    //aggiungo tutto ai dettagli dell'evento
    dettagliEvento->addRow(tag);
    dettagliEvento->addRow(luogo);
    dettagliEvento->addRow(contatto);
    dettagliEvento->addRow(desc);
}
