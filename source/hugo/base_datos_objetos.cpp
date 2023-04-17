//
// Created by alberto on 2/03/23.
//

#include "base_datos_objetos.h"
base_datos_objetos::base_datos_objetos() {

}

void base_datos_objetos::add(graphic_objects* obj) {
    list.push_back(obj);
}

graphic_objects* base_datos_objetos::get(int i) {
    return list[i];
}

const std::vector<graphic_objects *> &base_datos_objetos::getList() const {
    return list;
}



