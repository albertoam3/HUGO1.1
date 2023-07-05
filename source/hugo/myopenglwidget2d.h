#ifndef MYOPENGLWIDGET2D_H
#define MYOPENGLWIDGET2D_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColor>
#include "objetos/objetos.h"
#include <QMouseEvent>
#include "graphics/graphic_objects.h"
#include "graphics/neuron_g.h"
#include <Eigen/Dense>


class myopenglwidget2d : public QOpenGLWidget, public QOpenGLFunctions

{
	
	
private:
    float mouseX,mouseY;
    bool buttonDrawActive;
    std::vector<neuron_g*> neuronG;	
    float scala,scalaTotal{};
    bool _rotation;
    Eigen::Vector3f position;
    Eigen::Matrix4f model_view;
	Eigen::Matrix3f rotation;
	Eigen::Vector3f result;
    float translationX,translationY;
    bool _translation;
    float rotationX,rotationY;
    float ejeXAux{},ejeYAux{};
    bool controlPressed,rPressed,tPressed;
	Q_OBJECT
public:
  myopenglwidget2d(QWidget *parent =nullptr);
  void setNeuronG(neuron_g *neuG);
  void resetList();
  void setDraw(bool a); 
  void select_draw_den(bool a);
  void select_tam_den(bool a);
  void setTree(bool a);
  void setDendograma(bool a);
  void select_grosor_den(bool a);
  void variableGrosor(float a);
  
protected:
    void paintGL() override;
    void resizeGL(int w,int h) override;
    void initializeGL() override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent( QMouseEvent* event_ ) override;
    void mouseMoveEvent( QMouseEvent* event_ ) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    
    
private:
    void transform();
       void rotate(float x,float y,float z);
};

#endif // MYOPENGLWIDGET2D_H
