#ifndef SERVICIOGESTIONSISTEMADIRECTORIOS_H
#define SERVICIOGESTIONSISTEMADIRECTORIOS_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QSet>
#include <QMap>
#include <QDir>

class ServicioGestionSistemaDirectorios : public QObject
{
    Q_OBJECT
public:
    explicit ServicioGestionSistemaDirectorios(QObject *parent = 0);

public slots:
    void estableceDirectorioBase(QString directorioBase);
    
signals:
    void gestionaArchivo(QString archivo);
    
private slots:
    void archivoActualizado(QString directorioActualizado);
    void directorioActualizado(QString directorioActualizado);

private:
    QFileSystemWatcher * systemWatcher;

    QSet<QString> directoriosGestionados;
    QMap<QString, QSet<QString> > archivosPorDirectorioGestionado;

    void agregaSegunDirectorio(QDir directorioInteres);
    void limpiaWatcher();
    void registraArchivo(QString archivoInteres, QSet<QString> *conjuntoRegistrado);
};

#endif // SERVICIOGESTIONSISTEMADIRECTORIOS_H
