#ifndef AGENDA_H
#define AGENDA_H
#include <QWidget>
#include <QCalendarWidget>
#include <QListWidget>
#include <QFormLayout>
#include "Model/Calendario.h"

class Agenda : public QWidget
{
    Q_OBJECT

private:
    Calendario* calendario;
    QCalendarWidget* calendarWidget;
    QListWidget* eventiDelGiorno;
    QFormLayout* dettagliEvento;
    void dataConImpegni(const QDate&) const;
    void initConnections();
public:
    explicit Agenda(Calendario*,QWidget *parent = nullptr);
    ~Agenda() = default;
    void clearInfo();

public slots:
    void cambioEvento(QListWidgetItem*);
    void giornoSelezionato(const QDate&); 
signals:
    void richiestaEdit(Evento*);
    void eventoEliminato(Evento*, QDate);
};

#endif // AGENDA_H

