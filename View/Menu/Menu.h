#ifndef MENU_H
#define MENU_H
#include <QWidget>
#include <QToolBar>
#include <QAction>
#include "Model/Calendario.h"
class Menu: public QToolBar{
    Q_OBJECT
private:
    Calendario* calendario;
public:
    Menu(Calendario* cal,QWidget* parent = nullptr);
    ~Menu() = default;
signals:
    void agendaLoaded();
};
#endif // MENU_H
