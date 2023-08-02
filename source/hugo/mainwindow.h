#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <myOpenGLWidget.h>
#include <myOpenGLWidget2D.h>

//Qt
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QRadioButton>

#include <QLineEdit>

#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include <QFileDialog>
#include <QTextEdit>
#include <QDir>
#include <QFileInfo>
#include <QListWidgetItem>


#include "graphics/somaG.h"
#include "graphics/neuronG.h"
#include "graphics/axonG.h"
#include "graphics/dendriteG.h"
#include "baseDatosObjetos.h"

#include <nsol/nsol.h>

#include <map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:

    typedef std::map<QString, neuronG*> mapaNombreFicheroNeurona;
 
    QComboBox *list;
  
    QComboBox* elementosCargados;
 
    myOpenGLWidget *_openGLWidget;
    myOpenGLWidget2D* openGLWidget2d;
    baseDatosObjetos* base;
    mapaNombreFicheroNeurona * mapaBase;
    nsol::NeuronsMap neurons;

    bool loadedNeuron;

    QString path;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectButtons();
    void selecction();

    void openSWCFile( const std::string& fileName );
	void showDirectory(const QString& path);
    void loadData( const std::string& arg1 ,
                   const std::string& arg2 ,
                   const std::string& type);
                   
    void openFile(QListWidgetItem *item, QListWidgetItem *previous);
    void addList(const std::string& st);

public Q_SLOTS:
    void writeText();
    void openSWCFileThroughDialog();
    void loadDirectory();

    void pintar();
    void reset();
    void load();

    void difGrosor();
    void igualGrosor();
    void set_dend();
    void set_nada();
    void set_tree();
    void set_esq();
    void validarTam();
    
private slots:
    void onIgualAngClicked();

    void onTerminalesAngClicked();
    void setCirculos();
    

private:
    Ui::MainWindow *ui;
    void createList();
    void checkBoxStateChanged(int state);
    void initGrosorComboBox();
    void initTamComboBox();
    void resetButtons();

protected:
    QString _lastOpenedFileName;
    QString _lastOpenedDirectory;
};
#endif // MAINWINDOW_H
