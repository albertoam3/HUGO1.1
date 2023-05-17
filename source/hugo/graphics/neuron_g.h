//
// Created by alberto on 30/04/23.
//

#ifndef HUGO_NEURON_G_H
#define HUGO_NEURON_G_H

#include "objetos/neuron.h"
#include <QOpenGLWidget>
#include "graphic_objects.h"
#include "graphic_axon.h"
#include "graphic_soma.h"
#include "graphic_dendrite.h"
#include <nsol/nsol.h>
#include "soma_g.h"
#include "axon_g.h"
#include "dendrite_g.h"
#include "sectionH.h"

#include "vector"
#include "cmath"

class neuron_g : public graphic_objects{
private:
    nsol::Neuron *neu;
    std::vector<axon_g*> ax;
    soma_g* som;
    std::vector<dendrite_g> dends;
    float tam_max_neurite;
    
public:
    neuron_g(nsol::Neuron *_neu);

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
    float getTam();
    void tamNeurite();

};


#endif //HUGO_NEURON_G_H
