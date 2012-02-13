#include "ServicioGestionSistemaDirectorios.h"

#include <QDebug>

ServicioGestionSistemaDirectorios::ServicioGestionSistemaDirectorios(QObject *parent) :
    QObject(parent), systemWatcher(new QFileSystemWatcher(this))
{
    this->connect(systemWatcher, SIGNAL(fileChanged(QString)), this, SLOT(archivoActualizado(QString)));
    this->connect(systemWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(directorioActualizado(QString)));
}

void ServicioGestionSistemaDirectorios::estableceDirectorioBase(QString directorioBase) {
    this->limpiaWatcher();

    if (directorioBase.length()) {
        QDir directorioInteres(directorioBase);

        if(directorioInteres.exists()) {
            this->agregaSegunDirectorio(directorioInteres);
            qDebug() << QString("Watch: ") << directorioBase;
        }
    }
}

void ServicioGestionSistemaDirectorios::archivoActualizado(QString directorioActualizado) {
    qDebug() << QString("Archivo Actualizado:") << string;
}

void ServicioGestionSistemaDirectorios::directorioActualizado(QString directorioActualizado) {
    qDebug() << QString("Directorio Actualizado:") << string;
}

void ServicioGestionSistemaDirectorios::agregaSegunDirectorio(QDir directorioInteres) {
    QString pathDirectorioInteres = directorioInteres.path();
    QSet<QString> archivosInteres = archivosPorDirectorioGestionado[pathDirectorioInteres];
    qDebug() << QString("agregaSegunDirectorio: ") <<  pathDirectorioInteres;

    // Comportamiento recursivo para agregado de directorios
    QStringList listaDirectorios = directorioInteres.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot | QDir::NoDotAndDotDot);
    for(QStringList::iterator it_listaDirectorios = listaDirectorios .begin(); it_listaDirectorios != listaDirectorios .end(); ++it_listaDirectorios) {
        this->agregaSegunDirectorio(QDir(*it_listaDirectorios));
    }

    // Agregar Archivos y generar notificacion de gestion
    QStringList listaArchivos = directorioInteres.entryList(QDir::Files);
    for(QStringList::iterator it_listaArchivos = listaArchivos.begin(); it_listaArchivos != listaArchivos.end(); ++it_listaArchivos) {
        QString nombreArchivoEnDirectorio = *it_listaArchivos;

        archivosInteres.insert(nombreArchivoEnDirectorio);
        emit gestionaArchivoEnDirectorio(nombreArchivoEnDirectorio, directorioInteres);
    }

    // Agregar directorio al Watcher
    directoriosGestionados.insert(pathDirectorioInteres);
    systemWatcher->addPath(pathDirectorioInteres);
}

void ServicioGestionSistemaDirectorios::limpiaWatcher() {
    for(QSet<QString>::iterator it_directoriosGestionados = directoriosGestionados.begin(); it_directoriosGestionados != directoriosGestionados.end(); ++it_directoriosGestionados){
        systemWatcher->removePath(*it_directoriosGestionados);
    }

    archivosPorDirectorioGestionado.clear();
    directoriosGestionados.clear();
}
