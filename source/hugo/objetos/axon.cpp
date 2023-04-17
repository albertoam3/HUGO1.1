//
// Created by alberto on 16/11/22.
//


#include "axon.h"


axon::axon(float _x1,float _x2, float _y1, float _y2){
    x1=_x1;
    x2=_x2;
    y1=_y1;
    y2=_y2;
}


float axon::getX1() const {
    return x1;
}

float axon::getY1() const {
    return y1;
}

float axon::getX2() const {
    return x2;
}

float axon::getY2() const {
    return y2;
}
