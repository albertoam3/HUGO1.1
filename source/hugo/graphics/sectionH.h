//
// Created by alberto on 11/05/23.
//

#ifndef HUGO_SECTIONH_H
#define HUGO_SECTIONH_H

#include "nsol/nsol.h"

class sectionH {
private:
    nsol::NeuronMorphologySection *sec;
    
    //Tamaño total de esta sección más sus secciones hijas
    //EL tamaño total de la primera sección sera el tamaño total de la neurita
    float tamTotal;
    //Tamaño de esta sección
    float tamSeccion;

public:
    sectionH(nsol::NeuronMorphologySection* _sec);
    float getTamTotal();
    float getTamSection();
    nsol::NeuronMorphologySection getSection();
    
};



#endif //HUGO_SECCTIONH_H


