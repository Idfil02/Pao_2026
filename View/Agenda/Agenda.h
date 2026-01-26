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
    void clearView();
    ~Agenda() = default;
    Calendario* getCalendario() const {return calendario;}
private:
    QCalendarWidget* calendarWidget;
    QListWidget* eventiDelGiorno;
    QFormLayout* dettagliEvento;
    Calendario* calendario;
    void dataConImpegni(const QDate&);
    void initConnections();
public slots:
    void cambioEvento(QListWidgetItem*);
    void giornoSelezionato(const QDate&); 
signals:
    void richiestaEdit(Evento*);
    void eventoEliminato(Evento*, QDate);
};

#endif // AGENDA_H

