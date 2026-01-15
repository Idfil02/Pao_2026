#ifndef MENU_H
#define MENU_H
#include <QWidget>
#include <QToolBar>
#include <QAction>

class Menu: public QToolBar{
    Q_OBJECT

public:
    Menu(QWidget* parent = nullptr);
    ~Menu() = default;
};
#endif // MENU_H
