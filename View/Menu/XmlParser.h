#ifndef XMLPARSER_H
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "Model/Calendario.h"
#define XMLPARSER_H
class XmlParser{
private:

public:
    static bool saveToXml(const QString& filename, const Calendario& calendario);

    static bool loadFromXml(const QString& filename, Calendario& calendario);
};
#endif // XMLPARSER_H
