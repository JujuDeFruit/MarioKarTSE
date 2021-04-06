#include "Car.h"

Car::Car(){
}

Car::~Car(){
}

void Car::Display(uint64_t iTimeElapsed) {

    glPushMatrix();

    // Car material
    GLfloat ColorAmbient_car[] = {0.25f, 0.25f, 0.25f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ColorAmbient_car);
    GLfloat ColorDiffuse_car[] = {0.4f, 0.4f, 0.4f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ColorDiffuse_car);
    GLfloat ColorSpeculaire_car[] = {0.774597f, 0.774597f, 0.774597f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ColorSpeculaire_car);
    GLfloat shininess_car[] = {76.8};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess_car);

    // Draw Car
    glBegin(GL_QUADS);
    // ////////////////////////////// bottom part
    // Front
    glColor3ub(100,0,0);
    glNormal3f(0.f,0.f,1.f);
    glVertex3f(-3.0f,3.0f,-5.f);
    glVertex3f(-3.0f,0.0f,-5.f);
    glVertex3f(3.0f,0.0f,-5.f);
    glVertex3f(3.0f,3.0f,-5.f);

    // Back
    glColor3ub(100,0,0);
    glNormal3f(0.f,0.f,-1.f);
    glVertex3f(-3.0f,3.0f,-26.f);
    glVertex3f(-3.0f,0.0f,-26.f);
    glVertex3f(3.0f,0.0f,-26.f);
    glVertex3f(3.0f,3.0f,-26.f);

    // Left
    glColor3ub(100,0,0);
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(-3.0f,3.0f,-26.f);
    glVertex3f(-3.0f,0.0f,-26.f);
    glVertex3f(-3.0f,0.0f,-5.f);
    glVertex3f(-3.0f,3.0f,-5.f);

    // Rignt
    glColor3ub(100,0,0);
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(3.0f,3.0f,-26.f);
    glVertex3f(3.0f,0.0f,-26.f);
    glVertex3f(3.0f,0.0f,-5.f);
    glVertex3f(3.0f,3.0f,-5.f);

    // Top
    glColor3ub(0,100,100);
    glNormal3f(0.f,1.f,0.f);
    glVertex3f(-3.0f,3.0f,-26.f);
    glVertex3f(-3.0f,3.0f,-5.f);
    glVertex3f(3.0f,3.0f,-5.f);
    glVertex3f(3.0f,3.0f,-26.f);

    // Bottom
    glColor3ub(0,100,100);
    glNormal3f(0.f,-1.f,0.f);
    glVertex3f(-3.0f,0.0f,-26.f);
    glVertex3f(-3.0f,0.0f,-5.f);
    glVertex3f(3.0f,0.0f,-5.f);
    glVertex3f(3.0f,0.0f,-26.f);


     // ////////////////////////////// top part
    // Front
    glColor3ub(100,0,0);
    glNormal3f(0.f,0.5f,0.5f);
    glVertex3f(-3.0f,5.0f,-9.f);
    glVertex3f(-3.0f,3.0f,-8.f);
    glVertex3f(3.0f,3.0f,-8.f);
    glVertex3f(3.0f,5.0f,-9.f);

    // Back
    glColor3ub(100,0,0);
    glNormal3f(0.f,0.5f,-0.5f);
    glVertex3f(-3.0f,5.0f,-18.f);
    glVertex3f(-3.0f,3.0f,-20.f);
    glVertex3f(3.0f,3.0f,-20.f);
    glVertex3f(3.0f,5.0f,-18.f);

    // Left
    glColor3ub(100,0,0);
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(-3.0f,5.0f,-18.f);
    glVertex3f(-3.0f,3.0f,-20.f);
    glVertex3f(-3.0f,3.0f,-8.f);
    glVertex3f(-3.0f,5.0f,-9.f);

    // Rignt
    glColor3ub(100,0,0);
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(3.0f,5.0f,-18.f);
    glVertex3f(3.0f,3.0f,-20.f);
    glVertex3f(3.0f,3.0f,-8.f);
    glVertex3f(3.0f,5.0f,-9.f);

    // Top
    glColor3ub(0,100,100);
    glNormal3f(0.f,1.f,0.f);
    glVertex3f(-3.0f,5.0f,-18.f);
    glVertex3f(-3.0f,5.0f,-9.f);
    glVertex3f(3.0f,5.0f,-9.f);
    glVertex3f(3.0f,5.0f,-18.f);

    glEnd();

    glPopMatrix();


    // ////////////////////////// Girophare
    GLUquadric* quadrique1 = gluNewQuadric();
    gluQuadricDrawStyle(quadrique1,GLU_FILL);

    // Draw Gyro
    glPushMatrix();
    glTranslatef(-1.f,5.1f,-14.f);
    drawGirophare(quadrique1, iTimeElapsed);
    glPopMatrix();



    // ////////////////////////////// Windows

    // window Material
    GLfloat colorAmbiante_window[] = {0.0f, 0.0f, 0.0f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbiante_window);
    GLfloat colorDiffuse_window[] = {0.01f, 0.01f, 0.01f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDiffuse_window);
    GLfloat colorSpeculaire_window[] = {0.5f, 0.5f, 0.5f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorSpeculaire_window);
    GLfloat shininess_window[] = {32};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess_window);
    GLfloat colorEmission_window[] = {0, 0, 0, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colorEmission_window);

    // Draw Window

    glBegin(GL_QUADS);
    // Left Front
    glColor3f(0.f,0.f,0.f);
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(-3.01f,4.8f,-17.7f);
    glVertex3f(-3.01f,3.0f,-19.7f);
    glVertex3f(-3.001f,3.0f,-14.f);
    glVertex3f(-3.001f,4.8f,-14.f);

    // Rignt Front
    glColor3f(0.f,0.f,0.f);
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(3.01f,4.8f,-17.7f);
    glVertex3f(3.01f,3.0f,-19.7f);
    glVertex3f(3.01f,3.0f,-14.f);
    glVertex3f(3.01f,4.8f,-14.f);

    // Left Back
    glColor3f(0.f,0.f,0.f);
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(-3.01f,4.8f,-13.5f);
    glVertex3f(-3.01f,3.0f,-13.5f);
    glVertex3f(-3.01f,3.0f,-8.3f);
    glVertex3f(-3.01f,4.8f,-9.3f);

    // Rignt Back
    glColor3f(0.f,0.f,0.f);
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(3.01f,4.8f,-13.5f);
    glVertex3f(3.01f,3.0f,-13.5f);
    glVertex3f(3.01f,3.0f,-8.3f);
    glVertex3f(3.01f,4.8f,-9.3f);

    // Front
    glColor3ub(0,0,0);
    glNormal3f(0.f,0.5f,-0.5f);
    glVertex3f(-2.8f,4.97f,-8.999f);
    glVertex3f(-2.8f,3.2f,-7.999f);
    glVertex3f(2.8f,3.2f,-7.999f);
    glVertex3f(2.8f,4.97f,-8.999f);

    // Back
    glColor3ub(0,0,0);
    glNormal3f(1.f,0.5f,0.5f);
    glVertex3f(-2.8f,4.97f,-18.001f);
    glVertex3f(-2.8f,3.2f,-20.001f);
    glVertex3f(2.8f,3.2f,-20.001f);
    glVertex3f(2.8f,4.97f,-18.001f);
    glEnd();


    // //////////////////////////////: Phares

    glBegin(GL_QUADS);

    GLfloat colorAmbiante5_tab[] = {1.f, 0.10f, 0.01f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbiante5_tab);
    GLfloat colorDiffuse5_tab[] = {0.01f, 0.01f, 0.01f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDiffuse5_tab);
    GLfloat colorSpeculaire5_tab[] = {0.5f, 0.5f, 0.5f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorSpeculaire5_tab);
    GLfloat shininess5[] = {72};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess5);
    GLfloat colorEmission5_tab[] = {0.3, 0.3, 0.3, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colorEmission5_tab);


    // Front
    glColor3ub(100,100,50);
    glNormal3f(0.f,0.f,1.f);
    glVertex3f(-2.5f,2.f,-4.99f);
    glVertex3f(-2.5f,1.f,-4.99f);
    glVertex3f(-1.5f,1.f,-4.99f);
    glVertex3f(-1.5f,2.f,-4.99f);

    glColor3ub(100,100,50);
    glNormal3f(0.f,0.f,1.f);
    glVertex3f(1.5f,2.f,-4.99f);
    glVertex3f(1.5f,1.f,-4.99f);
    glVertex3f(2.5f,1.f,-4.99f);
    glVertex3f(2.5f,2.f,-4.99f);

    // Back
    glColor3ub(100,100,50);
    glNormal3f(0.f,0.f,-1.f);
    glVertex3f(-2.5f,2.f,-26.0001f);
    glVertex3f(-2.5f,1.f,-26.0001f);
    glVertex3f(-1.5f,1.f,-26.0001f);
    glVertex3f(-1.5f,2.f,-26.0001f);

    glColor3ub(100,100,50);
    glNormal3f(0.f,0.f,-1.f);
    glVertex3f(1.5f,2.f,-26.0001f);
    glVertex3f(1.5f,1.f,-26.0001f);
    glVertex3f(2.5f,1.f,-26.0001f);
    glVertex3f(2.5f,2.f,-26.0001f);

    glEnd();


    // /////////////////////////// Tiers

    GLUquadric* quadrique = gluNewQuadric();
    gluQuadricDrawStyle(quadrique,GLU_FILL);

    // Front left wheel
    glPushMatrix();
    glTranslatef(-3.2f,0.f,-20.f);
    drawTier(quadrique);
    glPopMatrix();

    // Front right wheel
    glPushMatrix();
    glTranslatef(2.8f,0.f,-20.f);
    drawTier(quadrique);
    glPopMatrix();

    // Back left wheel
    glPushMatrix();
    glTranslatef(-3.2f,0.f,-10.f);
    drawTier(quadrique);
    glPopMatrix();

    // Back right wheel
    glPushMatrix();
    glTranslatef(2.8f,0.f,-10.f);
    drawTier(quadrique);
    glPopMatrix();


    // General light
    GLfloat colorAmbiante_[] = {0.9f, 0.9f, 0.9f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbiante_);
}




void Car::drawTier(GLUquadric* quadrique){
    // Matériau
    GLfloat ambient_wheel[] = {0.f, 0.f, 0.f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_wheel);
    GLfloat diffuse_wheel[] = {0.01f, 0.01f, 0.01f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_wheel);
    GLfloat Speculaire_wheel[] = {0.5f, 0.5f, 0.5f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Speculaire_wheel);
    GLfloat shininess_wheel[] = {32};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess_wheel);

    glPushMatrix();
    glRotatef(90,0,1,0);   // rotation autour de l'axe y
    glColor3ub(0.,0.,0.);
    gluCylinder(quadrique,1., 1., 0.5, 40., 40.); // base top height sliceV stackH

    glColor3f(.25f,.25f,.25f);
    gluDisk(quadrique,0.25,1.0,12,1);

    glTranslatef(0.f,0.f,0.5f);
    gluDisk(quadrique,0.25,1.0,12,1);

    glPopMatrix();
}




void Car::drawGirophare(GLUquadric* quadrique, uint64_t iTimeElapsed){

    // light Gyro
    GLfloat light_tab[] = { -1.f,5.65f,-14.f, 1.f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_tab);

    GLfloat light_color_Red[] = { 1.f, 0.f, 0.f};
    GLfloat light_color_Blue[] = { 0.f, 0.f, 1.f};
    if (iTimeElapsed % 40 < 20) {
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color_Red);
        GLfloat colorAmbiante_[] = {0.9f, 0.f, 0.f, 1.f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbiante_);
    } else {
        GLfloat colorAmbiante_[] = {0.f, 0.f, 0.9f, 1.f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbiante_);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color_Blue);
    }

    glPushMatrix();
    glRotatef(90,-1,0,0);   // rotation autour de l'axe y
    glColor3f(.25f,.25f,.25f);
    gluSphere(quadrique, 0.5, 10, 10);
    glPopMatrix();
}
