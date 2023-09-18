//
// Created by alberto on 11/09/23.
//

#include <iostream>
#include "openGLDialog.h"

void openGLDialog::paintGL() {
    QPainter painter(this);
    painter.setPen(Qt::white); // Color del texto (blanco)
    QFont font;
    font.setPixelSize(24); // Tamaño de fuente
    painter.setFont(font);

    painter.drawLine(45, 450, 45,30 );
    painter.drawLine(20, 430, 430, 430);
    int alto=0;
    for(int i=0;i<9;i++){
        if(alto<nodos_por_punto[i])
            alto=nodos_por_punto[i];

    }
    float alto_aux=(alto/9 +1)*(9);

    int a=55;
    int b=420;
    int c=45;
    float pintar=0;
    QBrush brush(Qt::blue);
    painter.setBrush(brush);
    QPen pen;

    for(int i=0;i<9;i++){

        QString qstr = QString::number(i+1);
        QString qstr2 = QString::number((alto/9 +1)*(i+1));

        std::cout<<nodos_por_punto[i]<<"\n";

        if(nodos_por_punto[i]!=0)
            pintar=340*nodos_por_punto[i]/alto_aux;

        pen.setColor(Qt::white);
        painter.setPen(pen);

        painter.drawText(a, 450, qstr);
        painter.drawText(3, b, qstr2);

        pen.setColor(Qt::red);
        painter.setPen(pen);

        if(nodos_por_punto[i]>alto/9) {
            painter.drawRect(c, 430, 35, -pintar);
        }
        else if(nodos_por_punto[i]!=0){
            painter.drawRect(c,430,35,- (20*nodos_por_punto[i]/(alto/9 +1)));
        }
        a+=35;
        b-=40;
        c+=35;


    }




}


void openGLDialog::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void openGLDialog::initializeGL() {
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

void openGLDialog::anadir_nodos_por_punto(int aux[9]) {
    for (int i=0;i<9;i++){
        nodos_por_punto[i]=aux[i];
    }
}
