//
// Created by alberto on 27/02/23.
//

#include "graphic_axon.h"

graphic_axon::graphic_axon(axon* _ax){
    ax=_ax;
    name="axon";
    displacementX=0;
    displacementY=0;
    terminal_nodes=300;
    angle=0;
    dist=0;
}
void graphic_axon::draw(QOpenGLWidget* windowPaint){
    glColor3f(0.3f, 0.1f, 0.9f);
    glLineWidth(3.0); // Establecer el ancho de la línea

    dist=sqrt(pow(ax->getX2()-ax->getX1(),2) + pow(ax->getY2()- ax->getY1() ,2));
    coordinates();
    glBegin(GL_LINES); // Comenzar a dibujar la línea
    glVertex2f(ax->getX1() + displacementX + init_x, ax->getY1() + displacementY + init_y); // Definir el punto de inicio de la línea
    glVertex2f(dist*cos(angle) + displacementX + init_x , dist*sin(angle) + displacementY + init_y); // Definir el punto final de la línea
    glEnd(); // Terminar de dibujar la línea

    glFlush(); // Renderizar los cambios en la pantalla

    if(selected)
        drawSelc(windowPaint);
}

 void graphic_axon::drawSelc(QOpenGLWidget* windowPaint){
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
void graphic_axon::coordinates(){
    min_X= ax->getX1() + displacementX + init_x -0.03;
    min_Y= ax->getY1() + displacementY + init_y -0.03;
    max_X= dist*cos(angle) + displacementX + init_x +0.03;
    max_Y= dist*sin(angle) + displacementY + init_y +0.03;
    min_Z=displacementZ-0.03;
    max_Z=displacementZ+0.03;

}

//Comprueba si el objeto esta selected
bool graphic_axon::select(QOpenGLWidget* windowPaint, float x, float y,float z){
    coordinates();
    if(x>min_X && x<max_X && y>min_Y && y<max_Y){
        selected=!selected;

        }
    if(coord_include(x,y)){
        drawSelc(windowPaint);
        QString texto="Axon ,nodos terminales: ";
        texto+=QString::number(getTerminalNodes());
        seeToolTip(texto,windowPaint);
    }
    return selected;
}

//Cuando pintamos el objeto desde 0, quita el boton selected en caso de que estuviera.
bool graphic_axon::resetSelect(){
    selected=false;
    return selected;

}

bool graphic_axon::isSelected() {
    return selected;
}

int graphic_axon::getTerminalNodes() const {
    return terminal_nodes;
}

void graphic_axon::setAngle(float angle) {
    graphic_axon::angle = angle;
}

