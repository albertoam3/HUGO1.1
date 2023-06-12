#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColor>
#include "objetos/objetos.h"
#include <QMouseEvent>
#include "graphics/graphic_objects.h"
#include "graphics/neuron_g.h"
#include <Eigen/Dense>


class myopenglwidget : public QOpenGLWidget, public QOpenGLFunctions

{
    Q_OBJECT
private:
    float mouseX,mouseY;
    bool buttonDrawActive;
    std::vector<neuron_g*> gobject;


    float translationX,translationY;
    float ejeXAux{},ejeYAux{};
    float scala,scalaTotal{};
    float rotationX,rotationY;
    bool _rotation;
    bool _translation;
    

    Eigen::Vector3f position;
    Eigen::Matrix3f rotation;
    Eigen::Matrix2f rotation2D;

    Eigen::Matrix4f model_view;
    Eigen::Vector3f result;


public:



    myopenglwidget(QWidget *parent =nullptr);
    void setDraw(bool a);
    void setGraphicsObject(neuron_g *gobj);
    void resetList();


protected:

    void paintGL() override;
    void resizeGL(int w,int h) override;
    void initializeGL() override;
    void mousePressEvent( QMouseEvent* event_ ) override;
    void mouseMoveEvent( QMouseEvent* event_ ) override;
    void wheelEvent(QWheelEvent *event) override;
     
    //int calculatePosition(int i);
    void positionDraws();
    
    
private:
    void rotate(float x,float y,float z);
    
    void transform();

};

#endif // MYOPENGLWIDGET_H
