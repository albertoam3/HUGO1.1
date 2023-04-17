//
// Created by alberto on 28/02/23.
//

#include "graphic_soma.h"
#include "math.h"

graphic_soma::graphic_soma(soma* _som){
    som=_som;
    name="soma";
    displacementX=0;
    displacementY=0;
}
void graphic_soma::draw(QOpenGLWidget* windowPaint){
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.5f, 0.2f);
    float calcX,calcY;
    for(float i=0;i<10;i+=0.01){
        calcX=som->getRad()*cos(i);
        calcY=som->getRad()*sin(i);
        glVertex2f(calcX + displacementX + init_x, calcY + displacementY + init_y);
    }
    glEnd();
    if(selected)
        drawSelc(windowPaint);
}

void graphic_soma::drawSelc(QOpenGLWidget* windowPaint){
    glLineWidth(4.0);
    glBegin(GL_LINES);
    coordinates();
    glColor3f(0.7f, 0.1f, 0.1f);
    glVertex2f(max_X, max_Y);
    glVertex2f(max_X, min_Y);

    glVertex2f(max_X, max_Y);
    glVertex2f(min_X, max_Y);

    glVertex2f(min_X, max_Y);
    glVertex2f(min_X, min_Y);

    glVertex2f(max_X, min_Y);
    glVertex2f(min_X, min_Y);
    glEnd();

}


//Devuelve las coordinates en las que se encuentra el objeto
void graphic_soma::coordinates(){
    min_X= -som->getRad() + displacementX + init_x;
    min_Y= -som->getRad() + displacementY + init_y;
    max_X= som->getRad() + displacementX + init_x;
    max_Y= som->getRad() + displacementY + init_y;
    min_Z=displacementZ-0.03;
    max_Z=displacementZ+0.03;
}

//Comprueba si el objeto esta selected
bool graphic_soma::select(QOpenGLWidget* windowPaint, float x, float y,float z) {
    coordinates();
    if (x > min_X && x < max_X && y > min_Y && y < max_Y && z>min_Z && z<max_Z){
        selected = !selected;
    }
    if(coord_include(x,y)){
        QString texto="Soma, radio: ";
        texto+=QString::number(getRadio());
        seeToolTip(texto,windowPaint);
    }
    return selected;
}

//Cuando pintamos el objeto desde 0, quita el boton selected en caso de que estuviera.
bool graphic_soma::resetSelect() {
    selected = false;
    return selected;

}

bool graphic_soma::isSelected() {
    return selected;
}

float graphic_soma::getRadio() {
    return som->getRad();
}
