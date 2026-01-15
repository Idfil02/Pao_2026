#include "Menu.h"

Menu::Menu(QWidget *parent) : QToolBar("Menu", parent){
    setMovable(false);
    setFloatable(false);

    QAction* addNew = new QAction("Nuovo", this);
    QAction* save = new QAction("Salva", this);
    QAction* import = new QAction("Importa", this);
    QAction* preferences = new QAction("Preferenze", this);

    addAction(addNew);
    addAction(save);
    addAction(import);
    addAction(preferences);
}
