#include "editvisitor.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
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
    QPushButton* salva = new QPushButton("Salva Modifiche");
    editPage->addWidget(salva);
    Deadline* ptr = &scadenza;
    QObject::connect(salva, &QPushButton::clicked,[=](){
        QString param = nome->text();
        ptr->setNome(param);
        param = tag->text();
        ptr->setTag(param);
        param = desc->toPlainText();
        ptr->setDesc(param);
        QDate newData(data->date());
        ptr->setData(newData);
        emit eventoModificato(dataPrec, newData);
    });
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
    QPushButton* salva = new QPushButton("Salva Modifiche");
    editPage->addWidget(salva);
    Attivita* ptr = &att;
    QObject::connect(salva, &QPushButton::clicked,[=](){
        QString param = nome->text();
        ptr->setNome(param);
        param = tag->text();
        ptr->setTag(param);
        param = desc->toPlainText();
        ptr->setDesc(param);
        QDate newData(data->date());
        ptr->setData(newData);
        QTime newOraInizio(oraInizio->time());
        ptr->setOraInizio(newOraInizio);
        QTime newOraFine(oraFine->time());
        ptr->setOraInizio(newOraFine);
        emit eventoModificato(dataPrec, newData);
    });
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
    editPage->addRow("Nome:", nome);
    editPage->addRow("Tag:", tag);
    editPage->addRow("Descrizione:", desc);
    editPage->addRow("Data:", data);
    editPage->addRow("Ora Inizio:", oraInizio);
    editPage->addRow("Ora Fine:", oraFine);
    editPage->addRow("Link:", link);
    QPushButton* salva = new QPushButton("Salva Modifiche");
    editPage->addWidget(salva);
    Riunione* ptr = &riun;
    QObject::connect(salva, &QPushButton::clicked,[=](){
        QString param = nome->text();
        ptr->setNome(param);
        param = tag->text();
        ptr->setTag(param);
        param = desc->toPlainText();
        ptr->setDesc(param);
        QDate newData(data->date());
        ptr->setData(newData);
        QTime newOraInizio(oraInizio->time());
        ptr->setOraInizio(newOraInizio);
        QTime newOraFine(oraFine->time());
        ptr->setOraInizio(newOraFine);
        param = link->text();
        ptr->setLink(param);
        emit eventoModificato(dataPrec, newData);
    });
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
    QPushButton* salva = new QPushButton("Salva Modifiche");
    editPage->addWidget(salva);
    Appuntamento* ptr = &app;
    QObject::connect(salva, &QPushButton::clicked,[=](){
        QString param = nome->text();
        ptr->setNome(param);
        param = tag->text();
        ptr->setTag(param);
        param = desc->toPlainText();
        ptr->setDesc(param);
        QDate newData(data->date());
        ptr->setData(newData);
        QTime newOraInizio(oraInizio->time());
        ptr->setOraInizio(newOraInizio);
        QTime newOraFine(oraFine->time());
        ptr->setOraInizio(newOraFine);
        param = contatto->text();
        ptr->setContatto(param);
        param = luogo->text();
        ptr->setLuogo(param);
        emit eventoModificato(dataPrec, newData);
    });
}
