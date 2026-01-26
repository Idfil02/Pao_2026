#ifndef DEADLINEWINDOW_H
#define DEADLINEWINDOW_H
#include "Model/Calendario.h"
#include "Model/Deadline.h"
#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QVBoxLayout>
class DeadlineWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DeadlineWindow(Calendario*,QWidget *parent = nullptr);
    ~DeadlineWindow() = default;
    void setDeadlines(const QVector<Deadline*>&);
    void addDeadline(Deadline*);
    QVector<Deadline*> getDeadlines() const {return deadlines;}
    void viewRefresh();
    void clearDeadlines();
    QWidget* buildDeadlineItem(Deadline*);

private:
    QVector<Deadline*> deadlines;
    Calendario* calendario;
    QListWidget* scadenze;
    QTextEdit* dettagliDeadline;
signals:
    void eventoEliminato(Evento*,QDate);
    void richiestaEdit(Evento*);
};
#endif // DEADLINEWINDOW_H
