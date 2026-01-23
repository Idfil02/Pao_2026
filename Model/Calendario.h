#ifndef CALENDARIO_H
#define CALENDARIO_H
#include <QObject>
#include <QDate>
#include <QVector>
#include "Evento.h"
class Calendario: public QObject {
    Q_OBJECT
private:
    QVector<Evento*> impegni;
public:
    explicit Calendario(QObject* parent = nullptr);
    ~Calendario() = default;
    void clear();
    void addEvento(Evento* e);
    void removeEvento(Evento* e);
    QVector<Evento*> getImpegni() const;
    QVector<Evento*> getImpegni(const QDate& data) const;
signals:
    void aggiuntoEvento(const QDate& data);
};
#endif // CALENDARIO_H
