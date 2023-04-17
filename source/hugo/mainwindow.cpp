#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    /*Declaración e inicialización de la list con las distintas partes de la neurona y el botón para pintar
    La list es momentanea, pretende ser una list con los objetos cargados
     */
    ui->setupUi(this);
    setWindowTitle("HUGO");
    button_draw= ui->centralwidget->findChild<QPushButton*>("draw");
    button_reset= ui->centralwidget->findChild<QPushButton*>("reset");
    button_load=ui->centralwidget->findChild<QPushButton*>("load");

    list=ui->centralwidget->findChild<QComboBox*>("list");
    elementosCargados=ui->centralwidget->findChild<QComboBox*>("elemC");
    //Asigno a _openGLWidget la pantalla creada con mainwindow.ui
    _openGLWidget=ui->centralwidget->findChild<myopenglwidget*>("openGLWidget");
    _openGLWidget->setFocus();

    connect_buttons();

    //Creo cuatro objetos para probar distintas formas de pintar, esto tambien es momentaneo


    base=new base_datos_objetos();

    ax=new axon(0.0f,0.5f,0.0f,0.0f);
    den=new dendrites(-0.2f, -0.2f, 0.2f,0.2f);
    dendrites* den2=new dendrites(-0.2f,0.2f,-0.2f,0.2f);
    dendrites* den3=new dendrites(0.0f,0.0f,0.0f,0.3f);
    dendrites* den4=new dendrites(0.0f,0.0f,0.0f,0.5f);

    std::vector<dendrites> dends;
    dends.push_back(*den);
    dends.push_back(*den2);
    dends.push_back(*den3);
    dends.push_back(*den4);

    som= new soma(0.2f);
    neu= new neuron(som,ax,dends);


    gneu=new graphic_neuron(neu);
    gax=new graphic_axon(ax);
    gsom=new graphic_soma(som);
    gden=new graphic_dendrite(den);

    base->add(gneu);
    base->add(gax);
    base->add(gsom);
    base->add(gden);

    creat_list();

}

MainWindow::~MainWindow()
{
    delete ui;
}
//Método para el botón
void MainWindow::connect_buttons() {
    QObject::connect(button_draw, SIGNAL(clicked()), this, SLOT(pintar()));
    QObject::connect(button_reset, SIGNAL(clicked()), this, SLOT(reset()));
    QObject::connect(button_load, SIGNAL(clicked()), this, SLOT(load()));
}
//Pongo a true la openGLWidget, para poder pintarla.
void MainWindow::pintar(){
    _openGLWidget->setDraw(true);
}

void MainWindow::reset(){
    _openGLWidget->resetList();
    elementosCargados->clear();
}
void MainWindow::load(){
    this->selecction();
}

//Selecciono el objeto de la list que pinto y se lo mando a qopenGLWidget
void MainWindow::selecction() {
    int index=list->currentIndex();
    _openGLWidget->setGraphicsObject(base->get(index));
    elementosCargados->addItem(base->get(index)->getName());

}

void MainWindow::creat_list() {
    for(int i=0;i<base->getList().size();i++){
        list->addItem(base->get(i)->getName());
    }
}

void MainWindow::on_igual_clicked()
{
    _openGLWidget->select_draw_den(false);
}

void MainWindow::on_terminales_clicked()
{
    _openGLWidget->select_draw_den(true);
}
