QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/Appuntamento.cpp \
    Model/Attivita.cpp \
    Model/Calendario.cpp \
    Model/Deadline.cpp \
    Model/Evento.cpp \
    Model/Riunione.cpp \
    View/Agenda/Agenda.cpp \
    View/Agenda/AgendaVisitor.cpp \
    View/DeadlineWindow/DeadlineWindow.cpp \
    View/Agenda/InfoVisitor.cpp \
    View/Menu/Menu.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Model/Appuntamento.h \
    Model/Attivita.h \
    Model/Calendario.h \
    Model/Deadline.h \
    Model/EventVisitor.h \
    Model/Evento.h \
    Model/Riunione.h \
    View/Agenda/Agenda.h \
    View/Agenda/AgendaVisitor.h \
    View/DeadlineWindow/DeadlineWindow.h \
    View/Agenda/InfoVisitor.h \
    View/Menu/Menu.h \
    mainwindow.h
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
