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
    float getVolumenAcumulado();
    float getVolumenSeccion();
    nsol::NeuronMorphologySection getSection();
    void drawSections(float x1, float x2,float angle,float hipotenusa,float dif_angle,bool g);
    
private:    
    float distanciaEntreRegistros(nsol::Node* r1, nsol::Node* r2);
    float areaCono(nsol::Node* r1,nsol::Node* r2);
    float volumenCono(nsol::Node* r1, nsol::Node* r2);
    


    
};



#endif //HUGO_SECCTIONH_H


