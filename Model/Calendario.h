#ifndef CALENDARIO_H
#define CALENDARIO_H
#include "Evento.h"
#include <QVector>
class Calendario {
private:
    QVector<Evento*> impegni;
public:
    void setEventi(const QVector<Evento*>&);
    void addEvento(Evento&);
    void removeEvento(const Evento&);
//  void mostra() const;
};
#endif // CALENDARIO_H
