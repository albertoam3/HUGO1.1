//
// Created by alberto on 29/05/23.
//

#include "neuriteG.h"
constexpr float pint=0.5f;

neuriteG::neuriteG(nsol::Neurite* _neurite){
    this->neurite=_neurite;
    name="neurite";
    displacementX=0;
    displacementY=0;

    firstSection=new sectionH(this->neurite->firstSection());
    terminalNodes= this->terminalNodesFunction();
    scala=1;

    tree=false;
    neuritesGros=false;
    variableGrosor=VarEstado::Tamano;
    variableLongitud=VarLongitud::unitario;
    maxVolumenSeccion = new float;
    minVolumenSeccion = new float;
    maxTamSeccion = new float;
    minTamSeccion = new float;
    maxPuntoAPuntoSeccion=new float;
    minPuntoAPuntoSeccion=new float;

    tam=getTamTotal()/100;
    getDistacia_A_B(maxPuntoAPuntoSeccion, minPuntoAPuntoSeccion);


}
void neuriteG::draw(QOpenGLWidget* windowPaint){
    firstSection->setDisplacementX(displacementX);
    firstSection->setDisplacementY(displacementY);
    firstSection->putColor(color);
    if(tree){
		drawTree(windowPaint);
	}else if(dendograma){
        drawDendograma(windowPaint);

    }else if(esquema){
        drawEsquema(windowPaint);
    }else if(circle) {

        drawSol(windowPaint);


    }
    else{
		float aux,n;
		if(neuritesGros){
			switch(variableGrosor){
				case VarEstado::Tamano:
					aux= (tam - minLongitud) / (maxLongitud - minLongitud);
					n=aux*9 +1;
					glLineWidth(n);
					break;
				case VarEstado::Volumen:
					glLineWidth(grosor);
					break;
				case VarEstado::nodosTerminales:
					aux= (terminalNodes - minTerminalNodes) / (maxTerminalNodes - minTerminalNodes);
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
		glVertex2f(displacementX + initX, displacementY + initY); // Especificar las coordenadas del punto a dibujar
		
		if(neuritesTam)
			glVertex2f(tamMult * (initX) + displacementX + initX, tamMult * (initY) + displacementY + initY);
		else
			glVertex2f(2*(initX) + displacementX + initX, 2 * (initY) + displacementY + initY);
			
		if(selected){
			drawSelc(windowPaint);
		}
		glEnd();
	}  
}
void neuriteG::drawSelc(QOpenGLWidget* windowPaint){
    glLineWidth(4.0);
    glBegin(GL_LINES);
    coordinates();
    glColor3f(0.0f, 0.3f, 0.1f);
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


//Devuelve las coordinates en las que se encuentra el objeto
void neuriteG::coordinates(){
	float mult;
	
	if(neuritesTam){
		mult=tamMult;
	}
	else{
		mult=2;
	}
    if(displacementX + initX > displacementX + initX + mult * (initX)){
        maxX= displacementX + initX + 0.05;
        minX= displacementX + initX + mult * (displacementX + initX) - 0.05;
	}
	else{
        minX= displacementX + initX - 0.05;
        maxX= displacementX + initX + mult * (initX) + 0.05;
	}
	
	if(displacementY + initY > displacementY + initY + mult * (displacementY + initY)){
        maxY= displacementY + initY + 0.05;
        minY= displacementY + initY + mult * (initY) - 0.05;
	}
	else{
        minY= displacementY + initY - 0.05;
        maxY= displacementY + initY + mult * (initY) + 0.05;
	}
    minZ= displacementZ - 0.03;
    maxZ= displacementZ + 0.03;
}



//Comprueba si el objeto esta selected
bool neuriteG::select(QOpenGLWidget* windowPaint, float x, float y, float z){
    coordinates();
    //firstSection->selected(x,y,z);

    if(x > minX && x < maxX && y > minY && y < maxY)
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
bool neuriteG::resetSelect() {
    selected = false;
    return selected;

}

bool neuriteG::isSelected() {
    return selected;
}

int neuriteG::getTerminalNodes() const {
    return terminalNodes;
}

void neuriteG::setTerminalNodes(int terminalNodes) {
    terminalNodes = terminalNodes;
}

float neuriteG::getTam(){
	return tam;
}

void neuriteG::setTamMult(float t){
    tamMult=t;
}


void neuriteG::drawTree(QOpenGLWidget* windowPaint){
		
		bool g;
    float *max=new float;
    float *min=new float;
    if(neuritesGros == true){
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
		if(neuritesTam)
			mult= tamMult * 0.75;
		else
			mult=1.5;
		
		float x=mult*(initX) + displacementX + initX;
		float y=mult*(initY) + displacementY + initY;
		glVertex2f(displacementX + initX, displacementY + initY); // Especificar las coordenadas del punto a dibujar
		glVertex2f(x,y);

		float hipotenusa=0;
		float dif_angle=0.7;
		float distancia=std::sqrt(std::pow(mult*(x-displacementX),2)+pow(mult*(y-displacementY),2));
		hipotenusa=distancia/std::cos(0.52359878)*0.4;
		firstSection->drawSectionsTree(x, y, angle, hipotenusa, dif_angle, g, *max, *min, variableGrosor);

		if(selected){
			drawSelc(windowPaint);
		}
		glEnd();
	
	
}
void neuriteG::drawDendograma(QOpenGLWidget *windowPaint) {
    bool g;
    float *max=new float;
    float *min=new float;

    float *max_long=new float;
    float *min_long= new float;

    if(neuritesGros == true){
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

    float x= getValPoint2(variableLongitud, *max_long, *min_long) * (initX) + displacementX + initX;
    float y= getValPoint2(variableLongitud, *max_long, *min_long) * (initY) + displacementY + initY;
    glVertex2f(displacementX + initX, displacementY + initY); // Especificar las coordenadas del punto a dibujar
    glVertex2f(x,y);
    glEnd();
    glBegin(GL_POINTS);
    glColor3f(color.x(), color.y(), color.z());
    glVertex2f(displacementX + initX, displacementY + initY);
    glVertex2f(x,y);
    glEnd();
    int n=0;
    firstSection->drawSectionsDendograma(x, y, angleGap, angle, terminalNodes, &n, g, *max, *min, variableGrosor, variableLongitud, *max_long, *min_long);
}

void neuriteG::drawEsquema(QOpenGLWidget* windowPaint){

    float xFinal = 2*(initX) + displacementX + initX;
    float yFinal = 2 * (initY) + displacementY + initY;

    glBegin(GL_LINES); // Iniciar el modo de dibujo de linea
    glColor3f(color.x(), color.y(), color.z());
    glVertex2f(displacementX + initX, displacementY + initY); // Especificar las coordenadas del punto a dibujar

    if(neuritesTam)
        glVertex2f(tamMult * (initX) + displacementX + initX, tamMult * (initY) + displacementY + initY);
    else
        glVertex2f(xFinal, yFinal);

    if(selected){
        drawSelc(windowPaint);
    }
    glEnd();
    firstSection->drawSectionsEsquema(xFinal, yFinal,terminalNodes);
}


void neuriteG::setAngle(float a){
	
	angle=a;
	
}	

void neuriteG::setGrosor(float a){
	grosor=a;
}

float neuriteG::grosorTotal(){
    *maxVolumenSeccion=firstSection->getVolumenSeccion();
    *minVolumenSeccion=firstSection->getVolumenSeccion();
	return firstSection->getVolumenAcumulado(maxVolumenSeccion, minVolumenSeccion);
	
}
void neuriteG::setVariableGrosor(int a){
	
  switch ( a )
      {
         case 0:
             variableGrosor=VarEstado::Tamano;
            break;
         case 1:
             variableGrosor=VarEstado::Volumen;
            break;
         case 2:
             variableGrosor=VarEstado::nodosTerminales;
			break;
         default:
             variableGrosor=VarEstado::Tamano;
      }
	
}

void neuriteG::variableGrosorAux(float *max, float *min){
    float aux,n;
    switch(variableGrosor){
        case VarEstado::Volumen:

            *max=(*maxVolumenSeccion);
            *min=(*minVolumenSeccion);
            aux=(firstSection->getVolumenSeccion()-*min)/(*max-*min);
            break;
        case VarEstado::nodosTerminales:
            *max=(firstSection->terminalNodes());
            *min=1;
            aux=(firstSection->terminalNodes()-*min)/(*max-*min);
            break;
        case VarEstado::Tamano:
            *max=(*maxTamSeccion);
            *min=(*minTamSeccion);
            aux=(firstSection->getTamSection()-*min)/(*max-*min);

            break;
    }
    n=aux*4 +1;
    glLineWidth(n);
}

void neuriteG::variableLongitudAux(float *max_long, float *min_long) {
    switch (variableLongitud) {
        case VarLongitud::unitario:
            *max_long=0.25;
            *min_long=0;
            break;
        case VarLongitud::TamanoPuntoInitPuntoFinal:
            *max_long=*maxPuntoAPuntoSeccion;
            *min_long=*minPuntoAPuntoSeccion;
            break;
        case VarLongitud::TamanoSeccion:
            *max_long=*maxTamSeccion;
            *min_long=*minTamSeccion;
            break;

    }
}


void neuriteG::setVariableTam(int a){
    switch ( a )
    {
        case 0:
            variableLongitud=VarLongitud::TamanoSeccion;
            break;
        case 1:
            variableLongitud=VarLongitud::TamanoPuntoInitPuntoFinal;
            break;
        case 2:
            variableLongitud=VarLongitud::unitario;
            break;
        default:
            variableLongitud=VarLongitud::unitario;
    }
}



void neuriteG::setMaxTerminalNodes(float a){

    maxTerminalNodes=a;
}

void neuriteG::setMinTerminalNodes(float a){

    minTerminalNodes=a;
}
	

void neuriteG::setMaxLongitud(float a){

    maxLongitud=a;
}

void neuriteG::setMinLongitud(float a){

    minLongitud=a;
}

void neuriteG::setAngleHueco(float a) {
    angleGap=a;
}

float neuriteG::terminalNodesFunction() {
        return firstSection->terminalNodes();
}

float neuriteG::getTamTotal() {
    *maxTamSeccion=firstSection->getTamSection();
    *minTamSeccion=firstSection->getTamSection();
    return firstSection->getTamTotal(maxTamSeccion, minTamSeccion);
}

void neuriteG::getDistacia_A_B(float *max, float *min){
    *maxPuntoAPuntoSeccion=firstSection->getTamPuntoInicialPuntoFinal();
    *minPuntoAPuntoSeccion=firstSection->getTamPuntoInicialPuntoFinal();
    firstSection->getTamTotalP1P2(maxPuntoAPuntoSeccion, minPuntoAPuntoSeccion);
}


void neuriteG::selectSection(QOpenGLWidget* windowPaint, float x, float y) {
    firstSection->selected( windowPaint,x,y);
}

void neuriteG::draw3d(float x, float y, float z) {
   firstSection->draw3d(x,y,z);
}

float *neuriteG::getMaxTamSeccion() const {
    return maxTamSeccion;
}

float *neuriteG::getMinTamSeccion() const {
    return minTamSeccion;
}

void neuriteG::setMaxTamSeccion(float maxTamSeccionParam) {
    *maxTamSeccion = maxTamSeccionParam;
}

void neuriteG::setMinTamSeccion(float minTamSeccionParam) {
    *minTamSeccion = minTamSeccionParam;
}

float *neuriteG::getMaxPuntoAPuntoSeccion() const {
    return maxPuntoAPuntoSeccion;
}

void neuriteG::setMaxPuntoAPuntoSeccion(float maxPuntoAPuntoSeccionParam) {
    *maxPuntoAPuntoSeccion = maxPuntoAPuntoSeccionParam;
}

float *neuriteG::getMinPuntoAPuntoSeccion() const {
    return minPuntoAPuntoSeccion;
}

void neuriteG::setMinPuntoAPuntoSeccion(float minPuntoAPuntoSeccionParam) {
    *minPuntoAPuntoSeccion = minPuntoAPuntoSeccionParam;
}




float neuriteG::getValPoint2(VarLongitud var_long, float max, float min){
    switch (var_long) {
        case VarLongitud::TamanoSeccion:

            return (firstSection->getTamSection()-min)/(max-min)*1.4;

        case VarLongitud::TamanoPuntoInitPuntoFinal:
            return (firstSection->getTamSection()-min)/(max-min)*1.4;

        case VarLongitud::unitario:
            return 0.5;
        default:
            return 0.5;
    }

}
void neuriteG::drawCirculoAux(float modulo, bool activo) {


    glLineWidth(1);
    glBegin(GL_LINES);
    if(activo)
        glColor4f(0.3f, 0.5f, 0.2f,1.0f);
    else
        glColor4f(0.3f, 0.5f, 0.2f,0.5f);
    float xAux,yAux;
    glVertex2f(modulo,0);
    for (float i = 0; i <= 7 ; i += 0.005) {
        xAux= modulo * cos(i) ;
        yAux = modulo * sin(i) ;
        glVertex2f(xAux , yAux );
        glVertex2f(xAux , yAux );
    }
    glVertex2f(xAux,yAux);
    glEnd();
}

void neuriteG::drawSol(QOpenGLWidget *windowPaint) {
    bool g;
    float *max=new float;
    float *min=new float;

    float *max_long=new float;
    float *min_long= new float;

    if(neuritesGros == true){
        g=true;
        variableGrosorAux(max,min);
    }
    else{
        g=false;
        glLineWidth(1);
    }
    glBegin(GL_LINES); // Iniciar el modo de dibujo de linea
    glColor3f(1.0, 1.0, 1.0);

    //calcular la distancia de el primer punto al centro del soma
    //primero como si el soma siempre estuviera en el 0.0
    Eigen::Vector3f na(0,0,0);

//el error de compilacion esta en esta linea
    float dist= distanciaEntreRegistros(na, firstSection->getSection()->lastNode()->point()) / 1000;

    float x=  dist*initX+ displacementX + initX;
    float y= dist*initY + displacementY + initY;

    glVertex2f(displacementX + initX, displacementY + initY); // Especificar las coordenadas del punto a dibujar
    glVertex2f(x,y);
    glEnd();
    glBegin(GL_POINTS);
    glColor3f(color.x(), color.y(), color.z());
    glVertex2f(displacementX + initX, displacementY + initY);
    glVertex2f(x,y);
    glEnd();
    int n=0;
    firstSection->drawSol(x, y, angleGap, angle, terminalNodes, &n, g, *max, *min, variableGrosor);

}
float neuriteG::distanciaEntreRegistros(Eigen::Vector3f r1, Eigen::Vector3f r2){
    return std::sqrt( std::pow(r1[0] - r2[0], 2) +
                      std::pow(r1[1] - r2[1], 2) +
                      std::pow(r1[2] - r2[2], 2));

}