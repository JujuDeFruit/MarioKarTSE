#include "Barrel.h"
#include "Widget.h"


#include <iostream>

/**
 * Constructor of Barrel
 */
Barrel::Barrel(){

    /* Is barrel already created ? */
    created = false;

    /* Generate an array of textures */
    glGenTextures(1, textureID);

    xPos = 0;
    zPos = -200;
    speed = 2;

    stopZone = new StopZone();
}


/**
 * Delete textures
 */
Barrel::~Barrel(){
    delete [] textureID;
}


/**
 * @brief Barrel::LoadTextures
 * Load all textures in array of textures.
 */
void Barrel::LoadTextures() {
    /* Textures */
    QImage s_fuel = QGLWidget::convertToGLFormat(QImage(":/fuel.jpg"));

    /* Load barrel textures */
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, s_fuel.width(), s_fuel.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, s_fuel.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
}


/**
 * Display Barrels
 *
 * @param iTimeElapsed : timer
 * @param ground : Ground pointer
 * @param barrelPressed : is the barrel pressed by user ?
 */
void Barrel::Display( Ground * ground,  bool barrelPressed, bool activateMove) {

    if (!created) {
        if (!(std::rand() % 100)) {
            /* Initialize barrel position. */
            xPos = (std::rand() % 2) ? ground->GetRoadWidth()/2 + 1 : - ground->GetRoadWidth()/2 - 1;
            zPos = zInitBarrel;
            /* Barrel is created */
            created = true;
        }
    }
    if (created) {

        zPos = activateMove ? zPos += speed : zPos;
        //zPos += speed;

        LoadTextures();

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

        /* Draw Barrel */
        glPushMatrix();
        glTranslated(xPos, 5.f, zPos); // Translation
        DrawBarrel(quadrique);
        glPopMatrix();

        float * position = new float[3] { xPos, 5.0f, zPos};
        stopZone->setPosition(position);
        stopZone->Display();

        gluDeleteQuadric(quadrique);     // Remove barrel when out of frame

        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);

        if (zPos >= 60) {
            created = false;
            zPos = zInitBarrel;
            glColor3f(100.f, 100.f, 100.f);
            prevClicked_ = false;
        }
    }
}


/**
 * Draw barrel to define it on ground
 *
 * @param quadrique : barrel quadric object
 */
void Barrel::DrawBarrel(GLUquadric * quadrique){

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


/**
 * @brief drawStopZone
 * Draw area to stop car and fill the car.
 * @param xPos : x position of the barrel.
 */
void Barrel::DrawArea() {

    int xBegin = xPos > 0 ? xPos - 1 : xPos + 1;
    int xEnd = xPos > 0 ? xPos - 1 - areaSide : xPos + 1 + areaSide;

    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3f(xBegin, 1., zPos - areaSide / 2);
    glVertex3f(xEnd, 1., zPos - areaSide / 2);
    glVertex3f(xEnd, 1., zPos + areaSide / 2);
    glVertex3f(xBegin, 1., zPos + areaSide / 2);
    glEnd();
    glPopMatrix();
}



bool Barrel::CarInStopZone(Car * car) {

    if ((car->GetPosition()[0] >= stopZone->GetXRange()[0]
            && car->GetPosition()[0] <= stopZone->GetXRange()[1] - car->GetWidth() / 2.)
        && (car->GetPosition()[1] + car->GetHeight() / 2. <= stopZone->GetZRange()[1] && car->GetPosition()[1] + car->GetHeight() / 2. >= stopZone->GetZRange()[0]
        || car->GetPosition()[1] - car->GetHeight() / 2. <= stopZone->GetZRange()[1] && car->GetPosition()[1] - car->GetHeight() / 2. >= stopZone->GetZRange()[0]
            || car->GetPosition()[1] <= stopZone->GetZRange()[1] && car->GetPosition()[1] >= stopZone->GetZRange()[0])
            ) {
        return true;
    }
    return false;
}
