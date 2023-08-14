//
// Created by alberto on 30/04/23.
//

#ifndef HUGO_NEURON_G_H
#define HUGO_NEURON_G_H


#include <QOpenGLWidget>
#include "graphicObjects.h"
#include <nsol/nsol.h>
#include "somaG.h"
#include "axonG.h"
#include "dendriteG.h"
#include "sectionH.h"

#include "vector"
#include "cmath"

class neuronG : public graphicObjects{
private:
    nsol::Neuron *neu;
    std::vector<axonG*> ax;
    somaG* som;
    std::vector<dendriteG> dends;
    float tamMaxNeurite;

    
public:
    neuronG(nsol::Neuron *_neu);

    //Dibujar la neurona
    void draw(QOpenGLWidget* windowPaint);
    
    
    void draw(QOpenGLWidget* windowPaint,bool dim);
    
    void draw3D(QOpenGLWidget* windowPaint);
    void draw2D(QOpenGLWidget* windowPaint);
    //Dibujar el caudrado que la select, en este caso el soma
    void drawSelc(QOpenGLWidget* windowPaint);

    //Devuelve las coordinates en las que se encuentra el objeto
    void coordinates();

    //Coordenadas que se desplaza el objeto
    void displacement(float x, float y);

    //Comprueba si el objeto esta selected
    bool select(QOpenGLWidget* windowPaint, float x, float y,float z);

    //Cuando pintamos la neurona desde 0, quita el boton selected en caso de que estuviera.
    bool resetSelect();

    bool isSelected();
    float angleEqual();
    float angleTam();
    void auxDrawAngleEqual(QOpenGLWidget* windowPaint);
    void auxDrawAngleTam(QOpenGLWidget* windowPaint);
    float getTam();
    void tamNeurite();
    void grosorNeurite();
    void setNeuritesVariableGrosor(float a);
    void setNeuritesVariableTam(float a);
	void displacementN(float x,float y,float z);
	
	void calculateMaxMinNodosTerminales();
	void calculateMaxMinLongitud();
	void selectSection(QOpenGLWidget* windowPaint,float x,float y);


private:
    void tamMaxSeccion();
    void tamMaxP1P2Seccion();
	
};


#endif //HUGO_NEURON_G_H