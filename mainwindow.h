#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

class Agenda;
class DeadlineWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    QTabWidget* tabWidgets;
    Agenda* agendaTab;
    DeadlineWindow* deadlinesTab;
};
#endif // MAINWINDOW_H
