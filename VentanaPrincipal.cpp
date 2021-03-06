#include "VentanaPrincipal.h"
#include "ui_VentanaPrincipal.h"

#include <QDebug>
#include <QFileDialog>

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);
    ui->listadoAvance->setColumnCount(3);
    ui->listadoAvance->setHeaderLabels(QStringList() << "Nombre" << "Acumulador" << "Derivados");
    controladorListadoAvance = new ControladorListadoAvance(ui->listadoAvance, this);

    this->connect(ui->actionDirectorio_base, SIGNAL(triggered()), this, SLOT(seleccionarDirectorioBase()));
    this->connect(&servicioGestionSistemaDirectorios, SIGNAL(gestionaArchivo(QString)), controladorListadoAvance, SLOT(gestionaArchivo(QString)));
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::seleccionarDirectorioBase() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    if(dialog.exec()) {
        QStringList elementosSeleccionados = dialog.selectedFiles();
        for(QStringList::iterator it_elementosSeleccionados = elementosSeleccionados.begin(); it_elementosSeleccionados != elementosSeleccionados.end(); ++it_elementosSeleccionados) {
            QString elementoInteres = *it_elementosSeleccionados;
            qDebug() << QString("Gestionar directorio") << elementoInteres;
            servicioGestionSistemaDirectorios.estableceDirectorioBase(elementoInteres);
        }
    }
}
