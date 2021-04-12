#include "Ground.h"

Ground::Ground(){

    // Textures
    QImage grass = QGLWidget::convertToGLFormat(QImage(":/grass.jpg"));
    QImage sky = QGLWidget::convertToGLFormat(QImage(":/sky.jpg"));
    QImage road = QGLWidget::convertToGLFormat(QImage(":/road.jpg"));

    glGenTextures(3,TextureID);

    // sky texture
    glBindTexture(GL_TEXTURE_2D, TextureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, sky.width(), sky.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, sky.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    // grass texture
    glBindTexture(GL_TEXTURE_2D, TextureID[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, grass.width(), grass.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, grass.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

    // road texture
    glBindTexture(GL_TEXTURE_2D, TextureID[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, road.width(), road.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, road.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

}

Ground::~Ground(){
    delete [] TextureID;
}

void Ground::Display(uint64_t iTimeElapsed){

    double trans = (iTimeElapsed % 10) / 10.;
    double trans1 = (iTimeElapsed % 15) / 15.;

    glEnable(GL_TEXTURE_2D);
    // Bind sky
    glBindTexture(GL_TEXTURE_2D, TextureID[0]);

    // draw the sky
    glBegin(GL_QUADS);
    //glColor3ub(200,200,200);
    glTexCoord2f(0,2);glVertex3f(-200.0f,200.0f,-200.f);
    glTexCoord2f(0,0);glVertex3f(-200.0f,0.0f,-200.f);
    glTexCoord2f(2,0);glVertex3f(200.0f,0.0f,-200.f);
    glTexCoord2f(2,2);glVertex3f(200.0f,200.0f,-200.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    // Bind grass
    glBindTexture(GL_TEXTURE_2D, TextureID[1]);

    // draw the grass
    glBegin(GL_QUADS);
    //glColor3ub(0,100,0);
    glTexCoord2f(0,5 +trans1);glVertex3f(-200.0f,0.0f,-200.f);
    glTexCoord2f(0,0 +trans1);glVertex3f(-200.0f,0.0f,60.f);
    glTexCoord2f(5,0 +trans1);glVertex3f(200.0f,0.0f,60.f);
    glTexCoord2f(5,5 +trans1);glVertex3f(200.0f,0.0f,-200.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    // Bind ground
    glBindTexture(GL_TEXTURE_2D, TextureID[2]);



    // draw the ground
    glBegin(GL_QUADS);
    //glColor3ub(100,100,100);
    glTexCoord2f(0,0 + trans);glVertex3f(25.0f,0.1f,60.f);
    glTexCoord2f(1,0 + trans);glVertex3f(-25.0f,0.1f,60.f);
    glTexCoord2f(1,10 + trans);glVertex3f(-25.0f,0.1f,-200.f);
    glTexCoord2f(0,10 + trans);glVertex3f(25.0f,0.1f,-200.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

}
