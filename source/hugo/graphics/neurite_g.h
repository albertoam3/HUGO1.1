//
//
// Created by alberto on 29/05/23.
//

#ifndef HUGO_NEURITE_G_H
#define HUGO_NEURITE_G_H

#include "graphic_objects.h"
#include "nsol/nsol.h"
#include "sectionH.h"
#include <QLineEdit>


enum class VariableEstado
  {
    Tamano= 0 ,
    Volumen,
    nodosTerminales
  };


class neurite_g : public graphic_objects{
private:
    nsol::Neurite *neurite;
    float terminal_nodes;
    float angle{};
    float angle_hueco;
    float dist{};
    sectionH* firstSection;
    float tam;
    float tam_mult{};
    float grosor{};
    VariableEstado variable_grosor;
    float max_terminal_nodes{};
    float min_terminal_nodes{};
    float max_longitud{};
    float min_longitud{};
    

public:


    neurite_g(nsol::Neurite* _neurite);
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

    void setAngle(float a);  
     
	void setGrosor(float a);
	
	float grosorTotal();
	
	void setMaxTerminalNodes(float a);
	
	void setMinTerminalNodes(float a);
	
	void setMaxLongitud(float a);
	
	void setMinLongitud(float a);
	
	
	void setVariableGrosor(int a);

    void setAngleHueco(float a);
   
protected:   
    virtual float color()=0 ;
};


#endif //HUGO_NEURITE_G_H

