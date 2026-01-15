#ifndef DEADLINEINFOVISITOR_H
#define DEADLINEINFOVISITOR_H
#include "Model/EventVisitor.h"
#include <QTextEdit>
class DeadlineInfoVisitor: public EventVisitor{
private:
    QTextEdit* dettagliDeadline;
public:
    explicit DeadlineInfoVisitor(QTextEdit*);
    virtual void visit(Deadline&);
};

#endif // DEADLINEINFOVISITOR_H
