
#include "neuron_g.h"

#include <iostream>

const float pi = 3.14159265359;

neuron_g::neuron_g(nsol::Neuron *_neu){
    neu=_neu;
    ax.push_back(new axon_g(neu->morphology()->axon()));
    som=new soma_g(neu->morphology()->soma());
    const auto &den=neu->morphology()->dendrites();
    for (auto &dendrite: *den) {
        dends.push_back(*new dendrite_g(dendrite));
    }
 

    selected=false;
    displacementX=0;
    displacementY=0;
    init_x=0;
    init_y=0;
    coordinates();
    name=neu->gid();
    angleXTam=false;


}
void neuron_g::draw(QOpenGLWidget* windowPaint){
   if(dimension==false){	
     if(angleXTam==false)
       auxDrawAngleEqual(windowPaint);
     else
       auxDrawAngleTam(windowPaint);

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
    
    else{
	int x=0;
	int y=0;
	int z=0;
	int i=0;
    	for(nsol::Node* n: neu->morphology()->soma()->nodes()){
    		glVertex3f(n->point()[0]/100,n->point()[1]/100,n->point()[2]/100);
    	}
    	
    	for (nsol::Neurite* n:neu->morphology()->neurites()){
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
    	  	
    	  	glBegin(GL_LINES);
    	  	glColor3f(x, y, z);
    	  	std::stack<nsol::SectionPtr> sPS;

     	   	sPS.push(n->firstSection());
	
    		while (!sPS.empty( ))
    		{
      			nsol::NeuronMorphologySectionPtr lS =
        		dynamic_cast< nsol::NeuronMorphologySectionPtr >( sPS.top( ));
      			sPS.pop( );
      			for (nsol::Sections::iterator child = lS->children( ).begin( );
           			child != lS->children( ).end( ); child++)
      			{
        			for(nsol::Node* n: lS->nodes()){
        				if(n==lS->firstNode() || n==lS->lastNode())
    						glVertex3f(n->point()[0]/100,n->point()[1]/100,n->point()[2]/100);
    					else{
    						glVertex3f(n->point()[0]/100,n->point()[1]/100,n->point()[2]/100);
    						glVertex3f(n->point()[0]/100,n->point()[1]/100,n->point()[2]/100);
    					}
    				}
        			
        		sPS.push(*child);
      			}	
    		}
    		glEnd();
    	}
    	
    }
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
    ax[0]->draw(windowPaint);
    an+=aux;
    for (auto & item : dends) {
        item.setDisplacements(displacementX, displacementY);
        item.coordInitials(init_x+radio*cos(an), init_y+radio*sin(an));
        item.draw(windowPaint);
        an+=aux;
    }

}
void neuron_g::auxDrawAngleTam(QOpenGLWidget *windowPaint) {
    float radio=som->getRadio();
    float i=0;
    i+=ax[0]->getTerminalNodes();
    ax[0]->setDisplacements(displacementX, displacementY);
    ax[0]->coordInitials(init_x+radio*cos(i/angle_tam()*2*pi), init_y+radio*sin(i/angle_tam()*2*pi));
   
    ax[0]->draw(windowPaint);

    for(auto & item: dends){
        item.setDisplacements(displacementX,displacementY);
        i+=item.getTerminalNodes();
        item.coordInitials(init_x+radio*cos(i/angle_tam()*2*pi),init_y+radio*sin(i/angle_tam()*2*pi));
        item.draw(windowPaint);
    }

}



