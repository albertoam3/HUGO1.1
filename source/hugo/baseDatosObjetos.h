//
// Created by alberto on 2/03/23.
//

#ifndef HUGO_BASE_DATOS_OBJETOS_H
#define HUGO_BASE_DATOS_OBJETOS_H

#include "graphics/neuronG.h"
#include <vector>


#include <nsol/nsol.h>

class baseDatosObjetos {
private:
    std::vector<neuronG*> list;

public:
    baseDatosObjetos();
    void add(neuronG* neu);
    neuronG* get(int i);

    const std::vector<neuronG *> &getList() const;
};


#endif //HUGO_BASE_DATOS_OBJETOS_H
