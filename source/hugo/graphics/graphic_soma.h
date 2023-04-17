//
// Created by alberto on 28/02/23.
//

#ifndef HUGO_GRAPHIC_SOMA_H
#define HUGO_GRAPHIC_SOMA_H

#include "graphic_objects.h"
#include "objetos/soma.h"

class graphic_soma :public graphic_objects{
private:
    soma *som;

public:


    graphic_soma(soma* _som);
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
};



#endif //HUGO_GRAPHIC_SOMA_H
