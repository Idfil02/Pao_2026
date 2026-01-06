#ifndef CALENDARIO_H
#define CALENDARIO_H
#include "Evento.h"
#include <QVector>
class Calendario {
private:
    QVector<Evento*> impegni;
public:
    void addEvento(Evento&);
    void removeEvento(Evento&);
//  void mostra() const;
};
#endif // CALENDARIO_H
