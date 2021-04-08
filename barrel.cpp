#include "barrel.h"

Barrel::Barrel(){

    // Texture
    QImage s_fuel=QGLWidget::convertToGLFormat(QImage(":/fuel.jpg"));

    glGenTextures(1, TextureID);

    // Barrel texture
    glBindTexture(GL_TEXTURE_2D, TextureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, s_fuel.width(), s_fuel.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, s_fuel.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

}


Barrel::~Barrel(){
    delete [] TextureID;
}

void Barrel::Display(uint64_t iTimeElapsed) {

     glDisable(GL_LIGHTING);
     glEnable(GL_TEXTURE_2D);

     // Quadrique
     GLUquadric* quadrique = gluNewQuadric();
     gluQuadricDrawStyle(quadrique, GLU_FILL);

     // bind texture
     glBindTexture(GL_TEXTURE_2D, TextureID[0]);

     // Draw Barrel
     glPushMatrix();
     glTranslated(-21.f,5.f, -200. + (iTimeElapsed % 260)); // trans
     drawBarrel(quadrique);
     glPopMatrix();

     glPushMatrix();
     glTranslated(21.f,5.f, -250. + (iTimeElapsed % 310)); // trans
     drawBarrel(quadrique);
     glPopMatrix();

     glPushMatrix();
     glTranslated(21.f,5.f, -330. + (iTimeElapsed % 390)); // trans
     drawBarrel(quadrique);
     glPopMatrix();


     gluDeleteQuadric(quadrique);     // remove barrel when out of frame

     glDisable(GL_TEXTURE_2D);
     glEnable(GL_LIGHTING);

}

void Barrel::drawBarrel(GLUquadric* quadrique){


    glPushMatrix();
    glRotated(90., 1., 0., 0.);        // rotation autour de l'axe x



    glColor3f(1.f, 1.f, 1.f);           // color Barrel


    gluQuadricTexture(quadrique, GL_TRUE);  // Texture
    gluCylinder(quadrique,1.5, 1.5, 5., 40., 40.);
    gluQuadricTexture(quadrique, GL_FALSE);

    glColor3f(1.f, 1.f, 0.f);
    gluDisk(quadrique,0.25,1.5,12,1);

    glPopMatrix();
}
