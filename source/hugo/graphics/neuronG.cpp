    
#include "neuronG.h"

#include <iostream>

const float pi = 3.14159265359;

neuronG::neuronG(nsol::Neuron *_neu){
    neu=_neu;
    if(neu->morphology()->axon()!= nullptr) {
        ax.push_back(new axonG(neu->morphology()->axon()));
        tamMaxNeurite = ax[0]->getTam();
    }
    
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
    varPosDend=VarPosDendritas::Normal;

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
    if(varPosDend==VarPosDendritas::Tamano)
        std::sort(dends.begin(), dends.end(), compararTamDend);
    else if(varPosDend==VarPosDendritas::Grosor)
        std::sort(dends.begin(), dends.end(), compararGrosorDend);
    else if(varPosDend==VarPosDendritas::Nodos)
        std::sort(dends.begin(), dends.end(), compararNodosDend);
     for(auto & dend : dends){
				
                dend.setNeuritesTam(neuritesTam);
                dend.setNeuritesGrosor(neuritesGros);
                dend.setDisplacements(displacementX,displacementY);
                dend.setTree(tree);
                dend.setDendograma(dendograma);
                dend.setEsquema(esquema);
                dend.setCircle(circle);
                
     }
    for(auto  axi : ax) {
        axi->setNeuritesTam(neuritesTam);
        axi->setNeuritesGrosor(neuritesGros);
        axi->setDisplacements(displacementX, displacementY);
        axi->setTree(tree);
        axi->setDendograma(dendograma);
        axi->setEsquema(esquema);
        axi->setCircle(circle);
    }
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
         for(auto  axi : ax) {
             if (axi->isSelected())
                 axi->drawSelc(windowPaint);
         }
         if (som->isSelected())
            som->drawSelc(windowPaint);

     }

}

void neuronG::draw3D(QOpenGLWidget* windowPaint){
	float x=0;
	float y=0;
	float z=0;
	int i=0;
    	for(nsol::Node* n: neu->morphology()->soma()->nodes()){
    		glVertex3f(n->point()[0]/300,n->point()[1]/300,n->point()[2]/300);
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
    for(auto  axi : ax) {
        axi->draw3d(0.5, 0.3, 1.0);
    }

    som->draw3d(0.4,0.9,0.1);
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
        for(auto  axi : ax) {
            if (!selected && axi->select(windowPaint, x, y, z)) {
                selected = true;
            }
        }
        if (!selected && som->select(windowPaint, x, y,z)) {
            selected = true;
        } 
    }
    else {
        for (auto &dend: dends)
            if (dend.isSelected()) {
                selected = dend.select(windowPaint, x, y,z);
                break;
            }
        for(auto  axi : ax) {
            if (axi->isSelected())
                selected = axi->select(windowPaint, x, y, z);
        }
         if (som->isSelected())
            selected = som->select(windowPaint, x, y,z);

    }
    return selected;
}

bool neuronG::resetSelect() {
    selected=false;
    for(auto  axi : ax) {
        axi->resetSelect();
    }
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
    std::vector<dendriteG>::iterator it;
    it=dends.begin();
    bool axa=false;
    while(it != dends.end()){
        if(!axa && !ax.empty() && ((varPosDend==VarPosDendritas::Grosor && ax[0]->getGrosor()<it->getGrosor())
                                   || (varPosDend==VarPosDendritas::Nodos && ax[0]->getTerminalNodes()< it->getTerminalNodes()) ||
                                   (varPosDend==VarPosDendritas::Tamano && ax[0]->getTamm()< it->getTamm()))){
            ax[0]->setDisplacements(displacementX, displacementY);
            ax[0]->coordInitials(initX + radio * cos(an), initY + radio * sin(an));
            ax[0]->setAngle(an);
            ax[0]->setScala(scala);
            ax[0]->setAngleHueco(aux);
            ax[0]->draw(windowPaint);

            an += aux;
            axa=true;
        }

        else{
            it->setDisplacements(displacementX, displacementY);
            it->coordInitials(initX + radio * cos(an), initY + radio * sin(an));
            it->setScala(scala);
            it->setAngle(an);
            it->setAngleHueco(aux);
            it->draw(windowPaint);
            an+=aux;
            ++it;
        }
    }
    if(!axa && !ax.empty()){
        ax[0]->setDisplacements(displacementX, displacementY);
        ax[0]->coordInitials(initX + radio * cos(an), initY + radio * sin(an));
        ax[0]->setAngle(an);
        ax[0]->setScala(scala);
        ax[0]->setAngleHueco(aux);
        ax[0]->draw(windowPaint);
    }

}
void neuronG::auxDrawAngleTam(QOpenGLWidget *windowPaint) {
    float angle_anterior=0;
    float radio=som->getRadio();
    float i=0;
    std::vector<dendriteG>::iterator it;
   it=dends.begin();
    bool axa=false;
    while(it != dends.end()){
        if(!axa && !ax.empty() && ((varPosDend==VarPosDendritas::Grosor && ax[0]->getGrosor()<it->getGrosor())
        || (varPosDend==VarPosDendritas::Nodos && ax[0]->getTerminalNodes()< it->getTerminalNodes()) ||
        (varPosDend==VarPosDendritas::Tamano && ax[0]->getTamm()< it->getTamm()))){
            i += ax[0]->getTerminalNodes();
            ax[0]->setDisplacements(displacementX, displacementY);
            ax[0]->setAngle(i / angleTam() * 2 * pi);
            ax[0]->coordInitials(initX + radio * cos(i / angleTam() * 2 * pi),
                                 initY + radio * sin(i / angleTam() * 2 * pi));
            ax[0]->setAngleHueco(i / angleTam() * 2 * pi - angle_anterior);
            angle_anterior = i / angleTam() * 2 * pi;
            ax[0]->draw(windowPaint);
            axa=true;
        }

        else{
            it->setDisplacements(displacementX,displacementY);
            i+=it->getTerminalNodes();
            it->setAngle(i / angleTam() * 2 * pi);
            it->coordInitials(initX + radio * cos(i / angleTam() * 2 * pi), initY + radio * sin(i / angleTam() * 2 * pi));
            it->setScala(scala);
            it->setAngleHueco(i / angleTam() * 2 * pi - angle_anterior);
            angle_anterior= i / angleTam() * 2 * pi;
            it->draw(windowPaint);
            ++it;
        }
    }
    if(!axa && !ax.empty()){
        i += ax[0]->getTerminalNodes();
        ax[0]->setDisplacements(displacementX, displacementY);
        ax[0]->setAngle(i / angleTam() * 2 * pi);
        ax[0]->coordInitials(initX + radio * cos(i / angleTam() * 2 * pi),
                             initY + radio * sin(i / angleTam() * 2 * pi));
        ax[0]->setAngleHueco(i / angleTam() * 2 * pi - angle_anterior);
        angle_anterior = i / angleTam() * 2 * pi;
        ax[0]->draw(windowPaint);

    }

}

void neuronG::tamNeurite(){
    for(auto  axi : ax) {
        axi->setTamMult(2 * (axi->getTam() / tamMaxNeurite));
    }
	  	for (auto & item : dends) {
        		item.setTamMult(2*(item.getTam() / tamMaxNeurite));
	
		}
	
}
void neuronG::grosorNeurite(){
    for(auto  axi : ax) {
        axi->setGrosor(axi->grosorTotal() / 100);
    }
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
    for(auto  axi : ax) {
        axi->setVariableGrosor(a);
    }
    for (auto & item : dends) {
        item.setVariableGrosor(a);
    }
}




void neuronG::setNeuritesVariableTam(float a){
    for(auto  axi : ax) {
        axi->setVariableTam(a);
    }
    for (auto & item : dends) {
        item.setVariableTam(a);
    }
}


void neuronG::calculateMaxMinNodosTerminales(){
	int aux;
    for(auto  axi : ax) {
        aux = axi->getTerminalNodes();
    }
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
    for(auto  axi : ax) {
        axi->setMaxTerminalNodes(max);
        axi->setMinTerminalNodes(min);
    }
       for (auto & item : dends) {
       		item.setMaxTerminalNodes(max);
       		item.setMinTerminalNodes(min);
       	}	
}

void neuronG::calculateMaxMinLongitud(){

    float aux;
    for(auto  axi : ax) {
        aux = axi->getTam();
    }
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
    for(auto  axi : ax) {
        axi->setMaxLongitud(max);
        axi->setMinLongitud(min);
    }
       for (auto & item : dends) {
       		item.setMaxLongitud(max);
       		item.setMinLongitud(min);
       	}	
}

void neuronG::selectSection(QOpenGLWidget* windowPaint, float x, float y) {
    for(auto  axi : ax) {
        axi->selectSection(windowPaint, x, y);
    }
    for (auto & item : dends) {
        item.selectSection(windowPaint,x,y);
    }
}

void neuronG::tamMaxSeccion() {
    float max,min;
    for(auto  axi : ax) {
        max = *axi->getMaxTamSeccion();
        min = *axi->getMinTamSeccion();
    }
    for (auto & item : dends) {
        if(max<*item.getMaxTamSeccion())
            max=*item.getMaxTamSeccion();
        if(min>*item.getMinTamSeccion())
            min=*item.getMinTamSeccion();
    }
    for(auto  axi : ax) {
        axi->setMaxTamSeccion(max);
        axi->setMinTamSeccion(min);
    }
    for (auto & item : dends) {
        item.setMaxTamSeccion(max);
        item.setMinTamSeccion(min);
    }

}

void neuronG::tamMaxP1P2Seccion() {
    float max,min;
    for(auto  axi : ax) {
        max = *axi->getMaxPuntoAPuntoSeccion();
        min = *axi->getMinPuntoAPuntoSeccion();
    }
    for (auto & item : dends) {
        if(max<*item.getMaxPuntoAPuntoSeccion())
            max=*item.getMaxPuntoAPuntoSeccion();
        if(min>*item.getMinPuntoAPuntoSeccion())
            min=*item.getMinPuntoAPuntoSeccion();
    }
    for(auto  axi : ax) {
        axi->setMaxPuntoAPuntoSeccion(max);
        axi->setMinPuntoAPuntoSeccion(min);
    }
    for (auto & item : dends) {
        item.setMaxPuntoAPuntoSeccion(max);
        item.setMinPuntoAPuntoSeccion(min);
    }
}

VarPosDendritas neuronG::getVarPosDend() const {
    return varPosDend;
}

void neuronG::setVarPosDend(VarPosDendritas varPosDend) {
    neuronG::varPosDend = varPosDend;
}

bool neuronG::compararTamDend(const dendriteG& d1,const dendriteG& d2) {
    return d1.getTamm()<d2.getTamm();
}

bool neuronG::compararGrosorDend(const dendriteG &d1, const dendriteG &d2) {
    return d1.getGrosor()<d2.getGrosor();
}

bool neuronG::compararNodosDend(const dendriteG &d1, const dendriteG &d2) {
    return d1.getTerminalNodes()<d2.getTerminalNodes();
}

void neuronG::cont_points_neu(int *aux, float separador,float crecimiento) {
    for(auto  axi : ax) {
        axi->cont_points_neu(aux,separador,crecimiento);
    }
    for (auto & item : dends) {
        item.cont_points_neu(aux,separador,crecimiento);

    }

}


	

