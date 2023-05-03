//
// Created by alberto on 27/02/23.
//

#ifndef HUGO_AXON_G_H
#define HUGO_AXON_G_H

#include "graphic_objects.h"
#include "nsol/nsol.h"


class axon_g : public graphic_objects{
private:
    nsol::Axon *ax;
    float terminal_nodes;
    float angle;
    float dist;

public:


    axon_g(nsol::Axon* _ax);
/*Metodo que esta definido en cada clase hijo, quieres pintaran lo que necesiten en la pantalla openGLWidget
con un desplazamiento de X y otro desplazamiento de Y*/
    void draw(QOpenGLWidget* windowPaint);

    //Dibujar el caudrado que la select.
     void drawSelc(QOpenGLWidget* windowPaint);

    //Devuelve las coordinates en las que se encuentra el objeto
     void coordinates();

    //Coordenadas que se desplaza el objeto
     void displacement(float x, float y);

    //Comprueba si el objeto esta selected
     bool select(QOpenGLWidget* windowPaint, float x, float y,float z);

    //Cuando pintamos el objeto desde 0, quita el boton selected en caso de que estuviera.
     bool resetSelect();

    bool isSelected();

    int getTerminalNodes() const;
    void setTerminalNodes(int terminalNodes);

    void setAngle(float angle);
};


#endif //HUGO_AXON_G_H
