#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTabWidget>
#include "Model/Evento.h"
#include "Model/Calendario.h"
#include "View/Agenda/Agenda.h"
#include "View/DeadlineWindow/DeadlineWindow.h"
#include "View/Menu/Menu.h"
#include "View/ListaEventi/ListaEventi.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Calendario* cal;
    QTabWidget* tabWidgets;
    Agenda* agendaTab;
    DeadlineWindow* deadlinesTab;
    ListaEventi* eventsTab;
    Menu* menu;
    void initConnections();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

public slots:
    void richiestaEdit(Evento*);
    void eventoModificato(const QDate &dataPrec, const QDate& newData);
    void eventoEliminato(Evento*, const QDate&);
    void richiestaCreate(Evento*);
};
#endif // MAINWINDOW_H
