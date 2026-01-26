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
    void viewRefresh();
    void clearDeadlines();
    void deleteDeadline(Deadline*);
    QWidget* buildDeadlineItem(Deadline*);

private:
    QVector<Deadline*> deadlines;
    Calendario* calendario;
    QListWidget* scadenze;
    QTextEdit* dettagliDeadline;
signals:
    void eventoEliminato(Evento*,const QDate&);
    void richiestaEdit(Evento*);
    void deadlineModificata(const QDate&);
};
#endif // DEADLINEWINDOW_H
