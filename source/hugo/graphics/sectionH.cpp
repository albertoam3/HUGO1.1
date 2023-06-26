//
// Created by alberto on 03/05/23.
//

#include "sectionH.h"




const double sectionH::PI = 3.14159265358979323846;

sectionH::sectionH(nsol::NeuronMorphologySection* _sec){
     sec=_sec;
}

float sectionH::getTamTotal(){
	float tam=0;
	for (nsol::Section* s : sec->children()) {
    		nsol::NeuronMorphologySection* section = dynamic_cast<nsol::NeuronMorphologySection*>(s);
			sectionH secAux(section);
			tam+=secAux.getTamTotal();
	}
	tam+=getTamSection();
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

void sectionH::drawSectionsTree(float x1, float x2,float angle,float hipotenusa,float dif_angle,bool g){

		float valorX,valorY,valorX2,valorY2;
		
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
				if(g){
					float grosor=secAux.getVolumenSeccion();
					glEnd();
					glLineWidth(grosor/50*10);
					glBegin(GL_LINES);	
				}
				glVertex2f( x1, x2); // Especificar las coordenadas del punto a dibujar
				glVertex2f(valorX,valorY);
				secAux.drawSectionsTree(valorX,valorY,angle,hipotenusa,dif_angle,g);
			}
			else{
				if(g){
					float grosor=secAux.getVolumenSeccion();
					glEnd();
					glLineWidth(grosor/50*10);
					glBegin(GL_LINES);	
				}
				glVertex2f( x1, x2); // Especificar las coordenadas del punto a dibujar
				glVertex2f(valorX2,valorY2);	
				secAux.drawSectionsTree(valorX2,valorY2,angle,hipotenusa,dif_angle,g);
			}
			i++;
		}
}

void sectionH::selected(float x, float y, float z) {

}

void sectionH::drawSectionsDendograma(float x,float y,float angle_hueco,float angle,float init_x,float init_y,float terminal_nodes,int *cont,bool g,float maxVS,float minVS) {
    int i=0;
    for (nsol::Section* s : sec->children()) {
        nsol::NeuronMorphologySection* section = dynamic_cast<nsol::NeuronMorphologySection*>(s);
        sectionH secAux(section);
        if(i==0){
            if(g) {
                float aux,n;
                aux=(getVolumenSeccion()-minVS)/(maxVS-minVS);
                n=aux*4 +1;
                glLineWidth(n);
            }
            glBegin(GL_LINES);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f( x, y);
            glVertex2f(x +init_x,y+init_y);
            glEnd();
            glPointSize(5.0);

            glBegin(GL_POINTS);
            glColor3f(0.0, 0.0, 1.0);
            glVertex2f(x, y);
            glEnd();

            secAux.drawSectionsDendograma(x+init_x,y+init_y,angle_hueco,angle,init_x,init_y,terminal_nodes,cont,g,maxVS,minVS);
        }
        else{
            (*cont)++;
            if(g){
                float aux,n;
                aux=(getVolumenSeccion()-minVS)/(maxVS-minVS);
                n=aux*4 +1;
                glLineWidth(n);
            }

            glBegin(GL_LINES);
            glColor3f(1.0, 0.0, 0.0);
            float modulo=sqrt(pow(x,2)+pow(y,2));
            glVertex2f( x, y);
            float nx=modulo*cos(angle-angle_hueco*(*cont)/terminal_nodes);
            float ny=modulo*sin(angle-angle_hueco*(*cont)/terminal_nodes);

            glVertex2f(nx,ny);

            float mod_init=sqrt(pow(init_x,2)+pow(init_y,2));
            float nix=mod_init*cos(angle-angle_hueco*(*cont)/terminal_nodes);
            float niy=mod_init*sin(angle-angle_hueco*(*cont)/terminal_nodes);


            glVertex2f(nx,ny);
            glVertex2f(nx+nix,ny+niy);


            glEnd();
            glBegin(GL_POINTS);
            glColor3f(0.0, 0.0, 1.0);
            glVertex2f(nx+nix, ny+niy);
            glEnd();



            secAux.drawSectionsDendograma(nx+nix,ny+niy,angle_hueco,angle,nix,niy,terminal_nodes,cont,g,maxVS,minVS);

        }
        i++;
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
