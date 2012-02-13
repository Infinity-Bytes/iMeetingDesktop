#include "VentanaPrincipal.h"
#include "ui_VentanaPrincipal.h"

#include <QDebug>
#include <QFileDialog>

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);
    this->connect(ui->actionDirectorio_base, SIGNAL(triggered()), this, SLOT(seleccionarDirectorioBase()));


    QTreeWidgetItem * itemSuperior1 = new QTreeWidgetItem(QStringList() << "Fer" << "2" << "1");
    itemSuperior1->addChild(new QTreeWidgetItem(QStringList() << "Raquel" << "2" << "1"));

    // TODO Remover
    ui->listadoAvance->setColumnCount(3);
    ui->listadoAvance->setHeaderLabels(QStringList() << "Nombre" << "Total" << "Procesado");

    ui->listadoAvance->addTopLevelItem(itemSuperior1);
    ui->listadoAvance->addTopLevelItem(new QTreeWidgetItem(QStringList() << "Otro" << "3" << "3"));
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
