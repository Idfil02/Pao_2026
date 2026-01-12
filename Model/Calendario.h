#ifndef CALENDARIO_H
#define CALENDARIO_H
#include <QObject>
#include <QDate>
#include <QVector>
#include "Evento.h"
#include "Appuntamento.h"
#include "Attivita.h"
#include "Riunione.h"
#include "Deadline.h"
class Calendario: public QObject {
    Q_OBJECT
private:
    QVector<Evento*> impegni;
public:
    explicit Calendario(QObject* parent = nullptr);
    ~Calendario() = default;
    void setEventi(const QVector<Evento*>& evs);
    void addEvento(Evento& e);
    void removeEvento(const Evento& e);
    QVector<Evento*> getImpegni(const QDate& data);
//  void mostra() const;
signals:
    void aggiuntoEvento(const QDate& data);
};
#endif // CALENDARIO_H
