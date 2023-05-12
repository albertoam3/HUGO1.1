//
// Created by alberto on 23/02/23.
//

#include "graphic_neuron.h"

#include <iostream>

const float pi = 3.14159265359;

graphic_neuron::graphic_neuron(neuron *_neu){
    neu=_neu;
    ax.push_back(new graphic_axon(neu->getAx()));
    som=new graphic_soma(neu->getSom());
    std::vector<dendrites> den=neu->getDends();
    for (auto & i : den) {
        dends.push_back(*new graphic_dendrite(&i));
    }

    selected=false;
    displacementX=0;
    displacementY=0;
    init_x=0;
    init_y=0;
    coordinates();
    name="neuron";
    angleXTam=false;

    int a=5;
    for (auto & item : dends) {
        item.setTerminalNodes(a);
        a += 5;
    }
}

void graphic_neuron::draw(QOpenGLWidget* windowPaint){

   if(angleXTam==false)
       auxDrawAngleEqual(windowPaint);
   else
       auxDrawAngleTam(windowPaint);

    som->setDisplacements(displacementX, displacementY);
    som->coordInitials(init_x, init_y);
    som->draw(windowPaint);


    coordinates();
    if(selected) {
        for(auto & dend : dends){
            if(dend.isSelected())
                dend.drawSelc(windowPaint);
        }
        if (som->isSelected())
            som->drawSelc(windowPaint);
        else if (ax[0]->isSelected())
            ax[0]->drawSelc(windowPaint);

    }
}

void graphic_neuron::drawSelc(QOpenGLWidget* windowPaint){
    glLineWidth(4.0);
    glBegin(GL_LINES);

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


void graphic_neuron::coordinates(){
    min_X= -neu->getSom()->getRad() + displacementX + init_x;
    min_Y= -neu->getSom()->getRad() + displacementY + init_y;
    max_X= neu->getSom()->getRad() + displacementX + init_x;
    max_Y= neu->getSom()->getRad() + displacementY + init_y;
    min_Z=displacementZ-0.03;
    max_Z=displacementZ+0.03;
}


bool graphic_neuron::select(QOpenGLWidget* windowPaint, float x, float y,float z)  {
    coordinates();
    if(!selected){
        for (auto &dend: dends)
            if (dend.select(windowPaint, x, y,z)) {
                selected = true;
                break;
            }
        if (!selected && som->select(windowPaint, x, y,z)) {
            selected = true;
        } else if ( !selected && ax[0]->select(windowPaint, x, y,z) ) {
            selected = true;
        }
    }
    else {
        for (auto &dend: dends)
            if (dend.isSelected()) {
                selected = dend.select(windowPaint, x, y,z);
                break;
            }
        if (som->isSelected())
            selected = som->select(windowPaint, x, y,z);
        else if (ax[0]->isSelected())
            selected = ax[0]->select(windowPaint, x, y,z);
    }
    return selected;
}

bool graphic_neuron::resetSelect() {
    selected=false;
    ax[0]->resetSelect();
    som->resetSelect();

    for (int i = 0; i < dends.size(); i++) {
        dends[i].resetSelect();
    }
    return selected;
}

bool graphic_neuron::isSelected()  {
    return selected;
}

float graphic_neuron::angle_equal(){
    return 2*pi/(dends.size() +ax.size());
}
float graphic_neuron::angle_tam() {
    int n=0;
    for(int i=0;i<dends.size();i++){
        n+=dends[i].getTerminalNodes();
    }
    for(int i=0;i<ax.size();i++){
        n+=ax[i]->getTerminalNodes();
    }
    return n;
}

void graphic_neuron::auxDrawAngleEqual(QOpenGLWidget* windowPaint) {
    float an=angle_equal();
    float aux=an;
    float radio=som->getRadio();
    ax[0]->setDisplacements(displacementX, displacementY);
    ax[0]->coordInitials(init_x, init_y);
    ax[0]->setAngle(an);
    ax[0]->setScala(scala);
    ax[0]->draw(windowPaint);

    an+=aux;
    for (auto & item : dends) {
        item.setDisplacements(displacementX, displacementY);
        item.coordInitials(init_x+radio*cos(an), init_y+radio*sin(an));
        item.setScala(scala);
        item.draw(windowPaint);
        
        an+=aux;
    }

}
void graphic_neuron::auxDrawAngleTam(QOpenGLWidget *windowPaint) {
    float radio=som->getRadio();
    float i=0;
    i+=ax[0]->getTerminalNodes();
    ax[0]->setDisplacements(displacementX, displacementY);
    ax[0]->coordInitials(init_x, init_y);
    ax[0]->setAngle(i/angle_tam()*2*pi);
    ax[0]->setScala(scala);
    ax[0]->draw(windowPaint);

    for(auto & item: dends){
        item.setDisplacements(displacementX,displacementY);
        i+=item.getTerminalNodes();
        item.coordInitials(init_x+radio*cos(i/angle_tam()*2*pi),init_y+radio*sin(i/angle_tam()*2*pi));
        item.setScala(scala);
        item.draw(windowPaint);
    }

}


