#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <myopenglwidget.h>

//Qt
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>

#include <QLineEdit>

#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include <QFileDialog>
#include <QTextEdit>

#include "objetos/axon.h"
#include "objetos/dendrites.h"
#include "objetos/neuron.h"
#include "objetos/soma.h"
#include "graphics/graphic_neuron.h"
#include "graphics/graphic_axon.h"
#include "graphics/graphic_soma.h"
#include "graphics/graphic_dendrite.h"
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
    QPushButton *button_draw;
    QPushButton *button_reset;
    QPushButton *button_load;
    QComboBox *list;
  
    QComboBox* elementosCargados;

    QPushButton * button_3D;
    QPushButton * button_2D;

    

    myopenglwidget *_openGLWidget;
    axon* ax;
    dendrites* den;
    neuron* neu;
    soma* som;

    graphic_neuron* gneu;
    graphic_axon* gax;
    graphic_soma* gsom;
    graphic_dendrite* gden;

    base_datos_objetos* base;

    nsol::NeuronsMap neurons;



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connect_buttons();
    void selecction();

    void openSWCFile( const std::string& fileName );

    void loadData( const std::string& arg1 ,
                   const std::string& arg2 ,
                   const std::string& type);

    void addList(const std::string& st);

public Q_SLOTS:
    void writeText();
    void openSWCFileThroughDialog();

    void pintar();
    void reset();
    void load();
    
    void _2D_clicked();
    void _3D_clicked();
private slots:
    void on_igual_ang_clicked();

    void on_terminales_ang_clicked();
    

private:
    Ui::MainWindow *ui;
    void creat_list();
protected:
    QString _lastOpenedFileName;
};
#endif // MAINWINDOW_H
