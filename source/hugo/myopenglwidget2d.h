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
public:
  myopenglwidget2d(QWidget *parent =nullptr);
  
  
protected:
    void paintGL() override;
    void resizeGL(int w,int h) override;
    void initializeGL() override;
};

#endif // MYOPENGLWIDGET2D_H
