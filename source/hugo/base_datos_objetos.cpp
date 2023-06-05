//
// Created by alberto on 2/03/23.
//

#include "base_datos_objetos.h"
base_datos_objetos::base_datos_objetos() {

}

void base_datos_objetos::add(neuron_g* neu) {
    list.push_back(neu);
}

neuron_g* base_datos_objetos::get(int i) {
    return list[i];
}

const std::vector<neuron_g *> &base_datos_objetos::getList() const {
    return list;
}



