//
// Created by alberto on 03/05/23.
//



#include "sectionH.h"




const double sectionH::PI = 3.14159265358979323846;

sectionH::sectionH(nsol::NeuronMorphologySection* _sec){
     sec=_sec;
     selecionada=false;
     tamTotal=0;
     tamSeccion=getTamSection();
     coord_x=0;
     coord_y=0;
}

float sectionH::getTamTotal(float *max, float *min){
	float tam=0;
	for (nsol::Section* s : sec->children()) {
    		nsol::NeuronMorphologySection* section = dynamic_cast<nsol::NeuronMorphologySection*>(s);
			sectionH secAux(section);
			tam+=secAux.getTamTotal(max,min);
	}
	tam+=getTamSection();
    if(getTamSection()>(*max))
        (*max)=getTamSection();
    else if (getTamSection()<(*min))
        (*min)=getTamSection();
	return tam;
}

float sectionH::getTamSection(){
	nsol::Node* s=sec->firstNode();
	nsol::Node* a;
	bool first=true;
	float tam=0.0f;
	for(nsol::Node* node:sec->nodes()){
		if(first)
			first=false;
		else{
			a=s;
			s=node;
			tam+= distanciaEntreRegistros(s,a);
		}	
	}

	return tam;
}


float sectionH::getVolumenAcumulado(float *maxVolumenSeccion,float *minVolumenSeccion){
	float vol=0;
	for (nsol::Section* s : sec->children()) {
    		nsol::NeuronMorphologySection* section = dynamic_cast<nsol::NeuronMorphologySection*>(s);
			sectionH secAux(section);

			vol+=secAux.getVolumenAcumulado(maxVolumenSeccion,minVolumenSeccion);
	}
	vol+=getVolumenSeccion();
    if(getVolumenSeccion()>(*maxVolumenSeccion))
        (*maxVolumenSeccion)=getVolumenSeccion();
    else if (getVolumenSeccion()<(*minVolumenSeccion))
        (*minVolumenSeccion)=getVolumenSeccion();
	return vol;
}

float sectionH::getVolumenSeccion(){
	nsol::Node* s=sec->firstNode();
	nsol::Node* a;
	bool first=true;
	float tam=0.0f;
	for(nsol::Node* node:sec->nodes()){
		if(first)
			first=false;
		else{
			a=s;
			s=node;
			tam+= volumenCono(s,a);
		}	
	}
	return tam;
}



float sectionH::distanciaEntreRegistros(nsol::Node* r1, nsol::Node* r2){
		return std::sqrt( std::pow(r1->point()[0] - r2->point()[0], 2) +
        		std::pow(r1->point()[1] - r2->point()[1], 2) +
        		std::pow(r1->point()[2] - r2->point()[2], 2));
	
}

float sectionH::areaCono(nsol::Node* r1,nsol::Node* r2){
	double r=std::abs(r1->radius()-r2->radius()); 
    double g=std::sqrt(r*r+std::pow(r1->point()[0] - r2->point()[0], 2) +
        		std::pow(r1->point()[1] - r2->point()[1], 2) +
        		std::pow(r1->point()[2] - r2->point()[2], 2));
	return PI*g*(r1->radius()+r2->radius());
	
}

float sectionH::volumenCono(nsol::Node* r1,nsol::Node* r2) {

	double h=distanciaEntreRegistros(r1,r2);
	return (PI/3.)*h*(std::pow(r1->radius(),2)+std::pow(r2->radius(),2)+r1->radius()*r2->radius());
}


nsol::NeuronMorphologySection sectionH::getSection(){
	return *sec;
}

void sectionH::drawSectionsTree(float x1, float x2,float angle,float hipotenusa,float dif_angle,bool g,float max,float min,VariableEstado variable_grosor){

		float valorX,valorY,valorX2,valorY2;
		coord_x=x1;
        coord_y=x2;

		hipotenusa*=0.8;
		valorX=x1+cos(angle-1.30899694*dif_angle)*hipotenusa;
		valorY=x2+sin(angle-1.30899694*dif_angle)*hipotenusa;
		valorX2=x1+cos(angle+1.30899694*dif_angle)*hipotenusa;
		valorY2=x2+sin(angle+1.30899694*dif_angle)*hipotenusa;
		dif_angle*=0.6;

		int i=0;
		for (nsol::Section* s : sec->children()) {
			nsol::NeuronMorphologySection* section = dynamic_cast<nsol::NeuronMorphologySection*>(s);
			sectionH secAux(section);
			if(i==0){
                if(g) {
                    glEnd();
                    getLineWidth( variable_grosor, secAux, max, min);
                    glBegin(GL_LINES);
                }
				glVertex2f( x1, x2); // Especificar las coordenadas del punto a dibujar
				glVertex2f(valorX,valorY);
				secAux.drawSectionsTree(valorX,valorY,angle,hipotenusa,dif_angle,g,max,min,variable_grosor);
			}
			else{
                if(g) {
                    glEnd();
                    getLineWidth( variable_grosor, secAux, max, min);
                    glBegin(GL_LINES);
                }
				glVertex2f( x1, x2); // Especificar las coordenadas del punto a dibujar
				glVertex2f(valorX2,valorY2);	
				secAux.drawSectionsTree(valorX2,valorY2,angle,hipotenusa,dif_angle,g,max,min,variable_grosor);
			}
			i++;
		}
}

bool sectionH::selected(QOpenGLWidget* windowPaint,float x, float y) {
    if(coord_x+0.05>x && coord_x-0.05<x && coord_y+0.05>y && coord_y-0.05<y){
        QString texto="Soy la seleccionada :) ";
        seeToolTip(texto,windowPaint);
        return true;
    }else if (sec->children().size() == 2) {
          //  std::cout<<"Entro por aqui\n";
            nsol::NeuronMorphologySection *section1 = dynamic_cast<nsol::NeuronMorphologySection *>(sec->children()[0]);
            nsol::NeuronMorphologySection *section2 = dynamic_cast<nsol::NeuronMorphologySection *>(sec->children()[1]);
            sectionH secAux(section1);
            sectionH secAux2(section2);
            bool a=secAux.selected(windowPaint,x,y);
            if (a)
                return true;
            else
                return secAux2.selected(windowPaint,x,y);
    }
    else
        return false;
}

void sectionH::drawSectionsDendograma(float x,float y,float angle_hueco,float angle,float init_x,float init_y,float terminal_nodes,int *cont,bool g,float max,float min,VariableEstado variable_grosor) {
    coord_x=x;
    coord_y=y;

    if (sec->children().size() == 2) {
        nsol::NeuronMorphologySection *section1 = dynamic_cast<nsol::NeuronMorphologySection *>(sec->children()[0]);
        nsol::NeuronMorphologySection *section2 = dynamic_cast<nsol::NeuronMorphologySection *>(sec->children()[1]);

        sectionH secAux(section1);
        sectionH secAux2(section2);
        sectionH *sec1,*sec2;
        //ahora mismo se va siempre por la rama más grande, con una variable de estado podriamos decidir si lo queremos asi o queremos que siga el camino que nos dan
        if (secAux.terminalNodes()>secAux2.terminalNodes()){
            sec1=&secAux;
            sec2=&secAux2;
        }
        else{
             sec1=&secAux2;
             sec2=&secAux;
        }
        if (g) {
            getLineWidth( variable_grosor,*sec1, max, min);
        }
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(x, y);
        glVertex2f(x + init_x, y + init_y);
        glEnd();
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(x + init_x, y + init_y);
        glEnd();
        sec1->drawSectionsDendograma(x + init_x, y + init_y, angle_hueco, angle, init_x, init_y, terminal_nodes, cont,
                                      g, max, min, variable_grosor);

        (*cont)++;

        glColor3f(1.0, 0.0, 0.0);
        float modulo = sqrt(pow(x, 2) + pow(y, 2));
        float nx = modulo * cos(angle - angle_hueco * (*cont) / terminal_nodes);
        float ny = modulo * sin(angle - angle_hueco * (*cont) / terminal_nodes);

        drawArco( x, y, nx, ny, angle, angle_hueco,cont, terminal_nodes, modulo);
        if (g) {
            getLineWidth( variable_grosor,*sec2, max, min);
        }
        glBegin(GL_LINES);

        float mod_init = sqrt(pow(init_x, 2) + pow(init_y, 2));
        float nix = mod_init * cos(angle - angle_hueco * (*cont) / terminal_nodes);
        float niy = mod_init * sin(angle - angle_hueco * (*cont) / terminal_nodes);

        glVertex2f(nx, ny);
        glVertex2f(nx + nix, ny + niy);

        glEnd();
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(nx + nix, ny + niy);
        glEnd();

        sec2->drawSectionsDendograma(nx + nix, ny + niy, angle_hueco, angle, nix, niy, terminal_nodes, cont, g, max,
                                      min, variable_grosor);
    }
}

float sectionH::terminalNodes() {
    float terminal=0;

    if(sec->children().empty()){
        terminal++;
    }

    for (nsol::Section* s : sec->children()) {
        nsol::NeuronMorphologySection* section = dynamic_cast<nsol::NeuronMorphologySection*>(s);
        sectionH secAux(section);
        terminal+=secAux.terminalNodes();
    }
    return terminal;
}


void sectionH::drawArco(float x1,float y1,float x2,float y2,float angle,float angle_hueco, int* cont,float terminal_nodes,float modulo){
    glLineWidth(1);
    glBegin(GL_LINES);
    float angle_aux = std::atan2(y1, x1);
    if (angle_aux <  angle - angle_hueco * (*cont)/terminal_nodes)
        angle_aux += 2 * 3.14159;
    glVertex2f(x1, y1);
    for (float i = angle_aux; i >= angle - angle_hueco * (*cont) / terminal_nodes; i -= 0.005) {
        float xAux = modulo * cosf(i); // Calcula la coordenada x
        float yAux = modulo * sinf(i); // Calcula la coordenada y
        glVertex2f(xAux + 0, yAux + 0); // Dibuja el vértice en la posición (x + cx, y + cy)
        glVertex2f(xAux + 0, yAux + 0); // Dibuja el vértice en la posición (x + cx, y + cy)
    }
    glVertex2f(x2, y2);
    glEnd();


}

void sectionH::getLineWidth(VariableEstado variable_grosor,sectionH sec,float max,float min){
    float aux, n;
    switch (variable_grosor) {
        case VariableEstado::Volumen:
            aux = (sec.getVolumenSeccion() - min) / (max - min);
            break;
        case VariableEstado::nodosTerminales:
            aux = (sec.terminalNodes() - min) / (max - min);
            break;
        case VariableEstado::Tamano:
            aux = (sec.getTamSection() - min) / (max - min);
            break;
    }
    n = aux * 4 + 1;
    glLineWidth(n);

}

void sectionH::coordinates() {

}
void sectionH::seeToolTip(QString texto,QOpenGLWidget *windowPaint){
    QToolTip::showText(QCursor::pos(), texto, windowPaint, QRect(), 500);
}