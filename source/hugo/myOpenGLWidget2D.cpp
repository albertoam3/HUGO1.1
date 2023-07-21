#include "myOpenGLWidget2D.h"

myOpenGLWidget2D::myOpenGLWidget2D(QWidget *parent)  : QOpenGLWidget{parent} {
	buttonDrawActive = false;
    mouseX = 0;
    mouseY = 0;
    translationX = 0;
    translationY = 0;
    scala = 0.0f;
    scalaTotal=1.0f;
    _rotation=false;
    setFocusPolicy(Qt::StrongFocus);
    rotation=Eigen::Matrix3f::Identity( );
    position=Eigen::Vector3f(0, 0, 0);
    QSurfaceFormat format;
    format.setSamples(22); // Número de muestras para antialiasing
    this->setFormat(format);
    setMouseTracking(true); // Habilitar el seguimiento del ratón
    controlPressed=false;
    rPressed=false;
    tPressed=false;
    mogw=nullptr;
}

void myOpenGLWidget2D::setNeuronGraphic(neuronG *neuG){
	  neuronGraphic.push_back(neuG);
	  
}

void myOpenGLWidget2D::resetList() {
    neuronGraphic.clear();
    update();
}
void myOpenGLWidget2D::setDraw(bool a) {
    buttonDrawActive = a;
    mouseX = 0;
    mouseY = 0;
    for (auto &i: neuronGraphic) {
        i->displacementN(mouseX, mouseY,0);
        i->resetSelect();
    }
    //positionDraws();
    update();
}

void myOpenGLWidget2D::select_draw_den(bool a) {
  
    for (auto &i: neuronGraphic) {
        i->setAngleXTam(a);
    }
    update();
}
void myOpenGLWidget2D::select_tam_den(bool a) {
  
    for (auto &i: neuronGraphic) {
        i->setNeuritesTam(a);
    }
    update();
}

void myOpenGLWidget2D::setTree(bool a){
	 for (auto &i: neuronGraphic) {
        i->setTree(a);
    }
	update();
}
void myOpenGLWidget2D::select_grosor_den(bool a) {
    for (auto &i: neuronGraphic) {
        i->setNeuritesGrosor(a);
    }
    update();
}


void myOpenGLWidget2D::variableGrosor(float a){
	for (auto &i: neuronGraphic) {
        i->setNeuritesVariableGrosor(a);
    }
    update();
	
}

void myOpenGLWidget2D::variableTam(float a){
    for (auto &i: neuronGraphic) {
        i->setNeuritesVariableTam(a);
    }
    update();

}
//propias de openGLWidget
void myOpenGLWidget2D::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_MODELVIEW);



    // Habilitar antialiasing
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);

    QSurfaceFormat format = this->format();
}
void myOpenGLWidget2D::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (buttonDrawActive) {
        position=Eigen::Vector3f(0, 0, 0);
        buttonDrawActive = false;
        scalaTotal = 1;
        rotation=Eigen::Matrix3f::Identity();
        for (auto &i: neuronGraphic) {
            i->setDisplacements(0, 0);
            
        }
        model_view=Eigen::Matrix4f::Identity();
    } else {
        GLfloat modelview_matrix[16]; // Matriz de 16 elementos

        glTranslatef(position.x(), position.y(), 0.0f);

        glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
        Eigen::Matrix4f *aux= reinterpret_cast<Eigen::Matrix4f *>(modelview_matrix);
        aux->block< 3, 3 >( 0, 0 ) = rotation;

        glLoadMatrixf(aux->data());
        glScalef(scalaTotal, scalaTotal, 1.0f);
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

        model_view=*reinterpret_cast<Eigen::Matrix4f *>(modelview_matrix);

    }
    for (auto &i: neuronGraphic) {
    	i->setScala(scalaTotal);
        i->draw(this,false);
        //i->draw(this);
    }
    
    
}
void myOpenGLWidget2D::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void myOpenGLWidget2D::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) { // Verificar si se presionó la tecla de control
        int delta = event->angleDelta().y(); // Obtener el desplazamiento de la rueda del ratón
        scala = 0;
        if (delta > 0) {
            scala = 0.05;
        } else if (delta < 0) {
            scala = -0.05;
        }

        scalaTotal += scala;
        update();
    }
}

void myOpenGLWidget2D::mousePressEvent(QMouseEvent *event_) {

    float x = event_->x();
    float y = height() - event_->y();
    //Convertir la posición del ratón en la ventana en una posición normalizada
    mouseX = ((2.0f * x) / width() - 1.0f);
    mouseY = ((2.0f * y) / height() - 1.0f) ;
    transform();
    if (event_->button() == Qt::RightButton) {
        for (auto &i: neuronGraphic) {
            if (i != nullptr)
                i->select(this, result.x(), result.y(), result.z());
        }
        update();
    }
}

//Cuando arrastro el ratón pulsando la tecla arrastro el objeto alli.
void myOpenGLWidget2D::mouseMoveEvent(QMouseEvent *event_) {
    scala = 0;
    //Posición del ratón en la ventana
    float x = event_->x();
    float y = height() - event_->y();
    //Convertir la posición del ratón en la ventana en una posición normalizada
    mouseX = ((2.0f * x) / width() - 1.0f);
    mouseY = ((2.0f * y) / height() - 1.0f) ;
    transform();
    if (controlPressed && tPressed) {
        bool encontrado = false;
        for (auto &i: neuronGraphic) {
            if (i != nullptr && i->isSelected()) {
                encontrado = true;
                if (i->coord_include(result.x(), result.y()))
                    i->displacementN(result.x(), result.y(),result.z());
            }
        }
        if (!encontrado) {
            translationX = mouseX - ejeXAux;
            translationY = mouseY - ejeYAux;
            position.x() += translationX;
            position.y() += translationY;
        } else {
            translationX = 0;
            translationY = 0;
        }
        update();
    }
    else if(controlPressed && rPressed){
        rotate(mouseX-ejeXAux,mouseY-ejeYAux,0.0f);
        update();
    }
    else{
        for (auto &i: neuronGraphic) {
            i->selectSection(this,result.x(),result.y());
        }
    }
    if(mogw!= nullptr)
        mogw->update();

    ejeXAux = mouseX;
    ejeYAux = mouseY;
}

//privadas

void myOpenGLWidget2D::transform() {
    //Punto de origen
    Eigen::Vector3f p(mouseX, mouseY, 0.0f);

    //Obtener la matriz inversa de la transformación de modelo-vista
    Eigen::Matrix4f invMvMat4 = model_view.inverse();
    //Aplicar la transformación inversa al punto de origen
    Eigen::Vector4f transformedPoint = invMvMat4 * Eigen::Vector4f(p.x(), p.y(), p.z(), 1.0f);
    result = transformedPoint.head<3>();
  
}


void myOpenGLWidget2D::rotate(float x, float y, float z){
    Eigen::Matrix3f rot;

    float angle = std::atan2(y, x);  // Calcula el ángulo a partir de las coordenadas x e y

  // Aplica suavizado al ángulo
    static float smoothedAngle = angle;  // Variable para almacenar el ángulo suavizado
    smoothedAngle = 0.000005 * angle + (1.0 - 0.000005) * smoothedAngle;

    float sinAngle = sin(smoothedAngle);
    float cosAngle = cos(smoothedAngle);

    rot << cosAngle, -sinAngle, 0.0f,
           sinAngle, cosAngle, 0.0f,
           0.0f, 0.0f, 1.0f;
    rotation = rot * rotation;

}

void myOpenGLWidget2D::setDendograma(bool a) {
    for (auto &i: neuronGraphic) {
        i->setDendograma(a);
    }
    update();
}

void myOpenGLWidget2D::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Control)
        controlPressed = true; // Tecla Control presionada

    if (event->key() == Qt::Key_R)
        rPressed=true;
    if(event->key() == Qt::Key_T)
        tPressed=true;
}

void myOpenGLWidget2D::keyReleaseEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_Control){
        controlPressed = false; // Tecla Control liberada
    }
    if (event->key() == Qt::Key_R)
        rPressed=false;
    if(event->key() == Qt::Key_T)
        tPressed=false;
}

void myOpenGLWidget2D::otherWidget(myOpenGLWidget *mogw) {
    this->mogw=mogw;
}
