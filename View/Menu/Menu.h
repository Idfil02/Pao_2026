#ifndef MENU_H
#define MENU_H
#include <QWidget>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QToolButton>
#include "Model/Calendario.h"
#include "View/Agenda/Agenda.h"
#include "View/DeadlineWindow/DeadlineWindow.h"

class Menu: public QToolBar{    
    Q_OBJECT

private:
    Calendario* calendario;
    DeadlineWindow* scadenze;
    Agenda* agendaTab;
    QToolButton* addNew;
    QAction* addAppuntamento;
    QAction* addAttivita;
    QAction* addDeadline;
    QAction* addRiunione;
    QToolButton* save;
    QMenu* menuEsportazione;
    QMenu* addMenu;
    QAction* saveJSON;
    QAction* saveXML;
    QAction* import;
    void initConnections();
public:
    Menu(Calendario* cal,Agenda* agenda, DeadlineWindow* scad,QWidget* parent = nullptr);
    ~Menu() = default;

signals:
    void agendaLoaded();
    void createNew(Evento*);
};
#endif // MENU_H
