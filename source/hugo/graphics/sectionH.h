//
// Created by alberto on 11/05/23.
//

#ifndef HUGO_SECTIONH_H
#define HUGO_SECTIONH_H

#include "nsol/nsol.h"
#include <QOpenGLWidget>
#include <QToolTip>
#include "math.h"
#include "VariableEstado.h"

class sectionH {
private:
    nsol::NeuronMorphologySection *sec;

    static const double PI;


    float coord_x;
    float coord_y;
    bool selecionada;
    std::vector<sectionH*> sectionsHijas;
    float displacementX,displacementY;
    Eigen::Vector3f color;


public:
    sectionH(nsol::NeuronMorphologySection* _sec);
    float getTamTotal(float *max, float *min);
    float getTamSection();
    float getVolumenAcumulado(float *maxVolumenSeccion,float *minVolumenSeccion);
    float getVolumenSeccion();
    float terminalNodes();
    nsol::NeuronMorphologySection getSection();
    void drawSectionsTree(float x1, float x2,float angle,float hipotenusa,float dif_angle,bool g,float max,float min,VariableEstado variable_grosor);
    void drawSectionsDendograma(float x, float y, float angle_hueco, float angle, float dir_x, float dir_y, float terminal_nodes, int *cont, bool g, float max, float min, VariableEstado variable_grosor);
    bool selected(QOpenGLWidget* windowPaint,float x,float y);


    void seleccion();
    void draw3d( float x,float y,float z);
    void selected_hijas(bool sel);
    void setDisplacementX(float displacementX);

    void setDisplacementY(float displacementY);
    void putColor(Eigen::Vector3f c);
private:
    float distanciaEntreRegistros(nsol::Node* r1, nsol::Node* r2);
    float areaCono(nsol::Node* r1,nsol::Node* r2);
    float volumenCono(nsol::Node* r1, nsol::Node* r2);
    void getLineWidth(VariableEstado variable_grosor,sectionH sec,float max,float min);
    void drawArco(float x1,float y1,float x2,float y2,float angle,float angle_hueco, int* cont,float terminal_nodes,float modulo);
    void drawLine(float x1,float y1,float x2,float y2);
    void drawPoint(float x1,float y1);

    void coordinates();
    void seeToolTip(QString texto,QOpenGLWidget *windowPaint);



};



#endif //HUGO_SECCTIONH_H


