#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <myopenglwidget.h>

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

#include "objetos/axon.h"
#include "objetos/dendrites.h"
#include "objetos/neuron.h"
#include "objetos/soma.h"
#include "graphics/soma_g.h"
#include "graphics/neuron_g.h"
#include "graphics/axon_g.h"
#include "graphics/dendrite_g.h"
#include "base_datos_objetos.h"

#include <nsol/nsol.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
 
    QComboBox *list;
  
    QComboBox* elementosCargados;
 
    myopenglwidget *_openGLWidget;
    axon* ax;
    dendrites* den;
    neuron* neu;
    soma* som;
    base_datos_objetos* base;
    nsol::NeuronsMap neurons;

    QString path;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connect_buttons();
    void selecction();

    void openSWCFile( const std::string& fileName );
	void showDirectory(const QString& path);
    void loadData( const std::string& arg1 ,
                   const std::string& arg2 ,
                   const std::string& type);
                   
    void openFile(QListWidgetItem *item);
    void addList(const std::string& st);

public Q_SLOTS:
    void writeText();
    void openSWCFileThroughDialog();
    void loadDirectory();

    void pintar();
    void reset();
    void load();
    
    void _2D_clicked();
    void _3D_clicked();
    
    void igual_tam();
    void dif_tam();
    void dif_grosor();
    void igual_grosor();
    
private slots:
    void on_igual_ang_clicked();

    void on_terminales_ang_clicked();
    

private:
    Ui::MainWindow *ui;
    void creat_list();
    void checkBoxStateChanged(int state);
    void initGrosorComboBox();
protected:
    QString _lastOpenedFileName;
    QString _lastOpenedDirectory;
};
#endif // MAINWINDOW_H
