#include "myOpenGLWidget.h"
#include <QOpenGLContext>
#include <GL/gl.h>


constexpr float ROTATION_FACTOR = 0.01f;

myOpenGLWidget::myOpenGLWidget(QWidget *parent)
        : QOpenGLWidget{parent} {
    buttonDrawActive = false;
    mouseX = 0;
    mouseY = 0;
    translationX = 0;
    translationY = 0;
    scala = 0.0f;
    scalaTotal=1.0f;
    _rotation=false;
    _translation=false;
    setFocusPolicy(Qt::StrongFocus);
    rotation=Eigen::Matrix3f::Identity( );
    position=Eigen::Vector3f(0, 0, 0);
    QSurfaceFormat format;
    format.setSamples(22); // Número de muestras para antialiasing
    this->setFormat(format);
    circle=false;
}

//Métodos necesarios para la utilización de la pantalla QOpenGLWidget : initializeGL,paintGL,resizeGL
void myOpenGLWidget::initializeGL() {
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
}

void myOpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    if (buttonDrawActive) {
        position=Eigen::Vector3f(0, 0, 0);
        buttonDrawActive = false;
        scalaTotal = 1;
        rotation=Eigen::Matrix3f::Identity();
        for (auto &i: gobject) {
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
        glScalef(scalaTotal, scalaTotal, scalaTotal);
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);

        model_view=*reinterpret_cast<Eigen::Matrix4f *>(modelview_matrix);

    }
    for (auto &i: gobject) {
    	i->setScala(scalaTotal);
        i->draw(this,true);
    }

    if(circle){
        int a=0;
        for(float i=0;i<=3.6;i+=0.1){
            if(a%4==1){
                drawCirculoAux(i,true);
            }else{
                drawCirculoAux(i,false);
            }
            a++;
        }

    }

}

void myOpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

//Cada vez que le doy al botón draw, pongo pintar a true, y pongo mouseX y mouseY a 0
void myOpenGLWidget::setDraw(bool a) {
    buttonDrawActive = a;
    mouseX = 0;
    mouseY = 0;
    for (auto &i: gobject) {
        i->displacementN(mouseX, mouseY,0);
        i->resetSelect();
    }
    positionDraws();
    update();

}

void myOpenGLWidget::setGraphicsObject(neuronG *gobj) {
    gobject.push_back(gobj);

}

void myOpenGLWidget::resetList() {
    gobject.clear();
    update();
}


//Cuando pincho en un lado de la pantalla arrasto el objeto alli

void myOpenGLWidget::mousePressEvent(QMouseEvent *event_) {
    scala = 0;
    translationX = 0;
    translationY = 0;

    float x = event_->x();
    float y = height() - event_->y();
    //Convertir la posición del ratón en la ventana en una posición normalizada
    mouseX = ((2.0f * x) / width() - 1.0f);
    mouseY = ((2.0f * y) / height() - 1.0f) ;
    transform();
    if (event_->button() == Qt::RightButton) {
        for (auto &i: gobject) {
            if (i != nullptr)
                i->select(this, result.x(), result.y(),result.z());
        }
        update();
        _rotation=true;
        _translation=false;

    } else if (event_->button() == Qt::LeftButton) {

        _rotation=false;
        _translation=true;
    }
    ejeXAux = mouseX;
    ejeYAux = mouseY;
}

//Cuando arrastro el ratón pulsando la tecla arrastro el objeto alli.
void myOpenGLWidget::mouseMoveEvent(QMouseEvent *event_) {
    scala = 0;
    //Posición del ratón en la ventana
    float x = event_->x();
    float y = height() - event_->y();
    //Convertir la posición del ratón en la ventana en una posición normalizada
    mouseX = ((2.0f * x) / width() - 1.0f);
    mouseY = ((2.0f * y) / height() - 1.0f) ;
    transform();
    if (_translation) {
        bool encontrado = false;
        for (auto &i: gobject) {
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
    else if(_rotation){
        rotate(mouseX-ejeXAux,mouseY-ejeYAux,0.0f);
        update();
    }
    ejeXAux = mouseX;
    ejeYAux = mouseY;
}



void myOpenGLWidget::wheelEvent(QWheelEvent *event) {
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




//metodo auxiliar que habria que cambiar
void myOpenGLWidget::positionDraws() {
    int i = gobject.size();
    int j = (i - 1) / 3;
    int k = (i - 1) % 3 + 1;
    int l = 0;
    float a;
    if (j > 0)
        a = 0.5;
    else
        a = 0;
    for (int h = 0; h < j; h++) {
        gobject[l]->coordInitials(-0.5, a);
        l++;
        gobject[l]->coordInitials(0.0, a);
        l++;
        gobject[l]->coordInitials(0.5, a);
        l++;
        if (j == 1)
            a -= 1;
        else
            a -= 0.5;
    }
    if (k == 1) {
        gobject[l]->coordInitials(0.0, a);
    } else if (k == 2) {
        gobject[l]->coordInitials(-0.5, a);
        l++;
        gobject[l]->coordInitials(0.5, a);
    } else if (k == 3) {
        gobject[l]->coordInitials(-0.5, a);
        l++;
        gobject[l]->coordInitials(0, a);
        l++;
        gobject[l]->coordInitials(0.5, a);
    }
}


void myOpenGLWidget::rotate(float x, float y, float z){
    Eigen::Matrix3f rot;
    Eigen::Matrix3f rYaw;
    Eigen::Matrix3f rPitch;
    Eigen::Matrix3f rRoll;

    float sinYaw = sin( x);
    float cosYaw = cos( x);
    float sinPitch = sin( y);
    float cosPitch = cos( y);
    float sinRoll = sin( z);
    float cosRoll = cos( z);

    rYaw << cosYaw, 0.0f, sinYaw,
            0.0f, 1.0f, 0.0f,
            -sinYaw, 0.0f, cosYaw;

    rPitch << 1.0f, 0.0f, 0.0f,
            0.0f, cosPitch, -sinPitch,
            0.0f, sinPitch, cosPitch;

    rRoll << 1.0f, 0.0f, 0.0f,
            0.0f, cosRoll, -sinRoll,
            0.0f, sinRoll, cosRoll;

    rot = rYaw * rPitch * rRoll;
    rotation= rot*rotation;

}


void myOpenGLWidget::transform() {
    //Punto de origen
    Eigen::Vector3f p(mouseX, mouseY, 0.0f);

    //Obtener la matriz inversa de la transformación de modelo-vista
    Eigen::Matrix4f invMvMat4 = model_view.inverse();
    //Aplicar la transformación inversa al punto de origen
    Eigen::Vector4f transformedPoint = invMvMat4 * Eigen::Vector4f(p.x(), p.y(), p.z(), 1.0f);
    result = transformedPoint.head<3>();
  
}
void myOpenGLWidget::setDrawCircle(bool draw) {
    circle=draw;
    update();
}


void myOpenGLWidget::drawCirculoAux(float modulo, bool activo) {



    glLineWidth(1);
    glBegin(GL_LINES);
    if(activo)
        glColor4f(0.3f, 0.5f, 0.2f,1.0f);
    else
        glColor4f(0.3f, 0.5f, 0.2f,0.5f);
    float xAux,yAux;
    glVertex3f(modulo,0,0);
    for (float i = 0; i <= 7 ; i += 0.005) {
        xAux= modulo * cos(i) ;
        yAux = modulo * sin(i) ;
        glVertex3f(xAux , yAux,0.0f );
        glVertex3f(xAux , yAux,0.0f );
    }
    glVertex3f(xAux,yAux,0.0f);
    glEnd();


    glLineWidth(1);
    glBegin(GL_LINES);
    if(activo)
        glColor4f(0.3f, 0.5f, 0.2f,1.0f);
    else
        glColor4f(0.3f, 0.5f, 0.2f,0.5f);
    glVertex3f(modulo,0,0);
    for (float i = 0; i <= 7 ; i += 0.005) {
        xAux= modulo * cos(i) ;
        yAux = modulo * sin(i) ;
        glVertex3f(xAux ,0.0f, yAux );
        glVertex3f(xAux ,0.0f, yAux );
    }
    glVertex3f(xAux,0.0f,yAux);
    glEnd();


    glLineWidth(1);
    glBegin(GL_LINES);
    if(activo)
        glColor4f(0.3f, 0.5f, 0.2f,1.0f);
    else
        glColor4f(0.3f, 0.5f, 0.2f,0.5f);
    glVertex3f(0.0f,modulo,0);
    for (float i = 0; i <= 7 ; i += 0.005) {
        xAux= modulo * cos(i) ;
        yAux = modulo * sin(i) ;
        glVertex3f(0.0f,xAux , yAux );
        glVertex3f(0.0f,xAux , yAux );
    }
    glVertex3f(0.0f,xAux,yAux);



    glEnd();


}

