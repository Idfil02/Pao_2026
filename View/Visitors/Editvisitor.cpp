#include "Editvisitor.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QHBoxLayout>
EditVisitor::EditVisitor(QFormLayout* page, QWidget* parent): QObject(parent),editPage(page){}

void EditVisitor::visit(Deadline& scadenza){
    QDate dataPrec = scadenza.getData();
    QLineEdit* nome = new QLineEdit(scadenza.getNome());//nome
    QLineEdit* tag = new QLineEdit(scadenza.getTag()); //tag
    QTextEdit* desc = new QTextEdit(scadenza.getDesc()); //descrizione
    QDateEdit* data = new QDateEdit(dataPrec);
    editPage->addRow("Nome:", nome);
    editPage->addRow("Tag:", tag);
    editPage->addRow("Descrizione:", desc);
    editPage->addRow("Data:", data);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* annulla = new QPushButton("Annulla");
    buttonLayout->addWidget(annulla);
    QPushButton* salva = new QPushButton("Salva Modifiche");
    buttonLayout->addWidget(salva);
    editPage->addRow(buttonLayout);
    Deadline* ptr = &scadenza;
    QObject::connect(salva, &QPushButton::clicked,[=](){
        ptr->setNome(nome->text());
        ptr->setTag(tag->text());
        QString dsc = desc->toPlainText();
        ptr->setDesc(dsc);
        QDate newData(data->date());
        ptr->setData(newData);
        emit eventoModificato(dataPrec, newData);
    });
    QObject::connect(annulla, &QPushButton::clicked, this, &EditVisitor::eventoAnnullato);
}


void EditVisitor::visit(Attivita& att){
    QDate dataPrec = att.getData();
    QLineEdit* nome = new QLineEdit(att.getNome());//nome
    QLineEdit* tag = new QLineEdit(att.getTag()); //tag
    QTextEdit* desc = new QTextEdit(att.getDesc()); //descrizione
    QDateEdit* data = new QDateEdit(dataPrec);
    QTimeEdit* oraInizio = new QTimeEdit(att.getOraInizio());
    QTimeEdit* oraFine = new QTimeEdit(att.getOraFine());
    editPage->addRow("Nome:", nome);
    editPage->addRow("Tag:", tag);
    editPage->addRow("Descrizione:", desc);
    editPage->addRow("Data:", data);
    editPage->addRow("Ora Inizio:", oraInizio);
    editPage->addRow("Ora Fine:", oraFine);
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* annulla = new QPushButton("Annulla");
    buttonLayout->addWidget(annulla);
    QPushButton* salva = new QPushButton("Salva Modifiche");
    buttonLayout->addWidget(salva);
    editPage->addRow(buttonLayout);
    Attivita* ptr = &att;
    QObject::connect(salva, &QPushButton::clicked,[=](){
        ptr->setNome(nome->text());
        ptr->setTag(tag->text());
        QString dsc = desc->toPlainText();
        ptr->setDesc(dsc);
        QDate newData(data->date());
        ptr->setData(newData);
        QTime newOraInizio(oraInizio->time());
        ptr->setOraInizio(newOraInizio);
        QTime newOraFine(oraFine->time());
        ptr->setOraFine(newOraFine);
        emit eventoModificato(dataPrec, newData);
    });
    QObject::connect(annulla, &QPushButton::clicked, this, &EditVisitor::eventoAnnullato);
}


void EditVisitor::visit(Riunione& riun){
    QDate dataPrec = riun.getData();
    QLineEdit* nome = new QLineEdit(riun.getNome());//nome
    QLineEdit* tag = new QLineEdit(riun.getTag()); //tag
    QTextEdit* desc = new QTextEdit(riun.getDesc()); //descrizione
    QDateEdit* data = new QDateEdit(dataPrec);
    QTimeEdit* oraInizio = new QTimeEdit(riun.getOraInizio());
    QTimeEdit* oraFine = new QTimeEdit(riun.getOraFine());
    QLineEdit* link = new QLineEdit(riun.getLink());
    QTextEdit* partecipanti = new QTextEdit((riun.getPartecipanti()).toList().join(','));

    editPage->addRow("Nome:", nome);
    editPage->addRow("Tag:", tag);
    editPage->addRow("Descrizione:", desc);
    editPage->addRow("Data:", data);
    editPage->addRow("Ora Inizio:", oraInizio);
    editPage->addRow("Ora Fine:", oraFine);
    editPage->addRow("Link:", link);
    editPage->addRow("Partecipanti:", partecipanti);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* annulla = new QPushButton("Annulla");
    buttonLayout->addWidget(annulla);
    QPushButton* salva = new QPushButton("Salva Modifiche");
    buttonLayout->addWidget(salva);
    editPage->addRow(buttonLayout);
    Riunione* ptr = &riun;

    QObject::connect(salva, &QPushButton::clicked,[=](){
        ptr->setNome(nome->text());
        ptr->setTag(tag->text());
        QString dsc = desc->toPlainText();
        ptr->setDesc(dsc);
        QDate newData(data->date());
        ptr->setData(newData);
        QTime newOraInizio(oraInizio->time());
        ptr->setOraInizio(newOraInizio);
        QTime newOraFine(oraFine->time());
        ptr->setOraFine(newOraFine);
        ptr->setLink(link->text());
        QStringList membri = partecipanti->toPlainText().split(',');
        QVector<QString> part = membri.toVector();
        ptr->setPartecipanti(part);
        emit eventoModificato(dataPrec, newData);
    });
    QObject::connect(annulla, &QPushButton::clicked, this, &EditVisitor::eventoAnnullato);
}


void EditVisitor::visit(Appuntamento& app){
    QDate dataPrec = app.getData();
    QLineEdit* nome = new QLineEdit(app.getNome());//nome
    QLineEdit* tag = new QLineEdit(app.getTag()); //tag
    QTextEdit* desc = new QTextEdit(app.getDesc()); //descrizione
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
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* annulla = new QPushButton("Annulla");
    buttonLayout->addWidget(annulla);
    QPushButton* salva = new QPushButton("Salva Modifiche");
    buttonLayout->addWidget(salva);
    editPage->addRow(buttonLayout);
    Appuntamento* ptr = &app;
    QObject::connect(salva, &QPushButton::clicked,[=](){
        ptr->setNome(nome->text());
        ptr->setTag(tag->text());
        QString dsc = desc->toPlainText();
        ptr->setDesc(dsc);
        QDate newData(data->date());
        ptr->setData(newData);
        QTime newOraInizio(oraInizio->time());
        ptr->setOraInizio(newOraInizio);
        QTime newOraFine(oraFine->time());
        ptr->setOraFine(newOraFine);
        ptr->setContatto(contatto->text());
        ptr->setLuogo(luogo->text());
        emit eventoModificato(dataPrec, newData);
    });
    QObject::connect(annulla, &QPushButton::clicked, this, &EditVisitor::eventoAnnullato);
}
