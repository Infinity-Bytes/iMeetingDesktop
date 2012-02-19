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
    explicit ControladorListadoAvance(QTreeWidget * arbol, QObject *parent = 0);
    
signals:
    
public slots:
    void gestionaArchivo(QString archivo);

private:
    void cargaDefinicion(QString archivo);
    void cargarElementosTrabajados(QString archivo);

    QTreeWidgetItem * procesaPersonal(QVariantMap persona, QSet<QTreeWidgetItem *> padres);

    enum PosicionInfoColumnas {
        NOMBRE = 0,
        ACUMULADOR = 1,
        DERIVADOS = 2
    };

    QMap<QString, QSet<QTreeWidgetItem *> > itemsPorIdentificador;
    QMap<QString, QMap<QString, QString> > propiedadesPorIdentificador;
    QTreeWidget * arbol;
};

#endif // CONTROLADORLISTADOAVANCE_H
