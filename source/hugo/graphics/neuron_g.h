//
// Created by alberto on 30/04/23.
//

#ifndef HUGO_GRAPHIC_NEURON_H
#define HUGO_GRAPHIC_NEURON_H

#include "objetos/neuron.h"
#include <QOpenGLWidget>
#include "graphic_objects.h"
#include "graphic_axon.h"
#include "graphic_soma.h"
#include "graphic_dendrite.h"
#include <nsol/nsol.h>

#include "vector"
#include "cmath"

class graphic_neuron : public graphic_objects{
private:
    nsol::neuron *neu;
    std::vector<graphic_axon*> ax;
    graphic_soma* som;
    std::vector<graphic_dendrite> dends;
public:
    graphic_neuron(neuron *_neu);

    //Dibujar la neurona
    void draw(QOpenGLWidget* windowPaint);
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
    float angle_equal();
    float angle_tam();
    void auxDrawAngleEqual(QOpenGLWidget* windowPaint);
    void auxDrawAngleTam(QOpenGLWidget* windowPaint);


};


#endif //HUGO_GRAPHIC_NEURON_H
