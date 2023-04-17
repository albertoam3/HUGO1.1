//
// Created by alberto on 10/11/22.
//

#include "neuron.h"
#include <math.h>

neuron::neuron(soma* _som, axon* _ax){
    som=_som;
    ax=_ax;


}
neuron::neuron(soma *_som, axon *_ax, std::vector<dendrites> _dends) {
    som=_som;
    ax=_ax;
    dends=_dends;
}


soma *neuron::getSom() const {
    return som;
}

axon *neuron::getAx() const {
    return ax;
}

const std::vector<dendrites> neuron::getDends() const {
    return dends;
}
