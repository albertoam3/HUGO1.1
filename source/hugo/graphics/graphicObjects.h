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

class graphicObjects{
protected:
    bool selected;
    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;

    float displacementX;
    float displacementY;
    float displacementZ;

    QString name;
    float initX;
    float initY;
    float initZ;
    bool angleXTam;
    bool neuritesTam;
    bool neuritesGros;
    bool dimension;

    float scala;
    
    bool tree;
    bool dendograma;
    bool esquema;
    
    float variableGros;
    
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
            displacementX= x - initX;
            displacementY= y - initY;
            displacementZ= z - initZ;

    }

    //Comprueba si el objeto esta selected
    virtual bool select(QOpenGLWidget* windowPaint, float x, float y,float z)=0;

    //Cuando pintamos el objeto desde 0, quita el boton selected en caso de que estuviera.
    virtual bool resetSelect()=0;
     void coordInitials(float x, float y){
         initX=x;
         initY=y;
    }

    const QString &getName() const {
        return name;
    }

    void setName(const QString &name_) {
        graphicObjects::name = name_;
    }

    virtual bool isSelected()=0 ;

    bool coord_include(float x,float y){
        coordinates();
        if (x > minX - 0.05 && x < maxX + 0.05 && y > minY - 0.05 && y < maxY + 0.05){
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
    
    void setNeuritesGrosor(bool grosor){
        neuritesGros=grosor;
	}
    
    void setDimension(bool a){
   	dimension=a;
    }
    
    void setScala(float scalaX){
    	scala=scalaX;
    }
    void setNeuritesTam(bool c){
        neuritesTam=c;
    }
    

    void setNeuritesVariableGrosor(float a){
        variableGros=a;
		
	}
    
    
    virtual float getTam()=0;
    
    
	void setTree(bool a){
		tree=a;
	}

    void setEsquema(bool a){
        esquema=a;
    }

    void setDendograma(bool a){
        dendograma=a;
    }
};
#endif //HUGO_GRAPHIC_OBJECTS_H

