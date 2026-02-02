#ifndef DEADLINEWINDOW_H
#define DEADLINEWINDOW_H
#include "Model/Calendario.h"
#include "Model/Deadline.h"
#include <QFormLayout>
#include <QListWidget>
#include <QVBoxLayout>
class DeadlineWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DeadlineWindow(Calendario*,QWidget *parent = nullptr);
    ~DeadlineWindow() = default;
    void addDeadline(Deadline*);
    void viewRefresh();
    void clearInfo();
    void clearDeadlines();
    void deleteDeadline(Deadline*);

private:
    QVector<Deadline*> deadlines;
    Calendario* calendario;
    QListWidget* scadenze;
    QWidget* dettagliDeadline;
    QFormLayout* dettagliLayout;
    QWidget* buildDeadlineItem(Deadline*);
signals:
    void eventoEliminato(Evento*,const QDate&);
    void richiestaEdit(Evento*);
    void deadlineModificata(const QDate&);
};
#endif // DEADLINEWINDOW_H
