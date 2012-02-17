#include "ControladorListadoAvance.h"

#include "Lib/qt-json/json.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

ControladorListadoAvance::ControladorListadoAvance(QTreeWidget *arbol, QObject *parent) :
    QObject(parent), arbol(arbol)
{
}

void ControladorListadoAvance::gestionaArchivo(QString archivo) {
    if(archivo.endsWith("Definicion.json")) {
        this->cargaDefinicion(archivo);
    }

    // TODO Ver Zip, su contenido y generar las actualizaciones pertinentes como si se descomprimiera
}


void ControladorListadoAvance::cargaDefinicion(QString archivo) {

    QFile file(archivo);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    QString line = out.readAll();

    file.close(); // when your done.

    bool valido = true;
    QVariant definicionBase = QtJson::Json::parse(line, valido);
    if(valido && definicionBase.canConvert(QVariant::Map)) {
        QVariantMap defMeeting = definicionBase.toMap();
        QTreeWidgetItem * item = procesaPersonal(defMeeting, QSet<QTreeWidgetItem *>());
        item->setText(NOMBRE, defMeeting["nombreMeeting"].toString());

        // Cargado y validacion de model
        for(QMap<QString, QMap<QString, QString> >::iterator it_propiedadesPorIdentificador = propiedadesPorIdentificador.begin(); it_propiedadesPorIdentificador != propiedadesPorIdentificador.end(); ++it_propiedadesPorIdentificador) {
            QString identificador = it_propiedadesPorIdentificador.key();
            QMap<QString, QString> propiedaes = it_propiedadesPorIdentificador.value();

            QSet<QTreeWidgetItem *> itemsInteres = itemsPorIdentificador[identificador];
            for(QSet<QTreeWidgetItem *>::iterator it_widgetInteres = itemsInteres.begin(); it_widgetInteres != itemsInteres.end(); ++it_widgetInteres) {

                // TODO Cargar propiedades de interes para mostrar
                if (propiedaes.contains("nombre")) {
                    QTreeWidgetItem * itemInteres = *it_widgetInteres;
                    itemInteres->setText(NOMBRE, propiedaes["nombre"]);
                }
            }
        }

        arbol->addTopLevelItem(item);
    }
}

QTreeWidgetItem * ControladorListadoAvance::procesaPersonal(QVariantMap persona, QSet<QTreeWidgetItem *> padres) {
    QTreeWidgetItem * salida = new QTreeWidgetItem();

    // Almacenado elementos que tienen interes en un identificador especifico
    if(persona.contains("identificador")) {
        QString identificadorInteres = persona["identificador"].toString();
        QSet<QTreeWidgetItem *> conjuntoItemsPorIdentifiacor = itemsPorIdentificador[identificadorInteres];
        QMap<QString, QString> propiedaesInteres = propiedadesPorIdentificador[identificadorInteres];

        conjuntoItemsPorIdentifiacor.insert(salida);
        itemsPorIdentificador[identificadorInteres] = conjuntoItemsPorIdentifiacor;


        QStringList llaves = persona.keys();
        qDebug() << llaves;

        // Obtencion de propiedades de elemento de interés y almacenado en objeto correspondiente
        for(QStringList::iterator it_propiedades = llaves.begin(); it_propiedades != llaves.end(); ++it_propiedades) {
            QString propX = *it_propiedades;
            qDebug() << propX;
            QVariant valorPropiedad = persona[propX];
            if (valorPropiedad.canConvert(QVariant::String)) {
                QString valorPropiedadString = valorPropiedad.toString();
                if(valorPropiedadString.trimmed().length()) {
                    qDebug() << tr("propiedaesInteres[") << propX << "] = " << valorPropiedadString;

                    propiedaesInteres[propX] = valorPropiedadString;
                }
            }
        }

        propiedadesPorIdentificador[identificadorInteres] = propiedaesInteres;
    }

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
