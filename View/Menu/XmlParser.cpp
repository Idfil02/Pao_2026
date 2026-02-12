#include "XmlParser.h"
#include "Model/Deadline.h"
#include "Model/Riunione.h"
#include "Model/Appuntamento.h"
#include <QDate>
#include <QFile>
#include <QMessageBox>

bool XmlParser::saveToXml(const QString& filename, const Calendario& calendario){
    QFile save(filename);
    if (!save.open(QIODevice::WriteOnly))
        return false;
    QXmlStreamWriter* w = new QXmlStreamWriter(&save);
    w->setAutoFormatting(true);
    w->writeStartDocument();
    w->writeStartElement("calendario");
    for(auto e:calendario.getImpegni()){
        e->toXml(*w);
    }
    w->writeEndElement();
    w->writeEndDocument();
    save.close();
    return true;
}

bool XmlParser::loadFromXml(const QString& filename, Calendario& calendario){
    QFile file(filename);
    qDebug() << "super inizio";

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        return false;
    }

    QXmlStreamReader r(&file);

    while(!r.atEnd() && !r.hasError()){
        QXmlStreamReader::TokenType token = r.readNext();

        if(token == QXmlStreamReader::StartElement){
            QString elementName = r.name().toString();

            if(elementName == "deadline"){
                Deadline* deadline = new Deadline();

                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name().toString() == "deadline")){
                    r.readNext();

                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();
                        QString value = r.readElementText().trimmed();

                        if(fieldName == "nome"){
                            if(!value.isEmpty()){
                                deadline->setNome(value);
                            } else {
                                delete deadline;
                                return false;
                            }
                        }
                        else if(fieldName == "tag") deadline->setTag(value);
                        else if(fieldName == "desc") deadline->setDesc(value);
                        else if(fieldName == "data"){
                            QDate date = QDate::fromString(value);
                            if(date.isValid())
                                deadline->setData(date);
                            else{
                                delete deadline;
                                return false;
                            }
                        }
                        else if(fieldName == "completato") deadline->setCompletato(value == "true");
                    }
                }
                calendario.addEvento(deadline);
            }

            else if(elementName == "attivita"){
                Attivita* attivita = new Attivita();

                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name().toString() == "attivita")){
                    r.readNext();

                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();
                        QString value = r.readElementText().trimmed();

                        if(fieldName == "nome"){
                            if(!value.isEmpty()){
                                attivita->setNome(value);
                            } else {
                                delete attivita;
                                return false;
                            }
                        }
                        else if(fieldName == "tag") attivita->setTag(value);
                        else if(fieldName == "desc") attivita->setDesc(value);
                        else if(fieldName == "data"){
                            QDate date = QDate::fromString(value);
                            if(date.isValid())
                                attivita->setData(date);
                            else{
                                delete attivita;
                                return false;
                            }
                        }
                        else if(fieldName == "ora_inizio"){
                            QTime time = QTime::fromString(value);
                            if(time.isValid())
                                attivita->setOraInizio(time);
                            else{
                                delete attivita;
                                return false;
                            }
                        }
                        else if(fieldName == "ora_fine"){
                            QTime time = QTime::fromString(value);
                            if(time.isValid())
                                attivita->setOraFine(time);
                            else{
                                delete attivita;
                                return false;
                            }
                        }
                    }
                }
                calendario.addEvento(attivita);
            }

            else if(elementName == "riunione"){
                Riunione* riunione = new Riunione();
                QVector<QString> partecipanti;

                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name().toString() == "riunione")){
                    r.readNext();

                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();

                        if(fieldName == "partecipanti"){
                            // Legge l'elemento partecipanti che contiene più elementi persona
                            while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name().toString() == "partecipanti")){
                                r.readNext();

                                if(r.tokenType() == QXmlStreamReader::StartElement && r.name().toString() == "persona"){
                                    QString persona = r.readElementText().trimmed();
                                    if(!persona.isEmpty()){
                                        partecipanti.push_back(persona);
                                    } else {
                                        delete riunione;
                                        return false;
                                    }
                                }
                            }
                        }
                        else {
                            // Campi semplici della riunione
                            QString value = r.readElementText().trimmed();

                            if(fieldName == "nome"){
                                if(!value.isEmpty()){
                                    riunione->setNome(value);
                                } else {
                                    delete riunione;
                                    return false;
                                }
                            }
                            else if(fieldName == "tag") riunione->setTag(value);
                            else if(fieldName == "desc") riunione->setDesc(value);
                            else if(fieldName == "data"){
                                QDate date = QDate::fromString(value);
                                if(date.isValid())
                                    riunione->setData(date);
                                else{
                                    delete riunione;
                                    return false;
                                }
                            }
                            else if(fieldName == "ora_inizio"){
                                QTime time = QTime::fromString(value);
                                if(time.isValid())
                                    riunione->setOraInizio(time);
                                else{
                                    delete riunione;
                                    return false;
                                }
                            }
                            else if(fieldName == "ora_fine"){
                                QTime time = QTime::fromString(value);
                                if(time.isValid())
                                    riunione->setOraFine(time);
                                else{
                                    delete riunione;
                                    return false;
                                }
                            }
                            else if(fieldName == "link") riunione->setLink(value);
                        }
                    }
                }
                riunione->setPartecipanti(partecipanti);
                calendario.addEvento(riunione);
            }

            else if(elementName == "appuntamento"){
                Appuntamento* appuntamento = new Appuntamento();

                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name().toString() == "appuntamento")){
                    r.readNext();

                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();
                        QString value = r.readElementText().trimmed();

                        qDebug() << "Leggo campo:" << fieldName << "valore:" << value;

                        if(fieldName == "nome"){
                            if(!value.isEmpty()){
                                appuntamento->setNome(value);
                            } else {
                                delete appuntamento;
                                return false;
                            }
                        }
                        else if(fieldName == "tag"){
                            appuntamento->setTag(value);
                        }
                        else if(fieldName == "desc"){
                            appuntamento->setDesc(value);
                        }
                        else if(fieldName == "data"){
                            QDate date = QDate::fromString(value);
                            if(date.isValid()){
                                appuntamento->setData(date);
                            } else {
                                delete appuntamento;
                                return false;
                            }
                        }
                        else if(fieldName == "ora_inizio"){
                            QTime time = QTime::fromString(value);
                            if(time.isValid()){
                                appuntamento->setOraInizio(time);
                            } else {
                                delete appuntamento;
                                return false;
                            }
                        }
                        else if(fieldName == "ora_fine"){
                            QTime time = QTime::fromString(value);
                            if(time.isValid()){
                                appuntamento->setOraFine(time);
                            } else {
                                delete appuntamento;
                                return false;
                            }
                        }
                        else if(fieldName == "luogo"){
                            if(!value.isEmpty()){
                                appuntamento->setLuogo(value);
                            } else {
                                delete appuntamento;
                                return false;
                            }
                        }
                        else if(fieldName == "contatto"){
                            appuntamento->setContatto(value);
                        }
                    }
                }
                calendario.addEvento(appuntamento);
            }
        }
    }

    if(r.hasError()){
        qDebug() << "Errore XML:" << r.errorString();
        return false;
    }

    file.close();
    return true;
}
