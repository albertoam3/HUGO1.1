//
// Created by alberto on 16/11/22.
//

#ifndef HUGO_SOMA_H
#define HUGO_SOMA_H




#include <QWidget>
#include<qwidget.h>
#include <QObject>
#include <QOpenGLWidget>
#include <GL/gl.h>

#include "objetos.h"

class soma: public objetos {
private:

    float rad;


public:
    soma(float _rad);

    float getRad() const;

};



#endif //HUGO_SOMA_H
