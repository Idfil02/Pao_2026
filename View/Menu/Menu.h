#ifndef MENU_H
#define MENU_H
#include <QWidget>
#include <QToolBar>
#include <QAction>
#include "Model/Calendario.h"
#include "View/DeadlineWindow/DeadlineWindow.h"
class Menu: public QToolBar{
    Q_OBJECT
private:
    Calendario* calendario;
    DeadlineWindow* scadenze;
public:
    Menu(Calendario* cal,DeadlineWindow* scad,QWidget* parent = nullptr);
    ~Menu() = default;
signals:
    void agendaLoaded();
};
#endif // MENU_H
