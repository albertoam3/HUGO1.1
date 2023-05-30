//
// Created by alberto on 29/05/23.
//

#include "neurite_g.h"
constexpr float pint=0.5f;

neurite_g::neurite_g(nsol::Neurite* _neurite){
    this->neurite=_neurite;
    name="neurite";
    displacementX=0;
    displacementY=0;
    terminal_nodes=this->neurite->numBranches();
    firstSection=new sectionH(this->neurite->firstSection());
    tam=0;
    scala=1;
    tam=firstSection->getTamTotal()/100;
    
}
void neurite_g::draw(QOpenGLWidget* windowPaint){
    
    glPointSize(terminal_nodes*pint*scala*3);
    glBegin(GL_LINES); // Iniciar el modo de dibujo de linea
    glColor3f(1.0, color(), 0.0); 
    glVertex2f( displacementX+init_x, displacementY+init_y); // Especificar las coordenadas del punto a dibujar
    glVertex2f(displacementX+init_x+tam_mult*(displacementX+init_x),displacementY+init_y+tam_mult*(displacementY+init_y));
    glEnd();  

}
void neurite_g::drawSelc(QOpenGLWidget* windowPaint){
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
void neurite_g::coordinates(){
    min_X= displacementX + init_x - 0.005*terminal_nodes;
    min_Y= displacementY + init_y - 0.005*terminal_nodes;
    max_X= displacementX + init_x + 0.005*terminal_nodes;
    max_Y= displacementY + init_y + 0.005*terminal_nodes;
    min_Z=displacementZ-0.03;
    max_Z=displacementZ+0.03;
}



//Comprueba si el objeto esta selected
bool neurite_g::select(QOpenGLWidget* windowPaint, float x, float y,float z){
    coordinates();
    if(x>min_X && x<max_X && y>min_Y && y<max_Y && z>min_Z && z<max_Z)
        selected=!selected;
    if(coord_include(x,y)){
        drawSelc(windowPaint);
        QString texto="Axon,nodos terminales: ";
        texto+=QString::number(getTerminalNodes());
        seeToolTip(texto,windowPaint);
    }
    return selected;
}

//Cuando pintamos el objeto desde 0, quita el boton selected en caso de que estuviera.
bool neurite_g::resetSelect() {
    selected = false;
    return selected;

}

bool neurite_g::isSelected() {
    return selected;
}

int neurite_g::getTerminalNodes() const {
    return terminal_nodes;
}

void neurite_g::setTerminalNodes(int terminalNodes) {
    terminal_nodes = terminalNodes;
}

float neurite_g::getTam(){
	return tam;
}

void neurite_g::setTamMult(float t){
	tam_mult=t;
}

