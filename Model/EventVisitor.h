#ifndef EVENTVISITOR_H
#define EVENTVISITOR_H
#include "Deadline.h"
#include "Riunione.h"
#include "Appuntamento.h"
class EventVisitor{
public:
    void visit(Deadline&);
    void visit(Attivita&);
    void visit(Riunione&);
    void visit(Appuntamento&);
}
#endif // EVENTVISITOR_H
