//
// Created by alberto on 2/03/23.
//

#ifndef HUGO_BASE_DATOS_OBJETOS_H
#define HUGO_BASE_DATOS_OBJETOS_H

#include "graphics/neuron_g.h"
#include <vector>


#include <nsol/nsol.h>

class base_datos_objetos {
private:
    std::vector<neuron_g*> list;

public:
    base_datos_objetos();
    void add(neuron_g* neu);
    neuron_g* get(int i);

    const std::vector<neuron_g *> &getList() const;
};


#endif //HUGO_BASE_DATOS_OBJETOS_H
