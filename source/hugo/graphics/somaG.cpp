//
// Created by alberto on 03/05/23.
//

#include "somaG.h"
#include "math.h"

somaG::somaG(nsol::Soma* _som){
    som=_som;
    name="soma";
    displacementX=0;
    displacementY=0;
}
void somaG::draw(QOpenGLWidget* windowPaint){
    glPointSize(1);
    glBegin(GL_LINES);
    glColor3f(0.7f, 0.5f, 0.2f);
    float calcX,calcY;
    glVertex2f(0.5 + displacementX + initX, 0 + displacementY + initY);
    for(float i=0;i<10;i+=0.01){
        calcX=0.5*cos(i);
        calcY=0.5*sin(i);
        glVertex2f(calcX + displacementX + initX, calcY + displacementY + initY);
        glVertex2f(calcX + displacementX + initX, calcY + displacementY + initY);
    }
    glVertex2f(calcX + displacementX + initX, calcY + displacementY + initY);
    glEnd();
    if(selected)
        drawSelc(windowPaint);

}

void somaG::drawSelc(QOpenGLWidget* windowPaint){
    glLineWidth(4.0);
    glBegin(GL_LINES);
    coordinates();
    glColor3f(0.7f, 0.1f, 0.1f);
    glVertex2f(maxX, maxY);
    glVertex2f(maxX, minY);

    glVertex2f(maxX, maxY);
    glVertex2f(minX, maxY);

    glVertex2f(minX, maxY);
    glVertex2f(minX, minY);

    glVertex2f(maxX, minY);
    glVertex2f(minX, minY);
    glEnd();

}


//Devuelve las coordinates en las que se encuentra el objeto
void somaG::coordinates(){
   /* minX= -som->meanRadius() + displacementX + initX;
    minY= -som->meanRadius() + displacementY + initY;
    maxX= som->meanRadius() + displacementX + initX;
    maxY= som->meanRadius() + displacementY + initY;
    minZ=displacementZ-0.03;
    maxZ=displacementZ+0.03;
    */
    minX= -0.5 + displacementX + initX;
    minY= -0.5 + displacementY + initY;
    maxX= 0.5 + displacementX + initX;
    maxY= 0.5 + displacementY + initY;
    minZ= 0.5 - 0.03;
    maxZ= 0.5 + 0.03;
}

//Comprueba si el objeto esta selected
bool somaG::select(QOpenGLWidget* windowPaint, float x, float y, float z) {
    coordinates();
    if (x > minX && x < maxX && y > minY && y < maxY && z > minZ && z < maxZ){
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
bool somaG::resetSelect() {
    selected = false;
    return selected;

}

bool somaG::isSelected() {
    return selected;
}

float somaG::getRadio() {
    return 0.5;
}


float somaG::getTam(){
	return 3.1416*som->meanRadius()*som->meanRadius();
}
