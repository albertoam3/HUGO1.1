//
// Created by alberto on 03/05/23.
//


#ifndef HUGO_DENDRITE_G_H
#define HUGO_DENDRITE_G_H

#include "graphic_objects.h"
#include "nsol/nsol.h"
#include "sectionH.h"
#include "neurite_g.h"


class dendrite_g : public neurite_g{

public:
    typedef enum TDendriteType
    {
        BASAL = 0,
        APICAL
    } TDendriteType;

    dendrite_g(nsol::Dendrite* _dend);
    void put_color();
    void setTDendriteType(TDendriteType den);
private:
    TDendriteType _dendriteType;
};


#endif //HUGO_DENDRITE_G_H

