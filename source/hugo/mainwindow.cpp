#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    /*Declaración e inicialización de la list con las distintas partes de la neurona y el botón para pintar
    La list es momentanea, pretende ser una list con los objetos cargados
     */
    ui->setupUi(this);
    setWindowTitle("HUGO");

    
    
    
    button_igual_rama = ui->centralwidget->findChild<QGroupBox *>("groupBox_2")->findChild<QRadioButton *>("igual_ramas");
    button_dif_rama = ui->centralwidget->findChild<QGroupBox *>("groupBox_2")->findChild<QRadioButton *>("dif_rama");

    list = ui->list;
    elementosCargados = ui->elemC;
    //Asigno a _openGLWidget la pantalla creada con mainwindow.ui
    _openGLWidget = ui->openGLWidget;
    _openGLWidget->setFocus();

    connect_buttons();

    //Creo cuatro objetos para probar distintas formas de pintar, esto tambien es momentaneo


    base = new base_datos_objetos();

 
    creat_list();

}

MainWindow::~MainWindow() {
    delete ui;
}

//Método para el botón
void MainWindow::connect_buttons() {
    QObject::connect(ui->draw, SIGNAL(clicked()), this, SLOT(pintar()));
    QObject::connect(ui->reset, SIGNAL(clicked()), this, SLOT(reset()));
    QObject::connect(ui->load, SIGNAL(clicked()), this, SLOT(load()));
    QObject::connect(ui->boton2D, SIGNAL(clicked()), this, SLOT(_2D_clicked()));
    QObject::connect(ui->boton3D, SIGNAL(clicked()), this, SLOT(_3D_clicked()));
    QObject::connect(button_igual_rama, SIGNAL(clicked()), this, SLOT(igual_tam()));
    QObject::connect(button_dif_rama, SIGNAL(clicked()), this, SLOT(dif_tam()));
    QObject::connect(ui->setArbol, &QCheckBox::stateChanged, this, &MainWindow::checkBoxStateChanged);

}

//Pongo a true la openGLWidget, para poder pintarla.
void MainWindow::pintar() {
    _openGLWidget->setDraw(true);
}

void MainWindow::reset() {
    _openGLWidget->resetList();
    elementosCargados->clear();
}

void MainWindow::load() {
    this->selecction();
}

//Selecciono el objeto de la list que pinto y se lo mando a qopenGLWidget
void MainWindow::selecction() {
    int index = list->currentIndex();
    if(index<base->getList().size()){
        _openGLWidget->setGraphicsObject(base->get(index));
        elementosCargados->addItem(base->get(index)->getName());
    }
}

void MainWindow::creat_list() {
    for (int i = 0; i < base->getList().size(); i++) {
        list->addItem(base->get(i)->getName());
    }
}

void MainWindow::on_igual_ang_clicked()
{
    _openGLWidget->select_draw_den(false);
}

void MainWindow::on_terminales_ang_clicked()
{
    _openGLWidget->select_draw_den(true);
}

void MainWindow::loadData( const std::string& m_fileName, const std::string& arg2 ,
                           const std::string& type )
{
    nsol::DataSet* m_dataset = new nsol::DataSet( );
    m_dataset->loadNeuronFromFile< nsol::Node ,
            nsol::NeuronMorphologySection ,
            nsol::Dendrite ,
            nsol::Axon ,
            nsol::Soma ,
            nsol::NeuronMorphology ,
            nsol::Neuron >( m_fileName , 1 );

    std::cout << "Fichero leído con éxito\n";
//Ahora mismo añado todo a mi base de datos y borro lo anterior, el objetivo seria añadir todo pero sin borrar lo anterior
    neurons = m_dataset->neurons();

    writeText();
    for (auto& neuronPair : neurons) {
    	 base->add(new neuron_g(neuronPair.second));
         this->addList(std::to_string(neuronPair.first));
    }
}

void MainWindow::writeText(){

    QTextEdit* textEdit = this->centralWidget()->findChild<QTextEdit*>("texto_neurona");

    std::string neuronData = "";

    QString text = "";

    for (auto& neuronPair : neurons) {
        auto gid = neuronPair.first;
        auto &neuron = neuronPair.second;

        // Acceder a los parámetros de la neurona
        auto gidNeuron = neuron->gid();
        auto layer = neuron->layer();
        auto morphoType = neuron->morphologicalType();


        neuronData += "Neurona - GID: " + std::to_string(gidNeuron) + ", Layer: " + std::to_string(layer) +
                      ", Morpho Type: " + std::to_string(morphoType) + "\n";

        // Acceder a las estructuras morfológicas de la neurona
        const auto &soma = neuron->morphology()->soma();
        const auto &axon = neuron->morphology()->axon();
        const auto &dendrites = neuron->morphology()->dendrites();


        neuronData += "Soma Radius: " + std::to_string(soma->meanRadius()) + "\n";
       
        neuronData += "Axon Branch Number: " + std::to_string(axon->numBranches()) + "\n";

        for (auto &dendrite: *dendrites) {
           neuronData += "Dendrite Branch Number: " + std::to_string(dendrite->numBranches()) + "\n";
        }

    }
    text = QString::fromStdString(neuronData);

    textEdit->setText(text);

}

void MainWindow::openSWCFile( const std::string& fileName )
{
    loadData( fileName , std::string( ) , "swc");


}

void MainWindow::openSWCFileThroughDialog()
{
    QString path = QFileDialog::getOpenFileName(
            this, tr( "Open Swc File" ), _lastOpenedFileName,
            tr( "swc ( *.swc);; All files (*)" ), nullptr,
            QFileDialog::DontUseNativeDialog );

    if ( path != QString( "" ))
    {
        std::string fileName = path.toStdString( );
        openSWCFile( fileName );
    }
}
void MainWindow::addList(const std::string& st){
    QString qstr = QString::fromStdString(st);
    list->addItem(qstr);
}

void MainWindow::_2D_clicked(){
	_openGLWidget->setDimension(false);
}


void MainWindow::_3D_clicked(){
	_openGLWidget->setDimension(true);

}

void MainWindow::igual_tam(){
	_openGLWidget->select_tam_den(false);
}

void MainWindow::dif_tam(){
 	_openGLWidget->select_tam_den(true);
}

void MainWindow::checkBoxStateChanged(int state) {
    bool tree = (state == Qt::Checked) ? true : false;
    _openGLWidget->setTree(tree);
 
}






