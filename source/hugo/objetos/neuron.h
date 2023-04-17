//
// Created by alberto on 10/11/22.
//

#ifndef HUGO_NEURON_H
#define HUGO_NEURON_H



#include <QOpenGLWidget>


#include "objetos.h"
#include "soma.h"
#include "dendrites.h"
#include "axon.h"

#include "vector"


class neuron: public objetos {
private:
    soma* som;
    axon* ax;
    std::vector<dendrites> dends;
public:
    neuron(soma* _som, axon* _ax);
    neuron(soma* _som, axon* _ax,std::vector<dendrites> _dends );

    soma *getSom() const;

    axon *getAx() const;

    const std::vector<dendrites> getDends() const;
};



#endif //HUGO_NEURON_H
