#ifndef EDITVISITOR_H
#define EDITVISITOR_H
#include <QFormLayout>
#include "Model/EventVisitor.h"
class EditVisitor : public QObject, public EventVisitor
{
    Q_OBJECT
private:
    QFormLayout* editPage;
public:
    explicit EditVisitor(QFormLayout*, QWidget *parent = nullptr);
    virtual void visit(Deadline&) override;
    virtual void visit(Attivita&) override;
    virtual void visit(Riunione&) override;
    virtual void visit(Appuntamento&) override;
signals:
    void eventoModificato(const QDate&, const QDate&);
    void eventoAnnullato();
};

#endif // EDITVISITOR_H
