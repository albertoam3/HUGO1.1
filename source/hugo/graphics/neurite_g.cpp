//
// Created by alberto on 29/05/23.
//

#include "neurite_g.h"
constexpr float pint=0.5f;

neurite_g::neurite_g(nsol::Neurite* _neurite){
    this->neurite=_neurite;
    name="neurite";
    displacementX=0;
    displacementY=0;

    firstSection=new sectionH(this->neurite->firstSection());
    terminal_nodes=this->terminalNodes();
    scala=1;

    tree=false;
    neurites_grosor=false;
    variable_grosor=VariableEstado::Tamano;
    max_volumen_seccion = new float;
    min_volumen_seccion = new float;
    max_tam_seccion = new float;
    min_tam_seccion = new float;
    tam=firstSection->getTamTotal(max_tam_seccion,min_tam_seccion)/100;


}
void neurite_g::draw(QOpenGLWidget* windowPaint){
    
    if(tree){
		drawTree(windowPaint);
	}else if(dendograma){
        drawDendograma((windowPaint));

    }
	else{
		
		float aux,n;
		if(neurites_grosor){
			switch(variable_grosor){
				case VariableEstado::Tamano:
					aux=(tam-min_longitud)/(max_longitud-min_longitud);
					n=aux*9 +1;
					glLineWidth(n);
					break;
				case VariableEstado::Volumen:
					glLineWidth(grosor);
					break;
				case VariableEstado::nodosTerminales:
					aux=(terminal_nodes-min_terminal_nodes)/(max_terminal_nodes-min_terminal_nodes);
					n=aux*9 +1;
					
					glLineWidth(n);
					break;
				
			}
		}
		
		else{
			
			glLineWidth(1);		
			
		}

		glBegin(GL_LINES); // Iniciar el modo de dibujo de linea
		glColor3f(1.0, color(), 0.0); 
		glVertex2f( displacementX+init_x, displacementY+init_y); // Especificar las coordenadas del punto a dibujar
		
		if(neurites_tam)
			glVertex2f(tam_mult*(init_x)+displacementX+init_x,tam_mult*(init_y)+ displacementY+init_y);
		else
			glVertex2f(2*(init_x)+displacementX+init_x,2*(init_y)+ displacementY+init_y);
			
		if(selected){
			drawSelc(windowPaint);
		}
		glEnd();
	}  
}
void neurite_g::drawSelc(QOpenGLWidget* windowPaint){
    glLineWidth(4.0);
    glBegin(GL_LINES);
    coordinates();
    glColor3f(0.0f, 0.3f, 0.1f);
    glVertex2f(max_X, max_Y);
    glVertex2f(max_X, min_Y);

    glVertex2f(max_X, max_Y);
    glVertex2f(min_X, max_Y);

    glVertex2f(min_X, max_Y);
    glVertex2f(min_X, min_Y);

    glVertex2f(max_X, min_Y);
    glVertex2f(min_X, min_Y);
    glEnd();

}


//Devuelve las coordinates en las que se encuentra el objeto
void neurite_g::coordinates(){
	float mult;
	
	if(neurites_tam){
		mult=tam_mult;
	}
	else{
		mult=2;
		
	}

    if(displacementX+init_x >displacementX+init_x+mult*(init_x)){
		max_X=displacementX+init_x+0.05;
		min_X=displacementX+init_x+mult*(displacementX+init_x)-0.05;
	}
	else{
		min_X=displacementX+init_x-0.05;
		max_X=displacementX+init_x+mult*(init_x)+0.05;
	}
	
	if(displacementY+init_y >displacementY+init_y+mult*(displacementY+init_y)){
		max_Y=displacementY+init_y+0.05;
		min_Y=displacementY+init_y+mult*(init_y)-0.05;
	}
	else{
		min_Y=displacementY+init_y-0.05;
		max_Y=displacementY+init_y+mult*(init_y)+0.05;
	}
    min_Z=displacementZ-0.03;
    max_Z=displacementZ+0.03;
}



//Comprueba si el objeto esta selected
bool neurite_g::select(QOpenGLWidget* windowPaint, float x, float y,float z){
    coordinates();
    //firstSection->selected(x,y,z);

    if(x>min_X && x<max_X && y>min_Y && y<max_Y)
        selected=!selected;
    if(coord_include(x,y)){
        drawSelc(windowPaint);
        QString texto="Axon,nodos terminales: ";
        texto+=QString::number(getTerminalNodes());
        seeToolTip(texto,windowPaint);
    }
    return selected;
}

//Cuando pintamos el objeto desde 0, quita el boton selected en caso de que estuviera.
bool neurite_g::resetSelect() {
    selected = false;
    return selected;

}

bool neurite_g::isSelected() {
    return selected;
}

int neurite_g::getTerminalNodes() const {
    return terminal_nodes;
}

void neurite_g::setTerminalNodes(int terminalNodes) {
    terminal_nodes = terminalNodes;
}

float neurite_g::getTam(){
	return tam;
}

void neurite_g::setTamMult(float t){
	tam_mult=t;
}


void neurite_g::drawTree(QOpenGLWidget* windowPaint){
		
		bool g;
    float max,min=0;
    if(neurites_grosor==true){
        g=true;
        float aux,n;
        switch(variable_grosor){
            case VariableEstado::Volumen:

                max=(*max_volumen_seccion);
                min=(*min_volumen_seccion);
                aux=(firstSection->getVolumenSeccion()-min)/(max-min);
                break;
            case VariableEstado::nodosTerminales:
                max=(firstSection->terminalNodes());
                min=1;
                aux=(firstSection->terminalNodes()-min)/(max-min);
                break;
            case VariableEstado::Tamano:
                max=(*max_tam_seccion);
                min=(*min_tam_seccion);
                aux=(firstSection->getTamSection()-min)/(max-min);

                break;
        }
        n=aux*4 +1;
        glLineWidth(n);

    }
		else{
			g=false;
			glLineWidth(1);
		}
		
		glBegin(GL_LINES); // Iniciar el modo de dibujo de linea
		glColor3f(1.0, color(), 0.0); 
		float mult;
		if(neurites_tam)
			mult=tam_mult*0.75;
		else
			mult=1.5;
		
		float x=mult*(init_x)+ displacementX+init_x;
		float y=mult*(init_y)+ displacementY+init_y;
		glVertex2f(displacementX+init_x, displacementY+init_y); // Especificar las coordenadas del punto a dibujar
		glVertex2f(x,y);

		float hipotenusa=0;
		float dif_angle=dif_angle=0.7;
		float distancia=std::sqrt(std::pow(mult*(x-displacementX),2)+pow(mult*(y-displacementY),2));
		hipotenusa=distancia/std::cos(0.52359878)*0.4;
		firstSection->drawSectionsTree(x,y,angle,hipotenusa,dif_angle,g,max,min,variable_grosor);

		if(selected){
			drawSelc(windowPaint);
		}
		glEnd();
	
	
}
void neurite_g::drawDendograma(QOpenGLWidget *windowPaint) {
    bool g;
    float max,min=0;
    if(neurites_grosor==true){
        g=true;
        float aux,n;
        switch(variable_grosor){
            case VariableEstado::Volumen:

                max=(*max_volumen_seccion);
                min=(*min_volumen_seccion);
                aux=(firstSection->getVolumenSeccion()-min)/(max-min);
                break;
            case VariableEstado::nodosTerminales:
                max=(firstSection->terminalNodes());
                min=1;
                aux=(firstSection->terminalNodes()-min)/(max-min);
                break;
            case VariableEstado::Tamano:
                max=(*max_tam_seccion);
                min=(*min_tam_seccion);
                aux=(firstSection->getTamSection()-min)/(max-min);

                break;
        }
        n=aux*4 +1;
        glLineWidth(n);

    }
    else{
        g=false;
        glLineWidth(1);
    }
    glBegin(GL_LINES); // Iniciar el modo de dibujo de linea
    glColor3f(1.0, color(), 0.0);
    float mult;
    if(neurites_tam)
        mult=tam_mult*0.40;
    else
        mult=0.6;

    float x=mult*(init_x)+ displacementX+init_x;
    float y=mult*(init_y)+ displacementY+init_y;
    glVertex2f(displacementX+init_x, displacementY+init_y); // Especificar las coordenadas del punto a dibujar
    glVertex2f(x,y);
    glEnd();
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(displacementX+init_x, displacementY+init_y);
    glVertex2f(x,y);
    glEnd();
    int n=0;
    firstSection->drawSectionsDendograma(x,y,angle_hueco,angle,init_x*0.5,init_y*0.5,terminal_nodes,&n,g,max,min,variable_grosor);
}






void neurite_g::setAngle(float a){
	
	angle=a;
	
}	

void neurite_g::setGrosor(float a){
	grosor=a;
}

float neurite_g::grosorTotal(){
    *max_volumen_seccion=firstSection->getVolumenSeccion();
    *min_volumen_seccion=firstSection->getVolumenSeccion();
	return firstSection->getVolumenAcumulado(max_volumen_seccion,min_volumen_seccion);
	
}
void neurite_g::setVariableGrosor(int a){
	
  switch ( a )
      {
         case 0:
            variable_grosor=VariableEstado::Tamano;
            break;
         case 1:
            variable_grosor=VariableEstado::Volumen;
            break;
         case 2:
			variable_grosor=VariableEstado::nodosTerminales;
			break;
         default:
			variable_grosor=VariableEstado::Tamano;
      }
	
}




void neurite_g::setMaxTerminalNodes(float a){
	
	max_terminal_nodes=a;
}

void neurite_g::setMinTerminalNodes(float a){
	
	min_terminal_nodes=a;
}
	

void neurite_g::setMaxLongitud(float a){
	
	max_longitud=a;
}

void neurite_g::setMinLongitud(float a){
	
	min_longitud=a;
}

void neurite_g::setAngleHueco(float a) {
    angle_hueco=a;
}

float neurite_g::terminalNodes() {
        return firstSection->terminalNodes();
}

float neurite_g::getTamTotal() {
    *max_tam_seccion=firstSection->getTamSection();
    *min_tam_seccion=firstSection->getTamSection();
    return firstSection->getTamTotal(max_tam_seccion,min_tam_seccion);
}

void neurite_g::selectSection(QOpenGLWidget* windowPaint,float x, float y) {
    firstSection->selected( windowPaint,x,y);
}

	
