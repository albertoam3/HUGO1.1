#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <vector>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    /*Declaración e inicialización de la list con las distintas partes de la neurona y el botón para pintar
    La list es momentanea, pretende ser una list con los objetos cargados
     */
    ui->setupUi(this);
    setWindowTitle("HUGO");

    ui->list;
    elementosCargados = ui->elemC;
    //Asigno a _openGLWidget la pantalla creada con mainwindow.ui
    _openGLWidget = ui->openGLWidget;
    _openGLWidget->setFocus();
   
    openGLWidget2d= ui->openGLWidget2D;
	openGLWidget2d->setFocus();
    openGLWidget2d->otherWidget(_openGLWidget);
    connectButtons();

    //Creo cuatro objetos para probar distintas formas de pintar, esto tambien es momentaneo


    base = new baseDatosObjetos();

    mapaBase = new mapaNombreFicheroNeurona;

	initGrosorComboBox();
    initTamComboBox();
    createList();
    
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	
	auto temp = new QListWidgetItem("Cargue un directorio");
	ui->listWidget->addItem(temp);
	
	QObject::connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::openFile);

}

MainWindow::~MainWindow() {
    delete ui;
}

//Método para el botón
void MainWindow::connectButtons() {
    QObject::connect(ui->draw, SIGNAL(clicked()), this, SLOT(pintar()));
    QObject::connect(ui->reset, SIGNAL(clicked()), this, SLOT(reset()));
    QObject::connect(ui->load, SIGNAL(clicked()), this, SLOT(load()));
    QObject::connect(ui->validar_tam_2, SIGNAL(clicked()), this, SLOT(validarTam()));

    QObject::connect(ui->setDendograma,SIGNAL(clicked()),this,SLOT(set_dend()));
    QObject::connect(ui->setNada,SIGNAL(clicked()),this,SLOT(set_nada()));
    QObject::connect(ui->setArbol, SIGNAL(clicked()), this, SLOT(set_tree()));

    QObject::connect(ui->igualGrosor, SIGNAL(clicked()), this, SLOT(igualGrosor()));
    QObject::connect(ui->difGrosor, SIGNAL(clicked()), this, SLOT(difGrosor()));
    
    

}

//Pongo a true la openGLWidget, para poder pintarla.
void MainWindow::pintar() {
    _openGLWidget->setDraw(true);
    openGLWidget2d->setDraw(true);
}

void MainWindow::reset() {
    _openGLWidget->resetList();
    openGLWidget2d->resetList();
    elementosCargados->clear();
}

void MainWindow::load() {
    this->selecction();
}

//Selecciono el objeto de la list que pinto y se lo mando a qopenGLWidget
void MainWindow::selecction() {
    int index = ui->list->currentIndex();
    if(index<base->getList().size()){
        _openGLWidget->setGraphicsObject(base->get(index));
        openGLWidget2d->setNeuronGraphic(base->get(index));
        elementosCargados->addItem(base->get(index)->getName());
    }
}

void MainWindow::createList() {
    for (int i = 0; i < base->getList().size(); i++) {
        ui->list->addItem(base->get(i)->getName());
    }
}

void MainWindow::onIgualAngClicked()
{
    openGLWidget2d->select_draw_den(false);
}

void MainWindow::onTerminalesAngClicked()
{
    openGLWidget2d->select_draw_den(true);
}

void MainWindow::loadData(const std::string& m_fileName, const std::string& arg2, const std::string& type)
{
    nsol::DataSet* m_dataset = new nsol::DataSet();

    try {
        m_dataset->loadNeuronFromFile<nsol::Node,
                nsol::NeuronMorphologySection,
                nsol::Dendrite,
                nsol::Axon,
                nsol::Soma,
                nsol::NeuronMorphology,
                nsol::Neuron>(m_fileName, 1);

        std::cout << "Fichero leído con éxito\n";
        neurons = m_dataset->neurons();
        writeText();
        for (auto& neuronPair : neurons) {
            base->add(new neuronG(neuronPair.second));
            mapaBase->emplace(m_fileName, new neuronG(neuronPair.second));
            this->addList(std::to_string(neuronPair.first));
        }
    } catch (const std::exception& e) {
        QTextEdit* textEdit = this->centralWidget()->findChild<QTextEdit*>("texto_neurona");
        std::cerr << "Error al cargar el fichero: " << e.what() << std::endl;
        std::cout << "Fichero no disponible para lectura\n";

        std::stringstream errorMessage;
        errorMessage << "Error al cargar la neurona. Ref: \n" << e.what();
        textEdit->setText(QString::fromStdString(errorMessage.str()));
    }

    // Si llegamos a este punto, independientemente de si hubo una excepción o no,
    // ya no necesitamos el objeto DataSet, así que liberamos la memoria
    delete m_dataset;
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
    std::cout << "Objetos actuales en el mapa:" << mapaBase->size() << "\n";
    text = QString::fromStdString(neuronData);

    textEdit->setText(text);

}

void MainWindow::openSWCFile( const std::string& fileName )
{
    loadData( fileName , std::string( ) , "swc");


}

void MainWindow::loadDirectory(){
		QString directoryPath = QFileDialog::getExistingDirectory(
            this, tr( "Selecciona un directorio" ), _lastOpenedDirectory,
        QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);

		if ( directoryPath != QString( "" ))
		{
			this->path = directoryPath;
			showDirectory( directoryPath);
		}
	}
	
void MainWindow::showDirectory(const QString& path){
	QStringList fileFilters; 
	QDir directory(path);
	fileFilters << "*.swc";
	directory.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	directory.setNameFilters(fileFilters);
	
	if (directory.exists()) {
    
		QFileInfoList fileList = directory.entryInfoList();
		
		ui->listWidget->takeItem(0);

		for (const QFileInfo &fileInfo : fileList) {
			ui->listWidget->addItem(fileInfo.fileName());
		}
	} 
}

void MainWindow::openFile(QListWidgetItem *item) {
    QString fileName = ui->listWidget->item(ui->listWidget->row(item))->text();
    QString folderPath = this->path;
    std::string folderPathString = folderPath.toStdString();
    std::string fileNameString = fileName.toStdString();
    openSWCFile(folderPathString + "/" + fileNameString);
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
    ui->list->addItem(qstr);
}




void MainWindow::validarTam(){
 	openGLWidget2d->select_tam_den(true);
    openGLWidget2d->variableTam(ui->tamanoComboBox->currentIndex());
}

void MainWindow::checkBoxStateChanged(int state) {
    bool tree = (state == Qt::Checked) ? true : false;
    openGLWidget2d->setTree(tree);
 
}


void MainWindow::igualGrosor(){
	openGLWidget2d->select_grosor_den(false);
	
	
}

void MainWindow::difGrosor(){
	 openGLWidget2d->select_grosor_den(true);
	 openGLWidget2d->variableGrosor(ui->grosorComboBox->currentIndex());
	
}

void MainWindow::initGrosorComboBox(){
	ui->grosorComboBox->addItem("Tamaño");
	ui->grosorComboBox->addItem("Volumen");
	ui->grosorComboBox->addItem("Nodos terminales");
	
	
}

void MainWindow::initTamComboBox(){
    ui->tamanoComboBox->addItem("Tamaño real");
    ui->tamanoComboBox->addItem("distancia punto punto");
    ui->tamanoComboBox->addItem("unitario");
}

void MainWindow::set_dend() {
    openGLWidget2d->setDendograma(true);
    openGLWidget2d->setTree(false);
}

void MainWindow::set_nada(){
    openGLWidget2d->setDendograma(false);
    openGLWidget2d->setTree(false);


}

void MainWindow::set_tree() {
    openGLWidget2d->setDendograma(false);
    openGLWidget2d->setTree(true);
}



