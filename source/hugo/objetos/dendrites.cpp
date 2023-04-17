//
// Created by alberto on 11/11/22.
//

#include "dendrites.h"

dendrites::dendrites(float _x,float _y,float _x1, float _y1){
    x=_x;
    y=_y;
    x1=_x1;
    y=_y1;
}


float dendrites::getX() const {
    return x;
}

float dendrites::getY() const {
    return y;
}

float dendrites::getY1() const {
    return y1;
}

float dendrites::getX1() const {
    return x1;
}
