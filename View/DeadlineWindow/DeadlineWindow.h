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

    QListWidget* getDeadlinesList() const { return scadenze; }
    QTextEdit* getDeadlineDetails() const { return dettagliDeadline; }
    void viewRefresh();
    QWidget* buildDeadlineItem(Deadline*);

private:
    QVector<Deadline*> deadlines;
    QListWidget* scadenze;
    QTextEdit* dettagliDeadline;
private slots:
    void scadenzaSelezionata(QListWidgetItem*);
};
#endif // DEADLINEWINDOW_H
