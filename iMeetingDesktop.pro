#-------------------------------------------------
#
# Project created by QtCreator 2012-02-13T08:43:22
#
#-------------------------------------------------

QT       += core gui

TARGET = iMeetingDesktop
TEMPLATE = app

LIBS += -lz

SOURCES += main.cpp\
        VentanaPrincipal.cpp \
    Servicios/ServicioGestionSistemaDirectorios.cpp \
    ControladoresVista/ControladorListadoAvance.cpp \
    Lib/qt-json/json.cpp \
    Lib/quazip/quazipnewinfo.cpp \
    Lib/quazip/quazipfile.cpp \
    Lib/quazip/quazipdir.cpp \
    Lib/quazip/quazip.cpp \
    Lib/quazip/quaziodevice.cpp \
    Lib/quazip/quagzipfile.cpp \
    Lib/quazip/quacrc32.cpp \
    Lib/quazip/quaadler32.cpp \
    Lib/quazip/qioapi.cpp \
    Lib/quazip/JlCompress.cpp \
    Lib/quazip/zip.c \
    Lib/quazip/unzip.c

HEADERS  += VentanaPrincipal.h \
    Servicios/ServicioGestionSistemaDirectorios.h \
    ControladoresVista/ControladorListadoAvance.h \
    Lib/qt-json/json.h \
    Lib/quazip/zip.h \
    Lib/quazip/unzip.h \
    Lib/quazip/quazipnewinfo.h \
    Lib/quazip/quazipfileinfo.h \
    Lib/quazip/quazipfile.h \
    Lib/quazip/quazipdir.h \
    Lib/quazip/quazip.h \
    Lib/quazip/quazip_global.h \
    Lib/quazip/quaziodevice.h \
    Lib/quazip/quagzipfile.h \
    Lib/quazip/quacrc32.h \
    Lib/quazip/quachecksum32.h \
    Lib/quazip/quaadler32.h \
    Lib/quazip/JlCompress.h \
    Lib/quazip/ioapi.h \
    Lib/quazip/crypt.h

FORMS    += VentanaPrincipal.ui
