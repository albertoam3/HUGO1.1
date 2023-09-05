//
// Created by alberto on 03/05/23.
//


#ifndef HUGO_DENDRITE_G_H
#define HUGO_DENDRITE_G_H

#include "graphicObjects.h"
#include "nsol/nsol.h"
#include "sectionH.h"
#include "neuriteG.h"


class dendriteG : public neuriteG{

public:
    typedef enum TDendriteType
    {
        BASAL = 0,
        APICAL
    } TDendriteType;

    dendriteG(nsol::Dendrite* _dend);
    void putColor();
    void setTDendriteType(TDendriteType den);
    
private:
    TDendriteType _dendriteType;
};


#endif //HUGO_DENDRITE_G_H

