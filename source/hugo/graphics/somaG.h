//
// Created by alberto on 28/02/23.
//

#ifndef HUGO_SOMA_G_H
#define HUGO_SOMA_G_H

#include "graphicObjects.h"
#include "nsol/nsol.h"

class somaG : public graphicObjects{
private:
    nsol::Soma *som;

public:


    somaG(nsol::Soma* _som);
/*Metodo que esta definido en cada clase hijo, quieres pintaran lo que necesiten en la pantalla openGLWidget
con un desplazamiento de X y otro desplazamiento de Y*/
    void draw(QOpenGLWidget* windowPaint);

    //Dibujar el caudrado que la select.
    void drawSelc(QOpenGLWidget* windowPaint);

    //Devuelve las coordinates en las que se encuentra el objeto
    void coordinates();

    //Comprueba si el objeto esta selected
    bool select(QOpenGLWidget* windowPaint, float x, float y,float z);

    //Cuando pintamos el objeto desde 0, quita el boton selected en caso de que estuviera.
    bool resetSelect();

    bool isSelected();

    float getRadio();
    float getTam();
    void draw3d(float x,float y,float z);
};



#endif //HUGO_SOMA_G_H
