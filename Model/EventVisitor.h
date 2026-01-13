#ifndef EVENTVISITOR_H
#define EVENTVISITOR_H
#include "Deadline.h"
#include "Riunione.h"
#include "Appuntamento.h"
class EventVisitor{
public:
    virtual void visit(Deadline&) = 0;
    virtual void visit(Attivita&) = 0;
    virtual void visit(Riunione&) = 0;
    virtual void visit(Appuntamento&) = 0;
};
#endif // EVENTVISITOR_H
