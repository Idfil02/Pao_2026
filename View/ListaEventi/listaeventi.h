#ifndef LISTAEVENTI_H
#define LISTAEVENTI_H
#include <QWidget>
#include <QListWidget>
#include <QFormLayout>
#include "Model/Calendario.h"
class ListaEventi : public QWidget
{
    Q_OBJECT

private:
    QList<QString> tags;
    QListWidget* listaEventi;
    QWidget* infoEvento;
    QFormLayout* infoEventoLayout;
    Calendario* calendario;
    void initConnections() {};
public:
    ListaEventi(Calendario*,QWidget* parent = nullptr);
    ~ListaEventi() = default;
    void tagsUpdate();
    void clearList();
    void clearInfo();
    void refresh();
signals:
    void richiestaEdit(Evento*);
    void eventoEliminato(Evento*, const QDate&);
};

#endif // LISTAEVENTI_H
