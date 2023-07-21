//
// Created by alberto on 03/05/23.
//

#ifndef HUGO_AXON_G_H
#define HUGO_AXON_G_H

#include "graphicObjects.h"
#include "nsol/nsol.h"
#include "sectionH.h"
#include "neuriteG.h"


class axonG : public neuriteG{

public:

    axonG(nsol::Axon* _ax);
    void putColor();
};


#endif //HUGO_AXON_G_H
