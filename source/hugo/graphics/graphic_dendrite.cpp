//
// Created by alberto on 28/02/23.
//

#include "graphic_dendrite.h"



constexpr float pint=0.5f;

graphic_dendrite::graphic_dendrite(dendrites* _den){
    dend=_den;
    name="dendrite";
    displacementX=0;
    displacementY=0;
    terminal_nodes=0;
}
void graphic_dendrite::draw(QOpenGLWidget* windowPaint){

    glPointSize(5+terminal_nodes*pint);
    glBegin(GL_POINTS); // Iniciar el modo de dibujo de puntos
    glColor3f(1.0, 0.0, 0.0); // Establecer el color del punto a rojo

    glVertex2f( displacementX+init_x, displacementY+init_y); // Especificar las coordenadas del punto a dibujar
    glEnd();
    if(selected)
        drawSelc(windowPaint);
}

void graphic_dendrite::drawSelc(QOpenGLWidget* windowPaint){
    glLineWidth(4.0);
    glBegin(GL_LINES);
    coordinates();
    glColor3f(0.0f, 0.3f, 0.1f);
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
void graphic_dendrite::coordinates(){
    min_X= displacementX + init_x - 0.03;
    min_Y= displacementY + init_y - 0.03;
    max_X= displacementX + init_x + 0.03;
    max_Y= displacementY + init_y + 0.03;
    min_Z=displacementZ-0.03;
    max_Z=displacementZ+0.03;
}



//Comprueba si el objeto esta selected
bool graphic_dendrite::select(QOpenGLWidget* windowPaint, float x, float y,float z){
    coordinates();
    if(x>min_X && x<max_X && y>min_Y && y<max_Y && z>min_Z && z<max_Z)
        selected=!selected;
    if(coord_include(x,y)){
        drawSelc(windowPaint);
        QString texto="Dendrita,nodos terminales: ";
        texto+=QString::number(getTerminalNodes());
        seeToolTip(texto,windowPaint);
    }
    return selected;
}

//Cuando pintamos el objeto desde 0, quita el boton selected en caso de que estuviera.
bool graphic_dendrite::resetSelect() {
    selected = false;
    return selected;

}

bool graphic_dendrite::isSelected() {
    return selected;
}

int graphic_dendrite::getTerminalNodes() const {
    return terminal_nodes;
}

void graphic_dendrite::setTerminalNodes(int terminalNodes) {
    terminal_nodes = terminalNodes;
}


