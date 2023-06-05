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


float sectionH::getVolumenAcumulado(){
	float vol=0;
	for (nsol::Section* s : sec->children()) {
    		nsol::NeuronMorphologySection* section = dynamic_cast<nsol::NeuronMorphologySection*>(s);
			sectionH secAux(section);
			vol+=secAux.getVolumenAcumulado();
	}
	vol+=getVolumenSeccion();
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

void sectionH::drawSections(float x1, float x2, float tam_mult,float angle,float hipotenusa,float dif_angle){
		
	if(sec->children().size()==2){
		float valorX,valorY,valorX2,valorY2;
		
		hipotenusa*=0.8;
		valorX=x1+cos(angle-1.30899694*dif_angle)*hipotenusa;
		valorY=x2+sin(angle-1.30899694*dif_angle)*hipotenusa;
		valorX2=x1+cos(angle+1.30899694*dif_angle)*hipotenusa;
		valorY2=x2+sin(angle+1.30899694*dif_angle)*hipotenusa;
		dif_angle*=0.6;
			
		glVertex2f( x1, x2); // Especificar las coordenadas del punto a dibujar
		glVertex2f(valorX,valorY);
		
		glVertex2f( x1, x2); // Especificar las coordenadas del punto a dibujar
		glVertex2f(valorX2,valorY2);	
		int i=0;
		for (nsol::Section* s : sec->children()) {
			nsol::NeuronMorphologySection* section = dynamic_cast<nsol::NeuronMorphologySection*>(s);
			sectionH secAux(section);
			if(i==0){
				secAux.drawSections(valorX,valorY,tam_mult,angle,hipotenusa,dif_angle);
			}
			else{
				secAux.drawSections(valorX2,valorY2,tam_mult,angle,hipotenusa,dif_angle);
			}
			i++;
		}

	}
	
}
