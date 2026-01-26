#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "Model/Evento.h"
#include "Model/Calendario.h"
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
    Calendario* cal;
public slots:
    void richiestaEdit(Evento*);
    void eventoModificato(const QDate &dataPrec, const QDate& newData);
};
#endif // MAINWINDOW_H
