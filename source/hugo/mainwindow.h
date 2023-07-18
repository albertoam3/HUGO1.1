#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <myopenglwidget.h>
#include <myopenglwidget2d.h>

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
    myopenglwidget2d* openGLWidget2d;
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

    void dif_grosor();
    void igual_grosor();
    void set_dend();
    void set_nada();
    void set_tree();
    void validar_tam();
    
private slots:
    void on_igual_ang_clicked();

    void on_terminales_ang_clicked();
    

private:
    Ui::MainWindow *ui;
    void creat_list();
    void checkBoxStateChanged(int state);
    void initGrosorComboBox();
    void initTamComboBox();

protected:
    QString _lastOpenedFileName;
    QString _lastOpenedDirectory;
};
#endif // MAINWINDOW_H
