//
// Created by alberto on 11/05/23.
//

#ifndef HUGO_SECTIONH_H
#define HUGO_SECTIONH_H

#include "nsol/nsol.h"
#include <QOpenGLWidget>
#include "math.h"

class sectionH {
private:
    nsol::NeuronMorphologySection *sec;
    
    //Tamaño total de esta sección más sus secciones hijas
    //EL tamaño total de la primera sección sera el tamaño total de la neurita
    float tamTotal;
    //Tamaño de esta sección
    float tamSeccion;
    static const double PI;



public:
    sectionH(nsol::NeuronMorphologySection* _sec);
    float getTamTotal();
    float getTamSection();
    float getVolumenAcumulado(float *maxVolumenSeccion,float *minVolumenSeccion);
    float getVolumenSeccion();
    float terminalNodes();
    nsol::NeuronMorphologySection getSection();
    void drawSectionsTree(float x1, float x2,float angle,float hipotenusa,float dif_angle,bool g);
    void drawSectionsDendograma(float x,float y,float angle_hueco,float angle,float init_x,float init_y,float terminal_nodes,int *cont,bool g,float maxVS,float minVS);
    void selected(float x,float y, float z);
    
private:
    float distanciaEntreRegistros(nsol::Node* r1, nsol::Node* r2);
    float areaCono(nsol::Node* r1,nsol::Node* r2);
    float volumenCono(nsol::Node* r1, nsol::Node* r2);
    


    
};



#endif //HUGO_SECCTIONH_H


