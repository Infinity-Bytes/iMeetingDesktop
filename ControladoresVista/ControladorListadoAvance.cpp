#include "ControladorListadoAvance.h"

#include "Lib/qt-json/json.h"

ControladorListadoAvance::ControladorListadoAvance(QObject *parent) :
    QObject(parent)
{
}

void ControladorListadoAvance::gestionaArchivo(QString archivo) {
    if(archivo.endsWith("Definicion.json")) {
        this->cargaDefinicion(archivo);
    }

    // TODO Ver Zip, su contenido y generar las actualizaciones pertinentes como si se descomprimiera
}


void ControladorListadoAvance::cargaDefinicion(QString archivo) {
    bool valido = false;
    QVariant definicionBase = QtJson::Json::parse(archivo, valido);
    if(valido && definicionBase.canConvert(QVariant::Map)) {
        QMap<QString, QVariant> defMeeting = definicionBase.toMap();

        // TODO Cargado y validacion de model
    }
}
