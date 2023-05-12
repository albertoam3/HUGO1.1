//
// Created by alberto on 28/02/23.
//

#ifndef HUGO_GRAPHIC_DENDRITE_H
#define HUGO_GRAPHIC_DENDRITE_H

#include "graphic_objects.h"
#include "objetos/dendrites.h"


class graphic_dendrite : public graphic_objects{
private:
    dendrites *dend;
    int terminal_nodes;
    float tamano_punto;

public:


    graphic_dendrite(dendrites* _den);
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
    void getMensaje();
};




#endif //HUGO_GRAPHIC_DENDRITE_H
