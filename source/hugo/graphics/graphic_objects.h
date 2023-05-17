//
// Created by alberto on 27/02/23.
//

#ifndef HUGO_GRAPHIC_OBJECTS_H
#define HUGO_GRAPHIC_OBJECTS_H

#include <QOpenGLWidget>
#include <iostream>
#include "cmath"
#include <QToolTip>
#include <QPoint>

class graphic_objects{
protected:
    bool selected;
    float min_X;
    float max_X;
    float min_Y;
    float max_Y;
    float min_Z;
    float max_Z;

    float displacementX;
    float displacementY;
    float displacementZ;

    QString name;
    float init_x;
    float init_y;
    float init_z;
    bool angleXTam;
    bool neurites_tam;
    bool dimension;
    bool radiusView;
    
    float scala;
public:

/*Metodo que esta definido en cada clase hijo, quieres pintaran lo que necesiten en la pantalla openGLWidget
con un desplazamiento de X y otro desplazamiento de Y*/
    virtual void draw(QOpenGLWidget* windowPaint)=0;

    //Dibujar el caudrado que la select.
    virtual void drawSelc(QOpenGLWidget* windowPaint)=0;

    //Devuelve las coordinates en las que se encuentra el objeto
    virtual void coordinates()=0;

    //Coordenadas que se desplaza el objeto
    void displacement(float x, float y,float z){
            displacementX= x - init_x;
            displacementY= y - init_y;
            displacementZ= z-init_z;

    }

    //Comprueba si el objeto esta selected
    virtual bool select(QOpenGLWidget* windowPaint, float x, float y,float z)=0;

    //Cuando pintamos el objeto desde 0, quita el boton selected en caso de que estuviera.
    virtual bool resetSelect()=0;
     void coordInitials(float x, float y){
        init_x=x;
        init_y=y;
    }

    const QString &getName() const {
        return name;
    }

    void setName(const QString &name_) {
        graphic_objects::name = name_;
    }

    virtual bool isSelected()=0 ;

    bool coord_include(float x,float y){
        coordinates();
        if (x > min_X -0.05 && x < max_X +0.05 && y > min_Y -0.05 && y < max_Y + 0.05){
            return true;
        }
        return false;
    }
     void setDisplacements(float x, float y){
         displacementX=x;
         displacementY=y;
    }
    void setAngleXTam(bool _angleXTam) {
        angleXTam = _angleXTam;
    }
    void seeToolTip(QString texto,QOpenGLWidget *windowPaint){
        QToolTip::showText(QCursor::pos(), texto, windowPaint, QRect(), 5000);
    }
    void setDimension(bool a){
   	dimension=a;
    }
    void setRadiusView(bool a){
   	radiusView=a;
    }
    
    void setScala(float scalaX){
    	scala=scalaX;
    }
    void setNeuritesTam(bool c){
    	neurites_tam=c;
    }
    
    virtual float getTam()=0;
};
#endif //HUGO_GRAPHIC_OBJECTS_H

