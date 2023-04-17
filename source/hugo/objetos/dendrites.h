//
// Created by alberto on 11/11/22.
//

#ifndef HUGO_DENDRITES_H
#define HUGO_DENDRITES_H


#include <QWidget>
#include<qwidget.h>
#include <QObject>
#include <QOpenGLWidget>
#include <GL/gl.h>

#include "objetos.h"

class dendrites: public objetos {
private:

    float x;
    float y;
    float y1;
    float x1;


public:
    dendrites(float _x,float _y,float _x1,float _y1);


    float getX() const;

    float getY() const;

    float getY1() const;

    float getX1() const;

};




#endif //HUGO_DENDRITES_H
