//
// Created by alberto on 03/05/23.
//

#ifndef HUGO_AXON_G_H
#define HUGO_AXON_G_H

#include "graphic_objects.h"
#include "nsol/nsol.h"
#include "sectionH.h"
#include "neurite_g.h"


class axon_g : public neurite_g{

public:

    axon_g(nsol::Axon* _ax);
    void put_color();
};


#endif //HUGO_AXON_G_H
