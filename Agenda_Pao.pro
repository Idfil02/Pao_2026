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
    View/DeadlineWindow/DeadlineWindow.cpp \
    View/ListaEventi/listaeventi.cpp \
    View/Menu/Menu.cpp \
    View/Menu/XmlParser.cpp \
    View/Menu/eventofactory.cpp \
    View/Visitors/AgendaVisitor.cpp \
    View/Visitors/InfoVisitor.cpp \
    View/Visitors/editvisitor.cpp \
    View/Visitors/listvisitor.cpp \
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
    View/DeadlineWindow/DeadlineWindow.h \
    View/ListaEventi/listaeventi.h \
    View/Menu/Menu.h \
    View/Menu/XmlParser.h \
    View/Menu/eventofactory.h \
    View/Visitors/AgendaVisitor.h \
    View/Visitors/InfoVisitor.h \
    View/Visitors/editvisitor.h \
    View/Visitors/listvisitor.h \
    mainwindow.h
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
