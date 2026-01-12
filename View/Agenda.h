#ifndef AGENDA_H
#define AGENDA_H
#include <QWidget>
#include <QCalendarWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QSplitter>
#include <QHBoxLayout>
#include "../Model/Calendario.h"
class Agenda : public QWidget
{
    Q_OBJECT

public:
    explicit Agenda(QWidget *parent = nullptr);
    ~Agenda() = default;
    Calendario* getCalendar() const { return calendario; }
    QCalendarWidget* getCalendarWidget() const { return calendarWidget; }
    QListWidget* getEventList() const { return eventiDelGiorno; }
    QTextEdit* getEventDetails() const { return dettagliEvento; }
private:
    QCalendarWidget* calendarWidget;
    QListWidget* eventiDelGiorno;
    QTextEdit* dettagliEvento;
    QSplitter* splitterGiorno;
    Calendario* calendario;
    void viewUpdate(const QDate& data);
private slots:
    void dataConImpegni(const QDate& data);
    void cambioData();
};

#endif // AGENDA_H
