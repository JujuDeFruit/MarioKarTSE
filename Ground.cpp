#include "Ground.h"


/**
 * @brief Ground::Ground
 * Constructor of ground.
 * @param iTimeElapsed : timer to synchronize on.
 */
Ground::Ground(uint64_t iTimeElapsed){

    /* Define speeds */
    roadSpeed = (iTimeElapsed % 10) / 10.;
    grassSpeed = (iTimeElapsed % 15) / 15.;

    /* Load textures */
    QImage grass = QGLWidget::convertToGLFormat(QImage(":/grass.jpg"));
    QImage sky = QGLWidget::convertToGLFormat(QImage(":/sky.jpg"));
    QImage road = QGLWidget::convertToGLFormat(QImage(":/road.jpg"));

    /* Generate array of textures */
    glGenTextures(3, textureID);

    /* Sky texture */
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, sky.width(), sky.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, sky.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    /* Grass texture */
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, grass.width(), grass.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, grass.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    /* Road texture */
    glBindTexture(GL_TEXTURE_2D, textureID[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, road.width(), road.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, road.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
}


/**
 * @brief Ground::~Ground
 * Destructor of ground.
 */
Ground::~Ground(){
    delete [] textureID;
}


/**
 * @brief Ground::Display
 * Display and refresh ground.
 */
void Ground::Display(){

    glEnable(GL_TEXTURE_2D);
    /* Bind sky texture to array */
    glBindTexture(GL_TEXTURE_2D, textureID[0]);

    /* Draw sky */
    glBegin(GL_QUADS);
    //glColor3ub(200,200,200);
    glTexCoord2f(0,2);glVertex3f(-200.0f,200.0f,-200.f);
    glTexCoord2f(0,0);glVertex3f(-200.0f,0.0f,-200.f);
    glTexCoord2f(2,0);glVertex3f(200.0f,0.0f,-200.f);
    glTexCoord2f(2,2);glVertex3f(200.0f,200.0f,-200.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);

    /* Bind grass */
    glBindTexture(GL_TEXTURE_2D, textureID[1]);

    /* Draw the grass */
    glBegin(GL_QUADS);
    //glColor3ub(0,100,0);
    glTexCoord2f(0,5 + grassSpeed);glVertex3f(-200.0f,0.0f,-200.f);
    glTexCoord2f(0,0 + grassSpeed);glVertex3f(-200.0f,0.0f,60.f);
    glTexCoord2f(5,0 + grassSpeed);glVertex3f(200.0f,0.0f,60.f);
    glTexCoord2f(5,5 + grassSpeed);glVertex3f(200.0f,0.0f,-200.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);

    /* Bind ground */
    glBindTexture(GL_TEXTURE_2D, textureID[2]);

    /* Draw the ground */
    glBegin(GL_QUADS);
    //glColor3ub(100,100,100);
    glTexCoord2f(0,0 + roadSpeed);glVertex3f(25.0f,0.1f,60.f);
    glTexCoord2f(1,0 + roadSpeed);glVertex3f(-25.0f,0.1f,60.f);
    glTexCoord2f(1,10 + roadSpeed);glVertex3f(-25.0f,0.1f,-200.f);
    glTexCoord2f(0,10 + roadSpeed);glVertex3f(25.0f,0.1f,-200.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
