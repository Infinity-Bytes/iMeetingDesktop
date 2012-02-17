#ifndef CONTROLADORLISTADOAVANCE_H
#define CONTROLADORLISTADOAVANCE_H

#include <QObject>
#include <QVariant>
#include <QSet>
#include <QTreeWidgetItem>

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
    QTreeWidgetItem * procesaPersonal(QVariantMap persona, QSet<QTreeWidgetItem *> padres);

    enum PosicionInfoColumnas {
        ACUMULADOR = 1,
        DERIVADOS = 2,
        NUM_COLUMNAS = 3
    };
};

#endif // CONTROLADORLISTADOAVANCE_H
