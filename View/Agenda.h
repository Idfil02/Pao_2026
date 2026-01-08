#ifndef AGENDA_H
#define AGENDA_H
#include <QWidget>
#include <QCalendarWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QSplitter>
#include <QHBoxLayout>

class Agenda : public QWidget
{
    Q_OBJECT

public:
    explicit Agenda(QWidget *parent = nullptr);
    ~Agenda() = default;

    QCalendarWidget* getCalendar() const { return calendario; }
    QListWidget* getEventList() const { return eventiDelGiorno; }
    QTextEdit* getEventDetails() const { return dettagliEvento; }

private:
    QCalendarWidget* calendario;
    QListWidget* eventiDelGiorno;
    QTextEdit* dettagliEvento;
    QSplitter* splitterGiorno;
};

#endif // AGENDA_H
