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
        return false;
    }
    QXmlStreamReader r(&file);
    while(!r.atEnd() && !r.hasError()){
        QXmlStreamReader::TokenType token = r.readNext();
        //individuato un nodo, capisco che tipo di evento è e creo l'oggetto specifico
        if(token == QXmlStreamReader::StartElement){
            QString elementName = r.name().toString();
            if(elementName == "deadline"){
                //creo l'oggetto deadline e assegno i valori letti indipendentemente dall'ordine in cui si trovano
                Deadline* deadline = new Deadline();
                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name() == "deadline")){
                    r.readNext();
                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();
                        r.readNext();
                        if(r.tokenType() == QXmlStreamReader::Characters){
                            QString value = r.text().toString();
                            if(fieldName == "nome") deadline->setNome(value);
                            else if(fieldName == "tag") deadline->setTag(value);
                            else if(fieldName == "desc") deadline->setDesc(value);
                            else if(fieldName == "data") deadline->setData(QDate::fromString(value));
                            else if(fieldName == "completato") deadline->setCompletato(value == "true");
                        }
                    }
                }
                calendario.addEvento(deadline);
            }
            else if(elementName == "attivita"){
                //creo l'oggetto attivita e assegno i valori letti indipendentemente dall'ordine in cui si trovano
                Attivita* attivita = new Attivita();
                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name() == "attivita")){
                    r.readNext();
                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();
                        r.readNext();
                        if(r.tokenType() == QXmlStreamReader::Characters){
                            QString value = r.text().toString();
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
            }
            else if(elementName == "riunione"){
                //creo l'oggetto riunione e assegno i valori letti indipendentemente dall'ordine in cui si trovano
                Riunione* riunione = new Riunione();
                QVector<QString> partecipanti;
                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name() == "riunione")){
                    r.readNext();
                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();
                        if(fieldName == "partecipanti"){
                            r.readNext();
                            //inserisco partecipanti nel vettore per ogni elemento persona che trovo
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
            }
            else if(elementName == "appuntamento"){
                //creo l'oggetto appuntamento e assegno i valori letti indipendentemente dall'ordine in cui si trovano
                Appuntamento* appuntamento = new Appuntamento();
                while(!(r.tokenType() == QXmlStreamReader::EndElement && r.name() == "appuntamento")){
                    r.readNext();
                    if(r.tokenType() == QXmlStreamReader::StartElement){
                        QString fieldName = r.name().toString();
                        r.readNext();
                        if(r.tokenType() == QXmlStreamReader::Characters){
                            QString value = r.text().toString();
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
            }
        }
    }
    if(r.hasError()){
        return false;
    }
    file.close();
    return true;
}
