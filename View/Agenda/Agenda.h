#ifndef AGENDA_H
#define AGENDA_H
#include <QWidget>
#include <QCalendarWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QFormLayout>
#include "Model/Calendario.h"
class Agenda : public QWidget
{
    Q_OBJECT

public:
    explicit Agenda(Calendario*,QWidget *parent = nullptr);
    ~Agenda() = default;
    Calendario* getCalendar() const { return calendario; }
    QCalendarWidget* getCalendarWidget() const { return calendarWidget; }
    QListWidget* getEventList() const { return eventiDelGiorno; }
    QFormLayout* getEventDetails() const { return dettagliEvento; }
private:
    QCalendarWidget* calendarWidget;
    QListWidget* eventiDelGiorno;
    QFormLayout* dettagliEvento;
    Calendario* calendario;
public slots:
    void dataConImpegni(const QDate&);
    void cambioEvento(QListWidgetItem*);
    void giornoSelezionato(const QDate&);
    void eventoEliminato(Evento*, QDate);
    void clearView();
};

#endif // AGENDA_H

