#include "InfoVisitor.h"
#include <QLabel>
#include <QTextEdit>
InfoVisitor::InfoVisitor(QFormLayout* details):dettagliEvento(details){}

void InfoVisitor::visit(Deadline& scadenza){
    QLabel* tag = new QLabel(scadenza.getTag()); //tag
    QTextEdit* desc = new QTextEdit(scadenza.getDesc()); //descrizione
    //aggiungo tutto ai dettagli dell'evento
    dettagliEvento->addRow(tag);
    dettagliEvento->addRow(desc);
}
void InfoVisitor::visit(Attivita& att){
    QLabel* tag = new QLabel(att.getTag()); //tag
    QTextEdit* desc = new QTextEdit(att.getDesc());//descrizione
    //aggiungo tutto ai dettagli dell'evento
    dettagliEvento->addRow(tag);
    dettagliEvento->addRow(desc);
}
void InfoVisitor::visit(Riunione& riunione){
    QLabel* tag = new QLabel(riunione.getTag()); //tag
    QTextEdit* desc = new QTextEdit(riunione.getDesc());//descrizione
    QLabel* link = new QLabel(riunione.getLink());//link riunione
    QTextEdit* partecipanti = new QTextEdit; //elenco dei partecipanti

    QVector<QString> membri = riunione.getPartecipanti();
    QString contenuto = membri[0];
    for(int i=1; i<membri.size(); ++i){
        contenuto += "," + membri[i];
    }
    partecipanti->setPlainText(contenuto);

    //aggiungo tutto ai dettagli dell'evento
    dettagliEvento->addRow(tag);
    dettagliEvento->addRow(link);
    dettagliEvento->addRow(partecipanti);
    dettagliEvento->addRow(desc);
}
void InfoVisitor::visit(Appuntamento& app){
    QLabel* tag = new QLabel(app.getTag());//tag
    QTextEdit* desc = new QTextEdit(app.getDesc());//descrizione
    QLabel* luogo = new QLabel(app.getLuogo());//luogo appuntamento
    QLabel* contatto = new QLabel(app.getContatto());//contatto appuntamento

    //aggiungo tutto ai dettagli dell'evento
    dettagliEvento->addRow(tag);
    dettagliEvento->addRow(luogo);
    dettagliEvento->addRow(contatto);
    dettagliEvento->addRow(desc);
}
