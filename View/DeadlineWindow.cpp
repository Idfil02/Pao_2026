#include "DeadlineWindow.h"

DeadlineWindow::DeadlineWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layoutDeadline = new QVBoxLayout(this);

    scadenze = new QListWidget;
    layoutDeadline->addWidget(scadenze);

    dettagliDeadline = new QTextEdit;
    dettagliDeadline->setReadOnly(true);
    dettagliDeadline->setPlaceholderText("Descrizione Scadenza");
    layoutDeadline->addWidget(dettagliDeadline);
}
