#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "Model/Calendario.h"

class XmlParser{
public:
    static bool saveToXml(const QString& filename, const Calendario& calendario);
    static bool loadFromXml(const QString& filename, Calendario& calendario);
};
#endif // XMLPARSER_H
