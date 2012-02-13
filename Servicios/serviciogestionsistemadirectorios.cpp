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
    qDebug() << QString("Archivo Actualizado:") << directorioActualizado;
}

void ServicioGestionSistemaDirectorios::directorioActualizado(QString directorioActualizado) {
    qDebug() << QString("Directorio Actualizado:") << directorioActualizado;

    QDir directorioInteres(directorioActualizado);

    // Registrar archivos nuevos
    QSet<QString> archivosRegistrados = archivosPorDirectorioGestionado[directorioActualizado];
    QSet<QString> listaArchivosEnDirectorio = QSet<QString>::fromList(directorioInteres.entryList(QDir::Files));

    QSet<QString> listaArchivosNuevos = listaArchivosEnDirectorio.subtract(archivosRegistrados);
    for(QSet<QString>::iterator it_listaArchivosNuevos = listaArchivosNuevos.begin(); it_listaArchivosNuevos != listaArchivosNuevos.end(); ++it_listaArchivosNuevos) {
        this->registraArchivo(*it_listaArchivosNuevos, directorioInteres, &archivosRegistrados);
    }
    archivosPorDirectorioGestionado[directorioActualizado] = archivosRegistrados;

    // Registrar directorios nuevos
    QSet<QString> listaDirectoriosEnDirectorio = QSet<QString>::fromList(directorioInteres.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot | QDir::NoDotAndDotDot));
    QSet<QString> listaDirectoriosNuevos = listaDirectoriosEnDirectorio.subtract(directoriosGestionados);
    for(QSet<QString>::iterator it_listaDirectoriosNuevos = listaDirectoriosNuevos.begin(); it_listaDirectoriosNuevos != listaDirectoriosNuevos.end(); ++it_listaDirectoriosNuevos) {
        this->agregaSegunDirectorio( directorioInteres.absoluteFilePath(*it_listaDirectoriosNuevos));
    }
}

void ServicioGestionSistemaDirectorios::agregaSegunDirectorio(QDir directorioInteres) {
    QString pathDirectorioInteres = directorioInteres.path();
    qDebug() << QString("agregaSegunDirectorio: ") <<  pathDirectorioInteres;

    // Agregar Archivos y generar notificacion de gestion
    QSet<QString> archivosInteres = archivosPorDirectorioGestionado[pathDirectorioInteres];

    QStringList listaArchivos = directorioInteres.entryList(QDir::Files);
    for(QStringList::iterator it_listaArchivos = listaArchivos.begin(); it_listaArchivos != listaArchivos.end(); ++it_listaArchivos) {
        this->registraArchivo(*it_listaArchivos, directorioInteres, &archivosInteres);
    }

    archivosPorDirectorioGestionado[pathDirectorioInteres] = archivosInteres;

    // Comportamiento recursivo para agregado de directorios
    QStringList listaDirectorios = directorioInteres.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot | QDir::NoDotAndDotDot);
    for(QStringList::iterator it_listaDirectorios = listaDirectorios .begin(); it_listaDirectorios != listaDirectorios .end(); ++it_listaDirectorios) {
        this->agregaSegunDirectorio(directorioInteres.absoluteFilePath(*it_listaDirectorios));
    }

    // Agregar directorio al Watcher
    if(!directoriosGestionados.contains(pathDirectorioInteres)) {
        directoriosGestionados.insert(pathDirectorioInteres);

        systemWatcher->addPath(pathDirectorioInteres);
    }
}

void ServicioGestionSistemaDirectorios::registraArchivo(QString archivoInteres, QDir directorio, QSet<QString> *conjuntoRegistrado) {
    if (!conjuntoRegistrado->contains(archivoInteres)) {
        conjuntoRegistrado->insert(archivoInteres);

        QString pathArchivo = directorio.absoluteFilePath(archivoInteres);
        qDebug() << QString("Registra nuevo archivo: ") << pathArchivo;

        emit gestionaArchivo(pathArchivo);
    }
}

void ServicioGestionSistemaDirectorios::limpiaWatcher() {
    for(QSet<QString>::iterator it_directoriosGestionados = directoriosGestionados.begin(); it_directoriosGestionados != directoriosGestionados.end(); ++it_directoriosGestionados){
        systemWatcher->removePath(*it_directoriosGestionados);
    }

    archivosPorDirectorioGestionado.clear();
    directoriosGestionados.clear();
}
