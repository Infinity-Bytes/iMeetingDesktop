#ifndef CONTROLADORLISTADOAVANCE_H
#define CONTROLADORLISTADOAVANCE_H

#include <QObject>

class ControladorListadoAvance : public QObject
{
    Q_OBJECT
public:
    explicit ControladorListadoAvance(QObject *parent = 0);
    
signals:
    
public slots:
    void gestionaArchivo(QString archivo);

private:
    void cargaDefinicion(QString archivo);
};

#endif // CONTROLADORLISTADOAVANCE_H
