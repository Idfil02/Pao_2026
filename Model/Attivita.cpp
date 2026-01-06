#include "Attivita.h"

QTime Attivita::getOraInizio() const {return oraInizio;}
QTime Attivita::getOraFine() const {return oraFine;}
void Attivita::setOraInizio(QTime oi){oraInizio = oi;}
void Attivita::setOraFine(QTime of){oraFine = of;}
