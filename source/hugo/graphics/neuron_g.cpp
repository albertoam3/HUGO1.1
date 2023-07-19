    
#include "neuron_g.h"

#include <iostream>

const float pi = 3.14159265359;

neuron_g::neuron_g(nsol::Neuron *_neu){
    neu=_neu;
    ax.push_back(new axon_g(neu->morphology()->axon()));
    tam_max_neurite=ax[0]->getTam();
    
    som=new soma_g(neu->morphology()->soma());
    const auto &den=neu->morphology()->dendrites();
    for (auto &dendrite: *den) {
        dends.push_back(*new dendrite_g(dendrite));
        dends[dends.size()-1].setTDendriteType(static_cast<dendrite_g::TDendriteType>(dendrite->dendriteType()));
        
    }
    for (auto &d :dends){
    	if(d.getTam()>tam_max_neurite)
    		tam_max_neurite=d.getTam();
    		
    		
    }

    selected=false;
    displacementX=0;
    displacementY=0;
    init_x=0;
    init_y=0;
    coordinates();
    name=neu->gid();
    angleXTam=false;
    tree=0;
    dendograma=0;
    neurites_grosor=0;
    neurites_tam=0;
  

	tamNeurite();
    grosorNeurite();
	calculateMaxMinNodosTerminales();
	calculateMaxMinLongitud();

    tam_max_seccion();
    tam_max_p1_p2_seccion();





}
void neuron_g::draw(QOpenGLWidget* windowPaint){

}

void neuron_g::draw(QOpenGLWidget* windowPaint,bool dim){
   dimension=dim;
   if(dimension==false){
		draw2D(windowPaint);
    }
    else{
		draw3D(windowPaint);
    }
}

void neuron_g::draw2D(QOpenGLWidget* windowPaint){
	
     for(auto & dend : dends){
				
                dend.setNeuritesTam(neurites_tam);
                dend.setNeuritesGrosor(neurites_grosor);
                dend.setDisplacements(displacementX,displacementY);
                dend.setTree(tree);
                dend.setDendograma(dendograma);
                
     }
     ax[0]->setNeuritesTam(neurites_tam);
     ax[0]->setNeuritesGrosor(neurites_grosor);
     ax[0]->setDisplacements(displacementX,displacementY);
     ax[0]->setTree(tree);

     ax[0]->setDendograma(dendograma);
	 (angleXTam == false) ? auxDrawAngleEqual(windowPaint) : auxDrawAngleTam(windowPaint);
	

     som->setDisplacements(displacementX, displacementY);
     som->coordInitials(init_x, init_y);
     som->draw(windowPaint);

     coordinates();
     if(selected) {
        for(auto & dend : dends){
            if(dend.isSelected())
                dend.drawSelc(windowPaint);
        }
        if (ax[0]->isSelected())
            ax[0]->drawSelc(windowPaint);
        else if (som->isSelected())
            som->drawSelc(windowPaint);

     }

}

void neuron_g::draw3D(QOpenGLWidget* windowPaint){
	float x=0;
	float y=0;
	float z=0;
	int i=0;
    	for(nsol::Node* n: neu->morphology()->soma()->nodes()){
    		glVertex3f(n->point()[0]/100,n->point()[1]/100,n->point()[2]/100);
    	}

        for(dendrite_g d: dends){
            i++;
            if(i%1==0){
                z = (z == 0) ? 1 : 0;
            }
            if(i%2==0){
                y = (y == 0) ? 1 : 0;
            }
            if(i%4==0){
                x = (x == 0) ? 1 : 0;
            }
            if(i==8){
                x=0.9f;
                y=0.5f;
                z=0.0f;
            }
            d.draw3d(x,y,z);
        }
        ax[0]->draw3d(0.5,0.3,1.0);
}

void neuron_g::drawSelc(QOpenGLWidget* windowPaint){
    glLineWidth(4.0);
    glBegin(GL_LINES);

    glColor3f(0.7f, 0.1f, 0.1f);
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


void neuron_g::coordinates(){
    min_X= -neu->morphology()->soma()->meanRadius() + displacementX + init_x;
    min_Y= -neu->morphology()->soma()->meanRadius() + displacementY + init_y;
    max_X= neu->morphology()->soma()->meanRadius() + displacementX + init_x;
    max_Y= neu->morphology()->soma()->meanRadius() + displacementY + init_y;
    min_Z=displacementZ-0.03;
    max_Z=displacementZ+0.03;
}


bool neuron_g::select(QOpenGLWidget* windowPaint, float x, float y,float z)  {
    coordinates();
    if(!selected){
        for (auto &dend: dends)
            if (dend.select(windowPaint, x, y,z)) {
                selected = true;
                break;
            }
        if ( !selected && ax[0]->select(windowPaint, x, y,z) ) {
            selected = true;
        }
        else if (!selected && som->select(windowPaint, x, y,z)) {
            selected = true;
        } 
    }
    else {
        for (auto &dend: dends)
            if (dend.isSelected()) {
                selected = dend.select(windowPaint, x, y,z);
                break;
            }
        if (ax[0]->isSelected())
            selected = ax[0]->select(windowPaint, x, y,z);
        else if (som->isSelected())
            selected = som->select(windowPaint, x, y,z);

    }
    return selected;
}

bool neuron_g::resetSelect() {
    selected=false;
    ax[0]->resetSelect();
    som->resetSelect();

    for (int i = 0; i < dends.size(); i++) {
        dends[i].resetSelect();
    }
    return selected;
}

bool neuron_g::isSelected()  {
    return selected;
}

float neuron_g::angle_equal(){
    return 2*pi/(dends.size() +ax.size());
}
float neuron_g::angle_tam() {
    int n=0;
    for(int i=0;i<dends.size();i++){
        n+=dends[i].getTerminalNodes();
    }
    for(int i=0;i<ax.size();i++){
        n+=ax[i]->getTerminalNodes();
    }
    return n;
}

void neuron_g::auxDrawAngleEqual(QOpenGLWidget* windowPaint) {
    float an=angle_equal();
    float aux=an;
    float radio=som->getRadio();
    ax[0]->setDisplacements(displacementX, displacementY);
    ax[0]->coordInitials(init_x+radio*cos(an), init_y+radio*sin(an));
    ax[0]->setAngle(an);
    ax[0]->setScala(scala);
    ax[0]->setAngleHueco(aux);
    ax[0]->draw(windowPaint);

    an+=aux;
    for (auto & item : dends) {
        item.setDisplacements(displacementX, displacementY);
        item.coordInitials(init_x+radio*cos(an), init_y+radio*sin(an));
        item.setScala(scala);
        item.setAngle(an);
        item.setAngleHueco(aux);
        item.draw(windowPaint);
        an+=aux;
    }

}
void neuron_g::auxDrawAngleTam(QOpenGLWidget *windowPaint) {
    float angle_anterior=0;


    float radio=som->getRadio();
    float i=0;

    i+=ax[0]->getTerminalNodes();
    ax[0]->setDisplacements(displacementX, displacementY);
    ax[0]->setAngle(i/angle_tam()*2*pi);
    ax[0]->coordInitials(init_x+radio*cos(i/angle_tam()*2*pi), init_y+radio*sin(i/angle_tam()*2*pi));
    ax[0]->setAngleHueco(i/angle_tam()*2*pi-angle_anterior);
    angle_anterior=i/angle_tam()*2*pi;
    ax[0]->draw(windowPaint);

    for(auto & item: dends){
        item.setDisplacements(displacementX,displacementY);
        i+=item.getTerminalNodes();
        item.setAngle(i/angle_tam()*2*pi);
        item.coordInitials(init_x+radio*cos(i/angle_tam()*2*pi),init_y+radio*sin(i/angle_tam()*2*pi));
        item.setScala(scala);
        item.setAngleHueco(i/angle_tam()*2*pi-angle_anterior);
        angle_anterior=i/angle_tam()*2*pi;
        item.draw(windowPaint);
    }

}

void neuron_g::tamNeurite(){
		ax[0]->setTamMult(2*(ax[0]->getTam()/tam_max_neurite));	
	  	for (auto & item : dends) {
        		item.setTamMult(2*(item.getTam()/tam_max_neurite));
	
		}
	
}
void neuron_g::grosorNeurite(){
		ax[0]->setGrosor(ax[0]->grosorTotal()/100);	
	  	for (auto & item : dends) {
        		item.setGrosor(item.grosorTotal()/100);
	
		}

}
	
	

//Falta de implementar
float neuron_g::getTam(){
	return 0;
}

void neuron_g::displacementN(float x,float y,float z){
	graphic_objects::displacement(x,y,z);
}


void neuron_g::setNeuritesVariableGrosor(float a){
		ax[0]->setVariableGrosor(a);	
	  	for (auto & item : dends) {
        		item.setVariableGrosor(a);
        	}
}




void neuron_g::setNeuritesVariableTam(float a){
    ax[0]->setVariableTam(a);
    for (auto & item : dends) {
        item.setVariableTam(a);
    }
}


void neuron_g::calculateMaxMinNodosTerminales(){
	int aux=ax[0]->getTerminalNodes();
	int max=aux;
	int min=aux;
	
	for (auto & item : dends) {
			aux=item.getTerminalNodes();
			if(aux>max){
					max=aux;
			}
			if(aux<min){
					min=aux;
			}
       }
       
       ax[0]->setMaxTerminalNodes(max);
       ax[0]->setMinTerminalNodes(min);
       for (auto & item : dends) {
       		item.setMaxTerminalNodes(max);
       		item.setMinTerminalNodes(min);
       	}	
}

void neuron_g::calculateMaxMinLongitud(){
	float aux=ax[0]->getTam();
	float max=aux;
	float min=aux;
	
	for (auto & item : dends) {
			aux=item.getTam();
			if(aux>max){
					max=aux;
			}
			if(aux<min){
					min=aux;
			}
       }
       
       ax[0]->setMaxLongitud(max);
       ax[0]->setMinLongitud(min);
       for (auto & item : dends) {
       		item.setMaxLongitud(max);
       		item.setMinLongitud(min);
       	}	
}

void neuron_g::selectSection(QOpenGLWidget* windowPaint,float x, float y) {
    ax[0]->selectSection(windowPaint,x,y);
    for (auto & item : dends) {
        item.selectSection(windowPaint,x,y);
    }
}

void neuron_g::tam_max_seccion() {
    float max,min;
    max=*ax[0]->getMaxTamSeccion();
    min=*ax[0]->getMinTamSeccion();
    for (auto & item : dends) {
        if(max<*item.getMaxTamSeccion())
            max=*item.getMaxTamSeccion();
        if(min>*item.getMinTamSeccion())
            min=*item.getMinTamSeccion();
    }

    ax[0]->setMaxTamSeccion(max);
    ax[0]->setMinTamSeccion(min);
    for (auto & item : dends) {
        item.setMaxTamSeccion(max);
        item.setMinTamSeccion(min);
    }

}

void neuron_g::tam_max_p1_p2_seccion() {
    float max,min;
    max=*ax[0]->getMaxPuntoAPuntoSeccion();
    min=*ax[0]->getMinPuntoAPuntoSeccion();
    for (auto & item : dends) {
        if(max<*item.getMaxPuntoAPuntoSeccion())
            max=*item.getMaxPuntoAPuntoSeccion();
        if(min>*item.getMinPuntoAPuntoSeccion())
            min=*item.getMinPuntoAPuntoSeccion();
    }

    ax[0]->setMaxPuntoAPuntoSeccion(max);
    ax[0]->setMinPuntoAPuntoSeccion(min);
    for (auto & item : dends) {
        item.setMaxPuntoAPuntoSeccion(max);
        item.setMinPuntoAPuntoSeccion(min);
    }
}


	

