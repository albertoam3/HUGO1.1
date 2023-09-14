#ifndef MYOPENGLWIDGET2D_H
#define MYOPENGLWIDGET2D_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColor>
#include <QPainter>

#include <QMouseEvent>
#include "graphics/graphicObjects.h"
#include "graphics/neuronG.h"
#include <Eigen/Dense>
#include "myOpenGLWidget.h"
#include "graphics/VarPosDendritas.h"


class myOpenGLWidget2D : public QOpenGLWidget, public QOpenGLFunctions

{
	
	
private:
    float mouseX,mouseY;
    bool buttonDrawActive;
    std::vector<neuronG*> neuronGraphic;
    float scala,scalaTotal{};
    bool _rotation;
    Eigen::Vector3f position;
    Eigen::Matrix4f model_view;
	Eigen::Matrix3f rotation;
	Eigen::Vector3f result;
    float translationX,translationY;
    float ejeXAux{},ejeYAux{};
    bool controlPressed,rPressed,tPressed;
    myOpenGLWidget *mogw;
    bool circle;
	Q_OBJECT
public:
  myOpenGLWidget2D(QWidget *parent =nullptr);
  void setNeuronGraphic(neuronG *neuG);
  void resetList();
  void setDraw(bool a); 
  void select_draw_den(bool a);
  void select_tam_den(bool a);
  void setTree(bool a);
  void setDendograma(bool a);
  void setEsquema(bool a);
  void select_grosor_den(bool a);
  void variableGrosor(float a);
  void variableTam(float a);

  void otherWidget(myOpenGLWidget *mogw);

  void setDrawCircle(bool draw);

  void saveOpenGLWidget2DToPNG(const QString &filename);

  void setPosDendrita(VarPosDendritas vpd);

    const std::vector<neuronG *> &getNeuronGraphic() const;

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
    void drawCirculoAux(float modulo, bool activo);

};

#endif // MYOPENGLWIDGET2D_H
