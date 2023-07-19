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
    variable_longitud=VariableLongitud::unitario;
    max_volumen_seccion = new float;
    min_volumen_seccion = new float;
    max_tam_seccion = new float;
    min_tam_seccion = new float;
    max_punto_a_punto_seccion=new float;
    min_punto_a_punto_seccion=new float;

    tam=getTamTotal()/100;
    getDistacia_A_B(max_punto_a_punto_seccion,min_punto_a_punto_seccion);


}
void neurite_g::draw(QOpenGLWidget* windowPaint){
    firstSection->setDisplacementX(displacementX);
    firstSection->setDisplacementY(displacementY);
    firstSection->putColor(color);
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
		glColor3f(color.x(), color.y(), color.z());
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
    float *max=new float;
    float *min=new float;
    if(neurites_grosor==true){
        g=true;
        variableGrosorAux(max,min);

    }
		else{
			g=false;
			glLineWidth(1);
		}
		
		glBegin(GL_LINES); // Iniciar el modo de dibujo de linea
        glColor3f(1.0, 1.0, 1.0);
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
		float dif_angle=0.7;
		float distancia=std::sqrt(std::pow(mult*(x-displacementX),2)+pow(mult*(y-displacementY),2));
		hipotenusa=distancia/std::cos(0.52359878)*0.4;
		firstSection->drawSectionsTree(x,y,angle,hipotenusa,dif_angle,g,*max,*min,variable_grosor);

		if(selected){
			drawSelc(windowPaint);
		}
		glEnd();
	
	
}
void neurite_g::drawDendograma(QOpenGLWidget *windowPaint) {
    bool g;
    float *max=new float;
    float *min=new float;

    float *max_long=new float;
    float *min_long= new float;

    if(neurites_grosor==true){
        g=true;
        variableGrosorAux(max,min);
    }
    else{
        g=false;
        glLineWidth(1);
    }
    variableLongitudAux(max_long,min_long);
    glBegin(GL_LINES); // Iniciar el modo de dibujo de linea
    glColor3f(1.0, 1.0, 1.0);

    float x= getValPoint2(variable_longitud,*max_long,*min_long)*(init_x)+ displacementX+init_x;
    float y= getValPoint2(variable_longitud,*max_long,*min_long)*(init_y)+ displacementY+init_y;
    glVertex2f(displacementX+init_x, displacementY+init_y); // Especificar las coordenadas del punto a dibujar
    glVertex2f(x,y);
    glEnd();
    glBegin(GL_POINTS);
    glColor3f(color.x(), color.y(), color.z());
    glVertex2f(displacementX+init_x, displacementY+init_y);
    glVertex2f(x,y);
    glEnd();
    int n=0;
    firstSection->drawSectionsDendograma(x,y,angle_hueco,angle,terminal_nodes,&n,g,*max,*min,variable_grosor,variable_longitud,*max_long,*min_long);
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

void neurite_g::variableGrosorAux(float *max,float *min){
    float aux,n;
    switch(variable_grosor){
        case VariableEstado::Volumen:

            *max=(*max_volumen_seccion);
            *min=(*min_volumen_seccion);
            aux=(firstSection->getVolumenSeccion()-*min)/(*max-*min);
            break;
        case VariableEstado::nodosTerminales:
            *max=(firstSection->terminalNodes());
            *min=1;
            aux=(firstSection->terminalNodes()-*min)/(*max-*min);
            break;
        case VariableEstado::Tamano:
            *max=(*max_tam_seccion);
            *min=(*min_tam_seccion);
            aux=(firstSection->getTamSection()-*min)/(*max-*min);

            break;
    }
    n=aux*4 +1;
    glLineWidth(n);
}

void neurite_g::variableLongitudAux(float *max_long, float *min_long) {
    switch (variable_longitud) {
        case VariableLongitud::unitario:
            *max_long=0.25;
            *min_long=0;
            break;
        case VariableLongitud::TamanoPuntoInitPuntoFinal:
            *max_long=*max_punto_a_punto_seccion;
            *min_long=*min_punto_a_punto_seccion;
            break;
        case VariableLongitud::TamanoSeccion:
            *max_long=*max_tam_seccion;
            *min_long=*min_tam_seccion;
            break;

    }
}


void neurite_g::setVariableTam(int a){
    switch ( a )
    {
        case 0:
            variable_longitud=VariableLongitud::TamanoSeccion;
            break;
        case 1:
            variable_longitud=VariableLongitud::TamanoPuntoInitPuntoFinal;
            break;
        case 2:
            variable_longitud=VariableLongitud::unitario;
            break;
        default:
            variable_longitud=VariableLongitud::unitario;
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

void neurite_g::getDistacia_A_B(float *max,float *min){
    *max_punto_a_punto_seccion=firstSection->getTamPuntoInicialPuntoFinal();
    *min_punto_a_punto_seccion=firstSection->getTamPuntoInicialPuntoFinal();
    firstSection->getTamTotalP1_P2(max_punto_a_punto_seccion,min_punto_a_punto_seccion);
}


void neurite_g::selectSection(QOpenGLWidget* windowPaint,float x, float y) {
    firstSection->selected( windowPaint,x,y);
}

void neurite_g::draw3d(float x, float y, float z) {
   firstSection->draw3d(x,y,z);
}

float *neurite_g::getMaxTamSeccion() const {
    return max_tam_seccion;
}

float *neurite_g::getMinTamSeccion() const {
    return min_tam_seccion;
}

void neurite_g::setMaxTamSeccion(float maxTamSeccion) {
    *max_tam_seccion = maxTamSeccion;
}

void neurite_g::setMinTamSeccion(float minTamSeccion) {
    *min_tam_seccion = minTamSeccion;
}

float *neurite_g::getMaxPuntoAPuntoSeccion() const {
    return max_punto_a_punto_seccion;
}

void neurite_g::setMaxPuntoAPuntoSeccion(float maxPuntoAPuntoSeccion) {
    *max_punto_a_punto_seccion = maxPuntoAPuntoSeccion;
}

float *neurite_g::getMinPuntoAPuntoSeccion() const {
    return min_punto_a_punto_seccion;
}

void neurite_g::setMinPuntoAPuntoSeccion(float minPuntoAPuntoSeccion) {
    *min_punto_a_punto_seccion = minPuntoAPuntoSeccion;
}




float neurite_g::getValPoint2(VariableLongitud var_long,float max,float min){
    switch (var_long) {
        case VariableLongitud::TamanoSeccion:

            return (firstSection->getTamSection()-min)/(max-min)*1.4;

        case VariableLongitud::TamanoPuntoInitPuntoFinal:
            return (firstSection->getTamSection()-min)/(max-min)*1.4;

        case VariableLongitud::unitario:
            return 0.5;
        default:
            return 0.5;
    }

}