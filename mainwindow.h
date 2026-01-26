#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "Model/Evento.h"
#include "Model/Calendario.h"
#include "View/Agenda/Agenda.h"
#include "View/DeadlineWindow/DeadlineWindow.h"
#include "View/Menu/Menu.h"

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
    Menu* menu;
    void initConnections();
public slots:
    void richiestaEdit(Evento*);
    void eventoModificato(const QDate &dataPrec, const QDate& newData);
    void eventoEliminato(Evento*, const QDate&);
};
#endif // MAINWINDOW_H
