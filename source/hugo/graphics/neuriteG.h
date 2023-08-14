//
//
// Created by alberto on 29/05/23.
//

#ifndef HUGO_NEURITE_G_H
#define HUGO_NEURITE_G_H

#include "graphicObjects.h"
#include "nsol/nsol.h"
#include "sectionH.h"
#include <QLineEdit>
#include "VarEstado.h"
#include "VarLongitud.h"




class neuriteG : public graphicObjects{
private:
    nsol::Neurite *neurite;
    float terminalNodes;
    float angle{};
    float angleGap;

    sectionH* firstSection;
    float tam;
    float tamMult{};
    float grosor{};
    VarEstado variableGrosor;
    VarLongitud variableLongitud;
    float maxTerminalNodes{};
    float minTerminalNodes{};
    float maxLongitud{};
    float minLongitud{};
    float *maxVolumenSeccion;
    float *minVolumenSeccion;
    float *maxTamSeccion;
    float *minTamSeccion;

    float *maxPuntoAPuntoSeccion;
    float *minPuntoAPuntoSeccion;

protected:
    Eigen::Vector3f color;
public:


    neuriteG(nsol::Neurite* _neurite);
/*Metodo que esta definido en cada clase hijo, quieres pintaran lo que necesiten en la pantalla openGLWidget
con un desplazamiento de X y otro desplazamiento de Y*/
    void draw(QOpenGLWidget* windowPaint);

    //Dibujar el caudrado que la select.
     void drawSelc(QOpenGLWidget* windowPaint);

    //Devuelve las coordinates en las que se encuentra el objeto
     void coordinates();

    //Coordenadas que se desplaza el objeto
     void displacement(float x, float y);

    //Comprueba si el objeto esta selected
     bool select(QOpenGLWidget* windowPaint, float x, float y,float z);

    //Cuando pintamos el objeto desde 0, quita el boton selected en caso de que estuviera.
     bool resetSelect();

    bool isSelected();

    int getTerminalNodes() const;
    void setTerminalNodes(int terminalNodes);

    float getTam();
    void setTamMult(float t);
    
    void drawTree(QOpenGLWidget* windowPaint);

    void drawDendograma(QOpenGLWidget* windowPaint);

    void drawEsquema(QOpenGLWidget *windowPaint);

    void setAngle(float a);  
     
	void setGrosor(float a);
	
	float grosorTotal();
	
	void setMaxTerminalNodes(float a);

    float getTamTotal();
	void setMinTerminalNodes(float a);
	
	void setMaxLongitud(float a);
	
	void setMinLongitud(float a);

    void getDistacia_A_B(float* max,float* min);
	
	void setVariableGrosor(int a);


    void setVariableTam(int a);

    void setAngleHueco(float a);

    void selectSection(QOpenGLWidget* windowPaint,float x,float y);
    void draw3d(float x,float y,float z);

    float *getMaxTamSeccion() const;

    float *getMinTamSeccion() const;

    void setMaxTamSeccion(float maxTamSeccion);

    void setMinTamSeccion(float minTamSeccion);

    float *getMaxPuntoAPuntoSeccion() const;

    void setMaxPuntoAPuntoSeccion(float maxPuntoAPuntoSeccion);

    float *getMinPuntoAPuntoSeccion() const;

    void setMinPuntoAPuntoSeccion(float minPuntoAPuntoSeccion);

protected:
    virtual void putColor()=0 ;

private:
    float terminalNodesFunction();
    void variableGrosorAux(float *max,float *min);
    void variableLongitudAux(float *max_long,float *min_long);
    float getValPoint2(VarLongitud var_long, float max, float min);
    void drawCirculoAux(float modulo, bool activo);
};


#endif //HUGO_NEURITE_G_H

