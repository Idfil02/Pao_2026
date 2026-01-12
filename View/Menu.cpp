#include "Menu.h"

Menu::Menu(QWidget *parent) : QToolBar("Menu", parent){
    setMovable(false);
    setFloatable(false);

    QAction* add_new = new QAction("&Nuovo", this);
    QAction* save = new QAction("&Salva", this);
    QAction* import = new QAction("&Importa", this);

    addAction(add_new);
    addAction(save);
    addAction(import);
}
