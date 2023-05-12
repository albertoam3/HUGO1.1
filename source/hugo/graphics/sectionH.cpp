//
// Created by alberto on 03/05/23.
//

#include "sectionH.h"
#include "math.h"

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
			tam+= std::sqrt( std::pow(s->point()[0] - a->point()[0], 2) +
        		std::pow(s->point()[1] - a->point()[1], 2) +
        		std::pow(s->point()[2] - a->point()[2], 2));
		}	
	
	}
	return tam;
}


nsol::NeuronMorphologySection sectionH::getSection(){

	return *sec;
}
