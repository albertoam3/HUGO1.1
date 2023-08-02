//
// Created by alberto on 03/05/23.
//



#include "sectionH.h"


#include <vector>

const double sectionH::PI = 3.14159265358979323846;

sectionH::sectionH(nsol::NeuronMorphologySection* _sec){
     sec=_sec;
     selecionada=false;
     getTamSection();
    coordX=0;
    coordY=0;
     displacementX=0;
     displacementY=0;

    for(nsol::Section* s : sec->children()){
        nsol::NeuronMorphologySection* section = dynamic_cast<nsol::NeuronMorphologySection*>(s);
        sectionsHijas.push_back(new sectionH(section));
    }
    tamSeccion=getTamSection();
    tamPuntoInicialPuntoFinal=getTamPuntoInicialPuntoFinal();
}

float sectionH::getTamTotal(float *max, float *min){
	float tam=0;
	for (sectionH* s : sectionsHijas) {

			tam+=s->getTamTotal(max,min);
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
    for (sectionH* s : sectionsHijas) {
        vol+=s->getVolumenAcumulado(maxVolumenSeccion,minVolumenSeccion);
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

void sectionH::drawSectionsTree(float x1, float x2, float angle, float hipotenusa, float dif_angle, bool g, float max, float min, VarEstado variable_grosor){

		float valorX,valorY,valorX2,valorY2;
    coordX=x1;
    coordY=x2;

		hipotenusa*=0.8;
		valorX=x1+cos(angle-1.30899694*dif_angle)*hipotenusa;
		valorY=x2+sin(angle-1.30899694*dif_angle)*hipotenusa;
		valorX2=x1+cos(angle+1.30899694*dif_angle)*hipotenusa;
		valorY2=x2+sin(angle+1.30899694*dif_angle)*hipotenusa;
		dif_angle*=0.6;
		int i=0;
        for (sectionH* s : sectionsHijas) {
			if(i==0){
                if(g) {

                    getLineWidth( variable_grosor, *s, max, min);

                }
                drawLine(x1,x2,valorX,valorY);
                drawPoint(valorX,valorY);
                s->drawSectionsTree(valorX,valorY,angle,hipotenusa,dif_angle,g,max,min,variable_grosor);
			}
			else{
                if(g) {
                    getLineWidth( variable_grosor, *s, max, min);
                }
                drawLine(x1,x2,valorX2,valorY2);
                drawPoint(valorX2,valorY2);

				s->drawSectionsTree(valorX2,valorY2,angle,hipotenusa,dif_angle,g,max,min,variable_grosor);
			}
			i++;
		}
}

bool sectionH::selected(QOpenGLWidget* windowPaint,float x, float y) {
    if(coordX + 0.05 > x && coordX - 0.05 < x && coordY + 0.05 > y && coordY - 0.05 < y){
        QString texto="Soy la seleccionada ";
        seeToolTip(texto,windowPaint);
        selected_hijas(true);
        return true;

    }
    else{
        selected_hijas(false);
    }
    if (sectionsHijas.size() == 2) {
            bool a=sectionsHijas[0]->selected(windowPaint,x,y);
            if (a)
                return true;
            else
                return sectionsHijas[1]->selected(windowPaint,x,y);
    }
    else
        return false;
}


/* drawSectionsDendograma()
 *     elegirSeccionPrimeraYSegunda();
 *     calcularPuntosSeccionPrimera();
 *     drawSeccionRecta();
 *     llamadaRecursiva();
 *     calcularPuntosSeccionSEgunda();
 *     drawArco();
 *     drawSeccion2();
 *     llamadaRecursiva();
 *
 *
 */


void sectionH::drawSectionsDendograma(float x, float y, float angle_hueco, float angle, float terminal_nodes, int *cont, bool g,
                                      float max, float min, VarEstado variable_grosor, VarLongitud var_long, float max_long, float min_long) {
    coordX=x;
    coordY=y;


    if (sectionsHijas.size() == 2) {
        sectionH *sec1, *sec2;
        //ahora mismo se va siempre por la rama más grande, con una variable de estado podriamos decidir si lo queremos asi o queremos que siga el camino que nos dan
        if (sectionsHijas[0]->terminalNodes() > sectionsHijas[1]->terminalNodes()) {
            sec1 = sectionsHijas[0];
            sec2 = sectionsHijas[1];
        } else {
            sec1 = sectionsHijas[1];
            sec2 = sectionsHijas[0];
        }
        if (g) {
            getLineWidth(variable_grosor, *sec1, max, min);
        }
        float x2;
        float y2;
        x2 = x+ sec1->getPoint2(var_long,max_long,min_long) * cos(angle - angle_hueco * (*cont) / terminal_nodes);
        y2 =y+ sec1->getPoint2(var_long,max_long,min_long) * sin(angle - angle_hueco * (*cont) / terminal_nodes);



        drawLine(x, y, x2, y2);
        drawPoint(x2, y2);

        sec1->drawSectionsDendograma(x2, y2, angle_hueco, angle, terminal_nodes, cont,
                                     g, max, min, variable_grosor,var_long,max_long,min_long);
        (*cont)++;

        float modulo = sqrt(pow(x - displacementX, 2) + pow(y - displacementY, 2));
        float nx = modulo * cos(angle - angle_hueco * (*cont) / terminal_nodes) + displacementX;
        float ny = modulo * sin(angle - angle_hueco * (*cont) / terminal_nodes) + displacementY;



        float nix = sec2->getPoint2(var_long,max_long,min_long) * cos(angle - angle_hueco * (*cont) / terminal_nodes);
        float niy = sec2->getPoint2(var_long,max_long,min_long) * sin(angle - angle_hueco * (*cont) / terminal_nodes);

        drawArco( x, y, nx, ny, angle, angle_hueco,cont, terminal_nodes, modulo);
        if (g) {
            getLineWidth( variable_grosor,*sec2, max, min);
        }
        drawLine(nx,ny,nx+nix,ny+niy);
        drawPoint(nx+nix,ny+niy);

        sec2->drawSectionsDendograma(nx + nix, ny + niy, angle_hueco, angle, terminal_nodes, cont, g, max,
                                      min, variable_grosor,var_long,max_long,min_long);
    }

}

float sectionH::terminalNodes() {
    float terminal=0;

    if(sectionsHijas.empty()){
        terminal++;
    }
    for (sectionH* s : sectionsHijas) {
        terminal+=s->terminalNodes();
    }
    return terminal;
}

void sectionH::drawArco(float x1,float y1,float x2,float y2,float angle,float angle_hueco, int* cont,float terminal_nodes,float modulo){
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    float angle_aux = std::atan2(y1-displacementY, x1-displacementX);
    if (angle_aux <  angle - angle_hueco * (*cont)/terminal_nodes)
        angle_aux += 2 * 3.14159;
    glVertex2f(x1, y1);
    for (float i = angle_aux; i >= angle - angle_hueco * (*cont) / terminal_nodes; i -= 0.005) {
        float xAux = modulo * cos(i) ; // Calcula la coordenada x
        float yAux = modulo * sin(i) ; // Calcula la coordenada y
        glVertex2f(xAux + displacementX, yAux + displacementY); // Dibuja el vértice en la posición (x + cx, y + cy)
        glVertex2f(xAux + displacementX, yAux + displacementY); // Dibuja el vértice en la posición (x + cx, y + cy)
    }
    glVertex2f(x2, y2);
    glEnd();


}

void sectionH::drawLine(float x1,float y1,float x2,float y2){
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}
void sectionH::drawPoint(float x1,float y1){
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(color.x(), color.y(), color.z());
    glVertex2f(x1, y1);
    glEnd();
}

void sectionH::getLineWidth(VarEstado variable_grosor, sectionH sec, float max, float min){
    float aux, n;
    switch (variable_grosor) {
        case VarEstado::Volumen:
            aux = (sec.getVolumenSeccion() - min) / (max - min);
            break;
        case VarEstado::nodosTerminales:
            aux = (sec.terminalNodes() - min) / (max - min);
            break;
        case VarEstado::Tamano:
            aux = (sec.getTamSection() - min) / (max - min);
            break;
    }
    n = aux * 4 + 1;
    glLineWidth(n);

}

float sectionH::getPoint2(VarLongitud var_long, float max, float min){
    switch (var_long) {
        case VarLongitud::TamanoSeccion:
            return (tamSeccion-min)/(max-min)*1.4;
        case VarLongitud::TamanoPuntoInitPuntoFinal:
            return (tamPuntoInicialPuntoFinal-min)/(max-min)*1.4;
        case VarLongitud::unitario:
            return 0.25;
        default:
            return 0.25;
    }

}

void sectionH::coordinates() {

}
void sectionH::seeToolTip(QString texto,QOpenGLWidget *windowPaint){
    QToolTip::showText(QCursor::pos(), texto, windowPaint, QRect(), 500);
}

void sectionH::draw3d( float x, float y, float z) {
            glBegin(GL_LINES);
            if(selecionada){
                glColor3f(1,1,1);
            }
            else{
                glColor3f(x, y, z);
            }
            for(nsol::Node* n: sec->nodes()){
                if(n==sec->firstNode() || n==sec->lastNode())
                    glVertex3f(n->point()[0]/100,n->point()[1]/100,n->point()[2]/100);
                else{
                    glVertex3f(n->point()[0]/100,n->point()[1]/100,n->point()[2]/100);
                    glVertex3f(n->point()[0]/100,n->point()[1]/100,n->point()[2]/100);
                }
            }
            glEnd();
        for(sectionH *s: sectionsHijas){
            s->draw3d(x,y,z);
        }


}

void sectionH::selected_hijas(bool sel) {
    selecionada=sel;
    for(sectionH* s:sectionsHijas){
        s->selected_hijas(sel);
    }
}

void sectionH::setDisplacementX(float displacementX) {
    sectionH::displacementX = displacementX;
    for (sectionH* s :sectionsHijas)
        s->setDisplacementX(displacementX);
}

void sectionH::setDisplacementY(float displacementY) {
    sectionH::displacementY = displacementY;
    for (sectionH* s :sectionsHijas)
        s->setDisplacementY(displacementY);
}

void sectionH::putColor(Eigen::Vector3f c) {
    color=c;
    for (sectionH* s :sectionsHijas)
        s->putColor(c);
}

float sectionH::getTamPuntoInicialPuntoFinal() {
    nsol::Node* s=sec->firstNode();
    nsol::Node* a=sec->lastNode();
    float dist=distanciaEntreRegistros(s,a);

    return dist;
}

void sectionH::getTamTotalP1P2(float *max, float *min) {
    float vol=0;
    for (sectionH* s : sectionsHijas) {
        s->getTamTotalP1P2(max, min);
    }
    if(getTamPuntoInicialPuntoFinal()>(*max))
        (*max)=getTamPuntoInicialPuntoFinal();
    else if (getTamPuntoInicialPuntoFinal()<(*min))
        (*min)=getTamPuntoInicialPuntoFinal();

}
