//
// Created by alberto on 2/03/23.
//

#ifndef HUGO_BASE_DATOS_OBJETOS_H
#define HUGO_BASE_DATOS_OBJETOS_H

#include "graphics/graphic_objects.h"
#include <vector>


#include <nsol/nsol.h>

class base_datos_objetos {
private:
    std::vector<graphic_objects*> list;

public:
    base_datos_objetos();
    void add(graphic_objects* obj);
    graphic_objects* get(int i);

    const std::vector<graphic_objects *> &getList() const;
};


#endif //HUGO_BASE_DATOS_OBJETOS_H
