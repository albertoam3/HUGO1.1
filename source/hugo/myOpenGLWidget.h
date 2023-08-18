#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColor>

#include <QMouseEvent>
#include "graphics/graphicObjects.h"
#include "graphics/neuronG.h"
#include <Eigen/Dense>


class myOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions

{
    Q_OBJECT
private:
    float mouseX,mouseY;
    bool buttonDrawActive;
    std::vector<neuronG*> gobject;


    float translationX,translationY;
    float ejeXAux{},ejeYAux{};
    float scala,scalaTotal{};
    bool _rotation;
    bool _translation;
    bool circle;
    

    Eigen::Vector3f position;
    Eigen::Matrix3f rotation;
    Eigen::Matrix2f rotation2D;

    Eigen::Matrix4f model_view;
    Eigen::Vector3f result;


public:



    myOpenGLWidget(QWidget *parent =nullptr);
    void setDraw(bool a);
    void setGraphicsObject(neuronG *gobj);
    void resetList();
    void setDrawCircle(bool draw);


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
    void drawCirculoAux(float modulo, bool activo);
};

#endif // MYOPENGLWIDGET_H
