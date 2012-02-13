#-------------------------------------------------
#
# Project created by QtCreator 2012-02-13T08:43:22
#
#-------------------------------------------------

QT       += core gui

TARGET = iMeetingDesktop
TEMPLATE = app


SOURCES += main.cpp\
        VentanaPrincipal.cpp \
    Servicios/ServicioGestionSistemaDirectorios.cpp \
    ControladoresVista/ControladorListadoAvance.cpp \
    Lib/qt-json/json.cpp

HEADERS  += VentanaPrincipal.h \
    Servicios/ServicioGestionSistemaDirectorios.h \
    ControladoresVista/ControladorListadoAvance.h \
    Lib/qt-json/json.h

FORMS    += VentanaPrincipal.ui
