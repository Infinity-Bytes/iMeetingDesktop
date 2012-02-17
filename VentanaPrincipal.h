#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include "Servicios/ServicioGestionSistemaDirectorios.h"
#include "ControladoresVista/ControladorListadoAvance.h"

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit VentanaPrincipal(QWidget *parent = 0);
    ~VentanaPrincipal();
    
public slots:
    void seleccionarDirectorioBase();

private:
    Ui::VentanaPrincipal *ui;
    ServicioGestionSistemaDirectorios servicioGestionSistemaDirectorios;
    ControladorListadoAvance * controladorListadoAvance;
};

#endif // VENTANAPRINCIPAL_H
