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

bool loadFromXml(const QString& filename, Calendario& calendario){
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QXmlStreamReader r;
    r.setDevice(&file);
    r.readNext();
    while(!r.atEnd()){
        if(r.isStartElement()){
            if(r.name()=="deadline"){
                Deadline deadline;
                r.readNext();
                if(r.name()=="nome"){
                    deadline.setNome(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="tag"){
                    deadline.setTag(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="desc"){
                    deadline.setDesc(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="data"){
                    deadline.setData(QDate::fromString(r.readElementText()));
                    r.readNext();
                }
                if(r.name()=="completato"){
                    deadline.setCompletato(r.readElementText()=="true" ? true : false);
                    r.readNext();
                }
                calendario.addEvento(&deadline);
                r.readNext();
            }
            if(r.name()=="attivita"){
                Attivita attivita;
                r.readNext();
                if(r.name()=="nome"){
                    attivita.setNome(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="tag"){
                    attivita.setTag(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="desc"){
                    attivita.setDesc(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="data"){
                    attivita.setData(QDate::fromString(r.readElementText()));
                    r.readNext();
                }
                if(r.name()=="ora_inizio"){
                    attivita.setOraInizio(QTime::fromString(r.readElementText()));
                    r.readNext();
                }
                if(r.name()=="ora_fine"){
                    attivita.setOraFine(QTime::fromString(r.readElementText()));
                    r.readNext();
                }
                calendario.addEvento(&attivita);
            }
            if(r.name()=="riunione"){
                Riunione riunione;
                r.readNext();
                if(r.name()=="nome"){
                    riunione.setNome(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="tag"){
                    riunione.setTag(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="desc"){
                    riunione.setDesc(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="data"){
                    riunione.setData(QDate::fromString(r.readElementText()));
                    r.readNext();
                }
                if(r.name()=="ora_inizio"){
                    riunione.setOraInizio(QTime::fromString(r.readElementText()));
                    r.readNext();
                }
                if(r.name()=="ora_fine"){
                    riunione.setOraFine(QTime::fromString(r.readElementText()));
                    r.readNext();
                }
                if(r.name()=="link"){
                    riunione.setLink(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="partecipanti"){
                    QVector<QString> partecipanti;
                    r.readNext();
                    while(r.name()=="persona"){
                        partecipanti.push_back(r.readElementText());
                        r.readNext();
                    }
                    riunione.setPartecipanti(partecipanti);
                }
                calendario.addEvento(&riunione);
            }
            if(r.name()=="appuntamento"){
                Appuntamento appuntamento;
                r.readNext();
                if(r.name()=="nome"){
                    appuntamento.setNome(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="tag"){
                    appuntamento.setTag(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="desc"){
                    appuntamento.setDesc(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="data"){
                    appuntamento.setData(QDate::fromString(r.readElementText()));
                    r.readNext();
                }
                if(r.name()=="ora_inizio"){
                    appuntamento.setOraInizio(QTime::fromString(r.readElementText()));
                    r.readNext();
                }
                if(r.name()=="ora_fine"){
                    appuntamento.setOraFine(QTime::fromString(r.readElementText()));
                    r.readNext();
                }
                if(r.name()=="luogo"){
                    appuntamento.setLuogo(r.readElementText());
                    r.readNext();
                }
                if(r.name()=="contatto"){
                    appuntamento.setContatto(r.readElementText());
                    r.readNext();
                }
            }
        }
    }
    return true;
}
