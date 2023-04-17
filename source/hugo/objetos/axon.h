//
// Created by alberto on 16/11/22.
//

#ifndef HUGO_AXON_H
#define HUGO_AXON_H

#include <QWidget>
#include<qwidget.h>
#include <QObject>
#include <QOpenGLWidget>
#include <QPainter>
#include <QPaintEvent>

#include "objetos.h"

class axon: public objetos {
private:

    float x1;
    float y1;
    float x2;
    float y2;
    float aux;

public:
    axon(float _x1,float _x2, float _y1, float _y2);

    float getX1() const;

    float getY1() const;

    float getX2() const;

    float getY2() const;
};






#endif //HUGO_AXON_H
