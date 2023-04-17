#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColor>
#include "objetos/objetos.h"
#include <QMouseEvent>
#include "graphics/graphic_neuron.h"
#include "graphics/graphic_objects.h"
#include <Eigen/Dense>


class myopenglwidget : public QOpenGLWidget, public QOpenGLFunctions

{
    Q_OBJECT
private:
    float mouseX,mouseY;
    bool buttonDrawActive;
    objetos *objet_paint;
    std::vector<graphic_objects*> gobject;


    float translationX,translationY;
    float ejeXAux{},ejeYAux{};
    float scala,scalaTotal{};
    float rotationX,rotationY;
    bool _rotation;
    bool _translation;

    Eigen::Vector3f position;
    Eigen::Matrix3f rotation;

    Eigen::Matrix4f model_view;
    Eigen::Vector3f result;


public:



    myopenglwidget(QWidget *parent =nullptr);
    void setDraw(bool a);
    void setGraphicsObject(graphic_objects *gobj);
    void resetList();
    void select_draw_den(bool a);

protected:

    void paintGL() override;
    void resizeGL(int w,int h) override;
    void initializeGL() override;
     void mousePressEvent( QMouseEvent* event_ ) override;
     void mouseMoveEvent( QMouseEvent* event_ ) override;
     void keyPressEvent(QKeyEvent* event_) override;
    //int calculatePosition(int i);
    void positionDraws();
private:
    void rotate(float x,float y,float z);
    void transform();

};

#endif // MYOPENGLWIDGET_H
