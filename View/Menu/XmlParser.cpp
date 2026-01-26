#include "XmlParser.h"
#include "Model/Deadline.h"
#include "Model/Riunione.h"
#include "Model/Appuntamento.h"
#include <QDate>
#include <QFile>

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
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Failed to open file:" << filename;
        return false;
    }

    QXmlStreamReader r(&file);

    while(!r.atEnd() && !r.hasError()){
        QXmlStreamReader::TokenType token = r.readNext();

        if(token == QXmlStreamReader::StartDocument){
            qDebug() << "Start document";
            continue;
        }

        if(token == QXmlStreamReader::StartElement){
            QString elementName = r.name().toString();
            qDebug() << "Start element:" << elementName;

            if(elementName == "deadline"){
                Deadline* deadline = new Deadline();
                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name() == "deadline")){
                    r.readNext();
                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();
                        r.readNext();
                        if(r.tokenType() == QXmlStreamReader::Characters){
                            QString value = r.text().toString();
                            qDebug() << "Field:" << fieldName << "Value:" << value;

                            if(fieldName == "nome") deadline->setNome(value);
                            else if(fieldName == "tag") deadline->setTag(value);
                            else if(fieldName == "desc") deadline->setDesc(value);
                            else if(fieldName == "data") deadline->setData(QDate::fromString(value));
                            else if(fieldName == "completato") deadline->setCompletato(value == "true");
                        }
                    }
                }
                calendario.addEvento(deadline);
                qDebug() << "Added deadline:" << deadline->getNome();
            }
            else if(elementName == "attivita"){
                Attivita* attivita = new Attivita();
                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name() == "attivita")){
                    r.readNext();
                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();
                        r.readNext();
                        if(r.tokenType() == QXmlStreamReader::Characters){
                            QString value = r.text().toString();
                            qDebug() << "Field:" << fieldName << "Value:" << value;

                            if(fieldName == "nome") attivita->setNome(value);
                            else if(fieldName == "tag") attivita->setTag(value);
                            else if(fieldName == "desc") attivita->setDesc(value);
                            else if(fieldName == "data") attivita->setData(QDate::fromString(value));
                            else if(fieldName == "ora_inizio") attivita->setOraInizio(QTime::fromString(value));
                            else if(fieldName == "ora_fine") attivita->setOraFine(QTime::fromString(value));
                        }
                    }
                }
                calendario.addEvento(attivita);
                qDebug() << "Added attivita:" << attivita->getNome();
            }
            else if(elementName == "riunione"){
                Riunione* riunione = new Riunione();
                QVector<QString> partecipanti;

                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name() == "riunione")){
                    r.readNext();
                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();

                        if(fieldName == "partecipanti"){
                            // Skip to content
                            r.readNext();
                            while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name() == "partecipanti")){
                                if(r.tokenType() == QXmlStreamReader::StartElement && r.name() == "persona"){
                                    r.readNext();
                                    if(r.tokenType() == QXmlStreamReader::Characters){
                                        partecipanti.push_back(r.text().toString());
                                    }
                                }
                                r.readNext();
                            }
                        }
                        else{
                            r.readNext();
                            if(r.tokenType() == QXmlStreamReader::Characters){
                                QString value = r.text().toString();
                                qDebug() << "Field:" << fieldName << "Value:" << value;

                                if(fieldName == "nome") riunione->setNome(value);
                                else if(fieldName == "tag") riunione->setTag(value);
                                else if(fieldName == "desc") riunione->setDesc(value);
                                else if(fieldName == "data") riunione->setData(QDate::fromString(value));
                                else if(fieldName == "ora_inizio") riunione->setOraInizio(QTime::fromString(value));
                                else if(fieldName == "ora_fine") riunione->setOraFine(QTime::fromString(value));
                                else if(fieldName == "link") riunione->setLink(value);
                            }
                        }
                    }
                }
                riunione->setPartecipanti(partecipanti);
                calendario.addEvento(riunione);
                qDebug() << "Added riunione:" << riunione->getNome();
            }
            else if(elementName == "appuntamento"){
                Appuntamento* appuntamento = new Appuntamento();
                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name() == "appuntamento")){
                    r.readNext();
                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();
                        r.readNext();
                        if(r.tokenType() == QXmlStreamReader::Characters){
                            QString value = r.text().toString();
                            qDebug() << "Field:" << fieldName << "Value:" << value;

                            if(fieldName == "nome") appuntamento->setNome(value);
                            else if(fieldName == "tag") appuntamento->setTag(value);
                            else if(fieldName == "desc") appuntamento->setDesc(value);
                            else if(fieldName == "data") appuntamento->setData(QDate::fromString(value));
                            else if(fieldName == "ora_inizio") appuntamento->setOraInizio(QTime::fromString(value));
                            else if(fieldName == "ora_fine") appuntamento->setOraFine(QTime::fromString(value));
                            else if(fieldName == "luogo") appuntamento->setLuogo(value);
                            else if(fieldName == "contatto") appuntamento->setContatto(value);
                        }
                    }
                }
                calendario.addEvento(appuntamento);
                qDebug() << "Added appuntamento:" << appuntamento->getNome();
            }
        }
    }

    if(r.hasError()){
        qDebug() << "XML parsing error:" << r.errorString();
        return false;
    }

    file.close();
    qDebug() << "XML loaded successfully";
    return true;
}
