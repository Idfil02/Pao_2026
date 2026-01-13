#ifndef DEADLINEWINDOW_H
#define DEADLINEWINDOW_H
#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QVBoxLayout>
class DeadlineWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DeadlineWindow(QWidget *parent = nullptr);
    ~DeadlineWindow() = default;

    QListWidget* getDeadlinesList() const { return scadenze; }
    QTextEdit* getDeadlineDetails() const { return dettagliDeadline; }

private:
    QListWidget* scadenze;
    QTextEdit* dettagliDeadline;
};
#endif // DEADLINEWINDOW_H
