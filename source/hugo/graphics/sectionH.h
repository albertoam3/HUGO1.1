//
// Created by alberto on 11/05/23.
//

#ifndef HUGO_SECTIONH_H
#define HUGO_SECTIONH_H

#include "nsol/nsol.h"
#include <QOpenGLWidget>
#include <QToolTip>
#include "math.h"
#include "VarEstado.h"
#include "VarLongitud.h"

class sectionH {
private:
    nsol::NeuronMorphologySection *sec;

    static const double PI;


    float coordX;
    float coordY;
    bool selecionada;
    std::vector<sectionH*> sectionsHijas;
    float displacementX,displacementY;
    Eigen::Vector3f color;
    float tamSeccion;
    float tamPuntoInicialPuntoFinal;


public:
    sectionH(nsol::NeuronMorphologySection* _sec);
    float getTamTotal(float *max, float *min);
    float getTamSection();
    float getTamPuntoInicialPuntoFinal();
    float getVolumenAcumulado(float *maxVolumenSeccion,float *minVolumenSeccion);
    float getVolumenSeccion();
    float terminalNodes();
    nsol::NeuronMorphologySection *getSection();
    void drawSectionsTree(float x1, float x2, float angle, float hipotenusa, float dif_angle, bool g, float max, float min, VarEstado variable_grosor);
    void drawSectionsDendograma(float x, float y, float angle_hueco, float angle, float terminal_nodes, int *cont, bool g,
                                float max, float min, VarEstado variable_grosor, VarLongitud var_long, float max_long, float min_long);
    void drawSectionsEsquema(float x, float y, float terminal_nodes);

    void drawSol(float x, float y, float angle_hueco, float angle, float terminal_nodes, int *cont, bool g,
                 float max, float min, VarEstado variable_grosor);
    bool selected(QOpenGLWidget* windowPaint,float x,float y);
    float getPoint2(VarLongitud var_long, float max, float min);
    void getTamTotalP1P2(float *max, float *min);

    void seleccion();
    void draw3d( float x,float y,float z);
    void selected_hijas(bool sel);
    void setDisplacementX(float displacementX);

    void setDisplacementY(float displacementY);
    void putColor(Eigen::Vector3f c);

    nsol::NeuronMorphologySection *getSec() const;

    void cont_points_neu(int aux[9],float separador,float crecimiento);

private:
    float distanciaEntreRegistros(nsol::Node* r1, nsol::Node* r2);
    float areaCono(nsol::Node* r1,nsol::Node* r2);
    float volumenCono(nsol::Node* r1, nsol::Node* r2);
    void getLineWidth(VarEstado variable_grosor, sectionH sec, float max, float min);
    void drawArco(float x1,float y1,float x2,float y2,float angle,float angle_hueco, int* cont,float terminal_nodes,float modulo);
    void drawLine(float x1,float y1,float x2,float y2);
    void drawPoint(float x1,float y1);

    void coordinates();
    void seeToolTip(QString texto,QOpenGLWidget *windowPaint);

    float distanciaEntreRegistrosV(Eigen::Vector3f r1, Eigen::Vector3f r2);
    bool seleccionada_primera;

};



#endif //HUGO_SECCTIONH_H


