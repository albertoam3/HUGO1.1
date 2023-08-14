    
#include "neuronG.h"

#include <iostream>

const float pi = 3.14159265359;

neuronG::neuronG(nsol::Neuron *_neu){
    neu=_neu;
    ax.push_back(new axonG(neu->morphology()->axon()));
    tamMaxNeurite=ax[0]->getTam();
    
    som=new somaG(neu->morphology()->soma());
    const auto &den=neu->morphology()->dendrites();
    for (auto &dendrite: *den) {
        dends.push_back(*new dendriteG(dendrite));
        dends[dends.size()-1].setTDendriteType(static_cast<dendriteG::TDendriteType>(dendrite->dendriteType()));
        
    }
    for (auto &d :dends){
    	if(d.getTam() > tamMaxNeurite)
            tamMaxNeurite=d.getTam();
    		
    		
    }

    selected=false;
    displacementX=0;
    displacementY=0;
    initX=0;
    initY=0;
    coordinates();
    name=neu->gid();
    angleXTam=false;
    tree=0;
    dendograma=0;
    circle=0;
    esquema=0;
    neuritesGros=0;
    neuritesTam=0;
  

	tamNeurite();
    grosorNeurite();
	calculateMaxMinNodosTerminales();
	calculateMaxMinLongitud();

    tamMaxSeccion();
    tamMaxP1P2Seccion();





}
void neuronG::draw(QOpenGLWidget* windowPaint){

}

void neuronG::draw(QOpenGLWidget* windowPaint, bool dim){
   dimension=dim;
   if(dimension==false){
		draw2D(windowPaint);
    }
    else{
		draw3D(windowPaint);
    }
}

void neuronG::draw2D(QOpenGLWidget* windowPaint){
	
     for(auto & dend : dends){
				
                dend.setNeuritesTam(neuritesTam);
                dend.setNeuritesGrosor(neuritesGros);
                dend.setDisplacements(displacementX,displacementY);
                dend.setTree(tree);
                dend.setDendograma(dendograma);
                dend.setEsquema(esquema);
                dend.setCircle(circle);
                
     }
     ax[0]->setNeuritesTam(neuritesTam);
     ax[0]->setNeuritesGrosor(neuritesGros);
     ax[0]->setDisplacements(displacementX,displacementY);
     ax[0]->setTree(tree);

     ax[0]->setDendograma(dendograma);

     ax[0]->setEsquema(esquema);
     ax[0]->setCircle(circle);

	 (angleXTam == false) ? auxDrawAngleEqual(windowPaint) : auxDrawAngleTam(windowPaint);
	

     som->setDisplacements(displacementX, displacementY);
     som->coordInitials(initX, initY);
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

void neuronG::draw3D(QOpenGLWidget* windowPaint){
	float x=0;
	float y=0;
	float z=0;
	int i=0;
    	for(nsol::Node* n: neu->morphology()->soma()->nodes()){
    		glVertex3f(n->point()[0]/100,n->point()[1]/100,n->point()[2]/100);
    	}

        for(dendriteG d: dends){
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

void neuronG::drawSelc(QOpenGLWidget* windowPaint){
    glLineWidth(4.0);
    glBegin(GL_LINES);

    glColor3f(0.7f, 0.1f, 0.1f);
    glVertex2f(maxX, maxY);
    glVertex2f(maxX, minY);

    glVertex2f(maxX, maxY);
    glVertex2f(minX, maxY);

    glVertex2f(minX, maxY);
    glVertex2f(minX, minY);

    glVertex2f(maxX, minY);
    glVertex2f(minX, minY);
    glEnd();
}


void neuronG::coordinates(){
    minX= -neu->morphology()->soma()->meanRadius() + displacementX + initX;
    minY= -neu->morphology()->soma()->meanRadius() + displacementY + initY;
    maxX= neu->morphology()->soma()->meanRadius() + displacementX + initX;
    maxY= neu->morphology()->soma()->meanRadius() + displacementY + initY;
    minZ= displacementZ - 0.03;
    maxZ= displacementZ + 0.03;
}


bool neuronG::select(QOpenGLWidget* windowPaint, float x, float y, float z)  {
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

bool neuronG::resetSelect() {
    selected=false;
    ax[0]->resetSelect();
    som->resetSelect();

    for (int i = 0; i < dends.size(); i++) {
        dends[i].resetSelect();
    }
    return selected;
}

bool neuronG::isSelected()  {
    return selected;
}

float neuronG::angleEqual(){
    return 2*pi/(dends.size() +ax.size());
}
float neuronG::angleTam() {
    int n=0;
    for(int i=0;i<dends.size();i++){
        n+=dends[i].getTerminalNodes();
    }
    for(int i=0;i<ax.size();i++){
        n+=ax[i]->getTerminalNodes();
    }
    return n;
}

void neuronG::auxDrawAngleEqual(QOpenGLWidget* windowPaint) {
    float an= angleEqual();
    float aux=an;
    float radio=som->getRadio();
    ax[0]->setDisplacements(displacementX, displacementY);
    ax[0]->coordInitials(initX + radio * cos(an), initY + radio * sin(an));
    ax[0]->setAngle(an);
    ax[0]->setScala(scala);
    ax[0]->setAngleHueco(aux);
    ax[0]->draw(windowPaint);

    an+=aux;
    for (auto & item : dends) {
        item.setDisplacements(displacementX, displacementY);
        item.coordInitials(initX + radio * cos(an), initY + radio * sin(an));
        item.setScala(scala);
        item.setAngle(an);
        item.setAngleHueco(aux);
        item.draw(windowPaint);
        an+=aux;
    }

}
void neuronG::auxDrawAngleTam(QOpenGLWidget *windowPaint) {
    float angle_anterior=0;


    float radio=som->getRadio();
    float i=0;

    i+=ax[0]->getTerminalNodes();
    ax[0]->setDisplacements(displacementX, displacementY);
    ax[0]->setAngle(i / angleTam() * 2 * pi);
    ax[0]->coordInitials(initX + radio * cos(i / angleTam() * 2 * pi), initY + radio * sin(i / angleTam() * 2 * pi));
    ax[0]->setAngleHueco(i / angleTam() * 2 * pi - angle_anterior);
    angle_anterior= i / angleTam() * 2 * pi;
    ax[0]->draw(windowPaint);

    for(auto & item: dends){
        item.setDisplacements(displacementX,displacementY);
        i+=item.getTerminalNodes();
        item.setAngle(i / angleTam() * 2 * pi);
        item.coordInitials(initX + radio * cos(i / angleTam() * 2 * pi), initY + radio * sin(i / angleTam() * 2 * pi));
        item.setScala(scala);
        item.setAngleHueco(i / angleTam() * 2 * pi - angle_anterior);
        angle_anterior= i / angleTam() * 2 * pi;
        item.draw(windowPaint);
    }

}

void neuronG::tamNeurite(){
		ax[0]->setTamMult(2*(ax[0]->getTam() / tamMaxNeurite));
	  	for (auto & item : dends) {
        		item.setTamMult(2*(item.getTam() / tamMaxNeurite));
	
		}
	
}
void neuronG::grosorNeurite(){
		ax[0]->setGrosor(ax[0]->grosorTotal()/100);	
	  	for (auto & item : dends) {
        		item.setGrosor(item.grosorTotal()/100);
	
		}

}
	
	

//Falta de implementar
float neuronG::getTam(){
	return 0;
}

void neuronG::displacementN(float x, float y, float z){
	graphicObjects::displacement(x, y, z);
}


void neuronG::setNeuritesVariableGrosor(float a){
		ax[0]->setVariableGrosor(a);	
	  	for (auto & item : dends) {
        		item.setVariableGrosor(a);
        	}
}




void neuronG::setNeuritesVariableTam(float a){
    ax[0]->setVariableTam(a);
    for (auto & item : dends) {
        item.setVariableTam(a);
    }
}


void neuronG::calculateMaxMinNodosTerminales(){
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

void neuronG::calculateMaxMinLongitud(){
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

void neuronG::selectSection(QOpenGLWidget* windowPaint, float x, float y) {
    ax[0]->selectSection(windowPaint,x,y);
    for (auto & item : dends) {
        item.selectSection(windowPaint,x,y);
    }
}

void neuronG::tamMaxSeccion() {
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

void neuronG::tamMaxP1P2Seccion() {
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


	

