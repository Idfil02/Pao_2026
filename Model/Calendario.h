#ifndef CALENDARIO_H
#define CALENDARIO_H
#include <QObject>
#include <QDate>
#include <QVector>
#include <QMap>
#include "Evento.h"
class Calendario: public QObject {
    Q_OBJECT
private:
    QVector<Evento*> impegni;
    QMap<QString, int> tags;
public:
    Calendario() = default;
    Calendario(QObject* parent = nullptr);
    ~Calendario() = default;
    void clear();
    void addEvento(Evento* e);
    void removeEvento(Evento* e);
    void tagsRefresh();
    QVector<Evento*> getImpegni() const;
    QVector<Evento*> getImpegni(const QDate& data) const;
    QVector<Evento*> getImpegniByNome(const QString&) const;
    QVector<Evento*> getImpegniByTag(const QString&) const;
    QList<QString> getTags() const;

signals:
    void aggiuntoEvento(const QDate& data);
};
#endif // CALENDARIO_H
