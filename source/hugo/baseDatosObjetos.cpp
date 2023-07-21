//
// Created by alberto on 2/03/23.
//

#include "baseDatosObjetos.h"
baseDatosObjetos::baseDatosObjetos() {

}

void baseDatosObjetos::add(neuronG* neu) {
    list.push_back(neu);
}

neuronG* baseDatosObjetos::get(int i) {
    return list[i];
}

const std::vector<neuronG *> &baseDatosObjetos::getList() const {
    return list;
}



