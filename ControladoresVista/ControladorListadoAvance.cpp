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
        QVariantMap defMeeting = definicionBase.toMap();
        QTreeWidgetItem * item = procesaPersonal(defMeeting, QSet<QTreeWidgetItem *>());

        // TODO Cargado y validacion de model
    }
}

QTreeWidgetItem * ControladorListadoAvance::procesaPersonal(QVariantMap persona, QSet<QTreeWidgetItem *> padres) {
    QTreeWidgetItem * salida = new QTreeWidgetItem();

    QSet<QTreeWidgetItem *> conjuntoDerivado(padres);
    conjuntoDerivado.insert(salida);

    QStringList nombresInteresDerivados;
    nombresInteresDerivados << "personas" << "jefesEntrevistadores" << "entrevistadores";

    for(QStringList::iterator it_nombresInteresDerivados = nombresInteresDerivados.begin(); it_nombresInteresDerivados != nombresInteresDerivados.end(); ++it_nombresInteresDerivados) {
        QString nombreInteres = *it_nombresInteresDerivados;

        if(persona.contains(nombreInteres)) {
            QVariantList listaPersonas = persona[nombreInteres].toList();
            for(QVariantList::iterator it_listaPersonas = listaPersonas.begin(); it_listaPersonas != listaPersonas.end(); ++it_listaPersonas) {
                QVariantMap personaDerivada = it_listaPersonas->toMap();
                if(QTreeWidgetItem * itemPersonaDerivada = procesaPersonal(personaDerivada, conjuntoDerivado)) {
                    salida->addChild(itemPersonaDerivada);
                }
            }
        }
    }


    // Si no tiene elementos derivados agregar 1 a los elementos padres
    if(!salida->childCount()) {
        for(QSet<QTreeWidgetItem *>::iterator it_padres = padres.begin(); it_padres != padres.end(); ++it_padres) {
            QTreeWidgetItem * padre = *it_padres;
            bool acumuladorCorrecto;
            int acumuladorAnterior = padre->text(DERIVADOS).toInt(&acumuladorCorrecto);
            int acumuladorActual = (acumuladorCorrecto ? acumuladorAnterior : 0) + 1;
            padre->setText(DERIVADOS, QString::number(acumuladorActual));
        }
    }

    return salida;
}
