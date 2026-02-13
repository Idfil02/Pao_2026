#include "EditVisitor.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QMessageBox>

EditVisitor::EditVisitor(QFormLayout* page, QWidget* parent): QObject(parent),editPage(page){}

void EditVisitor::visit(Deadline& scadenza){
    QDate dataPrec = scadenza.getData();
    QLineEdit* nome = new QLineEdit(scadenza.getNome());
    QLineEdit* tag = new QLineEdit(scadenza.getTag());
    QTextEdit* desc = new QTextEdit(scadenza.getDesc());
    QDateEdit* data = new QDateEdit(dataPrec);
    editPage->addRow("Nome:", nome);
    editPage->addRow("Tag:", tag);
    editPage->addRow("Descrizione:", desc);
    editPage->addRow("Data:", data);
    //aggiunta bottoni
    QDialogButtonBox* bottoni = new QDialogButtonBox();
    bottoni->addButton(QDialogButtonBox::Cancel);
    bottoni->addButton(QDialogButtonBox::Ok);
    bottoni->button(QDialogButtonBox::Cancel)->setText("Annulla");
    bottoni->button(QDialogButtonBox::Ok)->setText("Salva");
    editPage->addRow(bottoni);
    QObject::connect(bottoni->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &EditVisitor::eventoAnnullato);
    QObject::connect(bottoni->button(QDialogButtonBox::Ok), &QPushButton::clicked,[=, &scadenza](){
        //validazione del form e applicazione modifiche
        if(nome->text().trimmed().isEmpty())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo nome non può essere vuoto");
        else if(tag->text().trimmed().isEmpty())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo tag non può essere vuoto");
        else if(!data->date().isValid())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo data non è valido");
        else{
            scadenza.setNome(nome->text());
            scadenza.setTag(tag->text());
            scadenza.setDesc(desc->toPlainText());
            QDate newData(data->date());
            scadenza.setData(newData);
            emit eventoModificato(dataPrec, newData);
        }
    });
}

void EditVisitor::visit(Attivita& att){
    QDate dataPrec = att.getData();
    QLineEdit* nome = new QLineEdit(att.getNome());
    QLineEdit* tag = new QLineEdit(att.getTag());
    QTextEdit* desc = new QTextEdit(att.getDesc());
    QDateEdit* data = new QDateEdit(dataPrec);
    QTimeEdit* oraInizio = new QTimeEdit(att.getOraInizio());
    QTimeEdit* oraFine = new QTimeEdit(att.getOraFine());
    editPage->addRow("Nome:", nome);
    editPage->addRow("Tag:", tag);
    editPage->addRow("Descrizione:", desc);
    editPage->addRow("Data:", data);
    editPage->addRow("Ora Inizio:", oraInizio);
    editPage->addRow("Ora Fine:", oraFine);
    //aggiunta bottoni
    QDialogButtonBox* bottoni = new QDialogButtonBox();
    bottoni->addButton(QDialogButtonBox::Cancel);
    bottoni->addButton(QDialogButtonBox::Ok);
    bottoni->button(QDialogButtonBox::Cancel)->setText("Annulla");
    bottoni->button(QDialogButtonBox::Ok)->setText("Salva");
    editPage->addRow(bottoni);
    QObject::connect(bottoni->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &EditVisitor::eventoAnnullato);
    QObject::connect(bottoni->button(QDialogButtonBox::Ok), &QPushButton::clicked,[=, &att](){
        //validazione del form e applicazione modifiche
        if(nome->text().trimmed().isEmpty())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo nome non può essere vuoto");
        else if(tag->text().trimmed().isEmpty())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo tag non può essere vuoto");
        else if(!data->date().isValid())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo data non è valido");
        else if(!oraInizio->time().isValid())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo ora inizio non è valido");
        else if(!oraFine->time().isValid())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo ora fine non è valido");
        else{
            att.setNome(nome->text());
            att.setTag(tag->text());
            att.setDesc(desc->toPlainText());
            QDate newData(data->date());
            att.setData(newData);
            att.setOraInizio(oraInizio->time());
            att.setOraFine(oraFine->time());
            emit eventoModificato(dataPrec, newData);
        }
    });
}

void EditVisitor::visit(Riunione& riun){
    QDate dataPrec = riun.getData();
    QLineEdit* nome = new QLineEdit(riun.getNome());
    QLineEdit* tag = new QLineEdit(riun.getTag());
    QTextEdit* desc = new QTextEdit(riun.getDesc());
    QDateEdit* data = new QDateEdit(dataPrec);
    QTimeEdit* oraInizio = new QTimeEdit(riun.getOraInizio());
    QTimeEdit* oraFine = new QTimeEdit(riun.getOraFine());
    QLineEdit* link = new QLineEdit(riun.getLink());
    QTextEdit* partecipanti = new QTextEdit((riun.getPartecipanti()).toList().join(','));
    partecipanti->setPlaceholderText("inserire i partecipanti separati da una virgola");
    editPage->addRow("Nome:", nome);
    editPage->addRow("Tag:", tag);
    editPage->addRow("Descrizione:", desc);
    editPage->addRow("Data:", data);
    editPage->addRow("Ora Inizio:", oraInizio);
    editPage->addRow("Ora Fine:", oraFine);
    editPage->addRow("Link:", link);
    editPage->addRow("Partecipanti:", partecipanti);    
    //aggiunta bottoni
    QDialogButtonBox* bottoni = new QDialogButtonBox();
    bottoni->addButton(QDialogButtonBox::Cancel);
    bottoni->addButton(QDialogButtonBox::Ok);
    bottoni->button(QDialogButtonBox::Cancel)->setText("Annulla");
    bottoni->button(QDialogButtonBox::Ok)->setText("Salva");
    editPage->addRow(bottoni);
    QObject::connect(bottoni->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &EditVisitor::eventoAnnullato);
    QObject::connect(bottoni->button(QDialogButtonBox::Ok), &QPushButton::clicked,[=, &riun](){
        //validazione del form e applicazione modifiche
        if(nome->text().trimmed().isEmpty())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo nome non può essere vuoto");
        else if(tag->text().trimmed().isEmpty())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo tag non può essere vuoto");
        else if(!data->date().isValid())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo data non è valido");
        else if(!oraInizio->time().isValid())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo ora inizio non è valido");
        else if(!oraFine->time().isValid())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo ora fine non è valido");
        else{
            QStringList membri = partecipanti->toPlainText().trimmed().split(',', Qt::SkipEmptyParts);
            for(QString& m : membri)
                m = m.trimmed();
            membri.removeAll(QString());
            if(membri.isEmpty()) {
                QMessageBox::warning(bottoni, "ATTENZIONE", "Inserire almeno un partecipante valido");}
            else{
                riun.setNome(nome->text());
                riun.setTag(tag->text());
                riun.setDesc(desc->toPlainText());
                QDate newData(data->date());
                riun.setData(newData);
                riun.setOraInizio(oraInizio->time());
                riun.setOraFine(oraFine->time());
                riun.setLink(link->text());
                QVector<QString> part = membri.toVector();
                riun.setPartecipanti(part);
                emit eventoModificato(dataPrec, newData);
            }
        }
    });
}

void EditVisitor::visit(Appuntamento& app){
    QDate dataPrec = app.getData();
    QLineEdit* nome = new QLineEdit(app.getNome());
    QLineEdit* tag = new QLineEdit(app.getTag());
    QTextEdit* desc = new QTextEdit(app.getDesc());
    QDateEdit* data = new QDateEdit(dataPrec);
    QTimeEdit* oraInizio = new QTimeEdit(app.getOraInizio());
    QTimeEdit* oraFine = new QTimeEdit(app.getOraFine());
    QLineEdit* contatto = new QLineEdit(app.getContatto());
    QLineEdit* luogo = new QLineEdit(app.getLuogo());
    editPage->addRow("Nome:", nome);
    editPage->addRow("Tag:", tag);
    editPage->addRow("Descrizione:", desc);
    editPage->addRow("Data:", data);
    editPage->addRow("Ora Inizio:", oraInizio);
    editPage->addRow("Ora Fine:", oraFine);
    editPage->addRow("Contatto:", contatto);
    editPage->addRow("Luogo: ", luogo);
    //aggiunta bottoni
    QDialogButtonBox* bottoni = new QDialogButtonBox();
    bottoni->addButton(QDialogButtonBox::Cancel);
    bottoni->addButton(QDialogButtonBox::Ok);
    bottoni->button(QDialogButtonBox::Cancel)->setText("Annulla");
    bottoni->button(QDialogButtonBox::Ok)->setText("Salva");
    editPage->addRow(bottoni);
    QObject::connect(bottoni->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &EditVisitor::eventoAnnullato);
    QObject::connect(bottoni->button(QDialogButtonBox::Ok), &QPushButton::clicked,[=, &app](){
        //validazione del form e applicazione modifiche
        if(nome->text().trimmed().isEmpty())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo nome non può essere vuoto");
        else if(tag->text().trimmed().isEmpty())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo tag non può essere vuoto");
        else if(!data->date().isValid())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo data non è valido");
        else if(!oraInizio->time().isValid())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo ora inizio non è valido");
        else if(luogo->text().trimmed().isEmpty())
            QMessageBox::warning(bottoni, "ATTENZIONE", "Il campo luogo non può essere vuoto");
        else{
            app.setNome(nome->text());
            app.setTag(tag->text());
            app.setDesc(desc->toPlainText());
            QDate newData(data->date());
            app.setData(newData);
            app.setOraInizio(oraInizio->time());
            app.setOraFine(oraFine->time());
            app.setContatto(contatto->text());
            app.setLuogo(luogo->text());
            emit eventoModificato(dataPrec, newData);
        }
    });
}
