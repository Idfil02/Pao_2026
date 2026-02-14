#ifndef LISTAEVENTI_H
#define LISTAEVENTI_H
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "Model/Calendario.h"

class ListaEventi : public QWidget
{
    Q_OBJECT

private:
    Calendario* calendario;
    QList<QString> tags;
    QListWidget* listaEventi;
    QWidget* searchBar;
    QComboBox* tagList;
    QLineEdit* searchText;
    QPushButton* searchBtn;
    void initConnections();
    QVector<Evento*> filtraNome(QVector<Evento*>&, const QString&) const;
    QVector<Evento*> filtraTag(QVector<Evento*>&, const QString&) const;
public:
    ListaEventi(Calendario*,QWidget* parent = nullptr);
    ~ListaEventi() = default;
    void tagsUpdate();
    void refresh(const QVector<Evento*>&);
    void refresh();
signals:
    void richiestaEdit(Evento*);
    void eventoEliminato(Evento*, const QDate&);
    void goTo(Evento*);
};

#endif // LISTAEVENTI_H
