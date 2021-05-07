#include "Barrel.h"

/**
 * Constructor of Barrel
 */
Barrel::Barrel(){

    /* Textures */
    QImage s_fuel=QGLWidget::convertToGLFormat(QImage(":/fuel.jpg"));

    /* Generate an array of textures */
    glGenTextures(1, textureID);

    /* Load barrel textures */
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, s_fuel.width(), s_fuel.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, s_fuel.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

}

/**
 * Delete textures
 */
Barrel::~Barrel(){
    delete [] textureID;
}

/**
 * Display Barrels
 *
 * @param iTimeElapsed : timer
 * @param ground : Ground pointer
 * @param barrelPressed : is the barrel pressed by user ?
 */
void Barrel::Display(uint64_t iTimeElapsed, Ground * ground,  bool barrelPressed) {

     glDisable(GL_LIGHTING);
     glEnable(GL_TEXTURE_2D);

     /* Barrel quadric */
     GLUquadric* quadrique = gluNewQuadric();
     gluQuadricDrawStyle(quadrique, GLU_FILL);

     /* Bind textures to array of textures */
     glBindTexture(GL_TEXTURE_2D, textureID[0]);

     /* Change barrels color upon click */
     if (barrelPressed || prevClicked_) {
         glColor3f(100.f, 0.f, 0.f);
         prevClicked_ = true;
     } else {
         glColor3f(100.f, 100.f, 100.f);
     }

     if (iTimeElapsed % 260 == 0 ) {
         glColor3f(100.f, 100.f, 100.f);
         prevClicked_ = false;
     }



     /* Draw Barrels */
     glPushMatrix();
     glTranslated(- ground->getRoadWidth()/2 - 1., 5.f, -200. + (iTimeElapsed % 260)); // Translation
     drawBarrel(quadrique);
     glPopMatrix();

     glPushMatrix();
     glTranslated(ground->getRoadWidth()/2 + 1., 5.f, -250. + (iTimeElapsed % 310)); // Translation
     drawBarrel(quadrique);
     glPopMatrix();

     glPushMatrix();
     glTranslated(ground->getRoadWidth()/2 + 1., 5.f, -330. + (iTimeElapsed % 390)); // Translation
     drawBarrel(quadrique);
     glPopMatrix();

     gluDeleteQuadric(quadrique);     // Remove barrel when out of frame

     glDisable(GL_TEXTURE_2D);
     glEnable(GL_LIGHTING);

}

/**
 * Draw barrel to define it on ground
 *
 * @param quadrique : barrel quadric object
 */
void Barrel::drawBarrel(GLUquadric * quadrique){

   // glPushMatrix();
    glRotated(90., 1., 0., 0.);        // Rotate around axis

   // glColor3f(1.f, 1.f, 1.f);           // Color Barrel

    gluQuadricTexture(quadrique, GL_TRUE);  // Texture
    gluCylinder(quadrique,1.5, 1.5, 5., 40., 40.);
    gluQuadricTexture(quadrique, GL_FALSE);

   // glColor3f(1.f, 1.f, 0.f);
    gluDisk(quadrique,0.25,1.5,12,1);

   // glPopMatrix();
}
