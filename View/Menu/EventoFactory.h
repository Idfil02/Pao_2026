#ifndef EVENTOFACTORY_H
#define EVENTOFACTORY_H
#include "Model/Calendario.h"
#include <QJsonObject>

enum tipoEvento{deadline = 0, attivita = 1, riunione = 2, appuntamento = 3};

class EventoFactory{
public:
    EventoFactory();
    bool BuildEvento(Calendario*, QJsonObject);
};

#endif // EVENTOFACTORY_H
