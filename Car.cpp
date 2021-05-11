#include "Car.h"


/**
 * @brief Car::Car
 * Constructor of car object.
 *
 * @param color_ color of the car to display.
 */
Car::Car(GLfloat * color_){
    color = color_;
}


/**
 * @brief Car::Display
 * Display and refresh car on the screen.
 *
 * @param iTimeElapsed : timer to synchronize displaying.
 */
void Car::Display(uint64_t iTimeElapsed, bool activGiro) {
    glPushMatrix();

    /* Car settings */

    /** Material reaction **/
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    GLfloat ColorDiffuse_car[] = {0.4f, 0.4f, 0.4f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ColorDiffuse_car);
    GLfloat ColorSpeculaire_car[] = {0.774597f, 0.774597f, 0.774597f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ColorSpeculaire_car);
    GLfloat shininess_car[] = {76.8};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess_car);

    /* Draw Car */
    glBegin(GL_QUADS);

    /** Bottom part**/

    /*** Front ***/
    glColor3ub(100,0,0);
    glNormal3f(0.f,0.f,1.f);
    glVertex3f(-3.0f,3.0f,-5.f);
    glVertex3f(-3.0f,0.0f,-5.f);
    glVertex3f(3.0f,0.0f,-5.f);
    glVertex3f(3.0f,3.0f,-5.f);

    /*** Back ***/
    glColor3ub(100,0,0);
    glNormal3f(0.f,0.f,-1.f);
    glVertex3f(-3.0f,3.0f,-26.f);
    glVertex3f(-3.0f,0.0f,-26.f);
    glVertex3f(3.0f,0.0f,-26.f);
    glVertex3f(3.0f,3.0f,-26.f);

    /*** Left ***/
    glColor3ub(100,0,0);
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(-3.0f,3.0f,-26.f);
    glVertex3f(-3.0f,0.0f,-26.f);
    glVertex3f(-3.0f,0.0f,-5.f);
    glVertex3f(-3.0f,3.0f,-5.f);

    /*** Right ***/
    glColor3ub(100,0,0);
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(3.0f,3.0f,-26.f);
    glVertex3f(3.0f,0.0f,-26.f);
    glVertex3f(3.0f,0.0f,-5.f);
    glVertex3f(3.0f,3.0f,-5.f);

    /*** Top ***/
    glColor3ub(0,100,100);
    glNormal3f(0.f,1.f,0.f);
    glVertex3f(-3.0f,3.0f,-26.f);
    glVertex3f(-3.0f,3.0f,-5.f);
    glVertex3f(3.0f,3.0f,-5.f);
    glVertex3f(3.0f,3.0f,-26.f);

    /*** Bottom ***/
    glColor3ub(0,100,100);
    glNormal3f(0.f,-1.f,0.f);
    glVertex3f(-3.0f,0.0f,-26.f);
    glVertex3f(-3.0f,0.0f,-5.f);
    glVertex3f(3.0f,0.0f,-5.f);
    glVertex3f(3.0f,0.0f,-26.f);


    /** Top Part **/

    //*** Front ***/
    glColor3ub(100,0,0);
    glNormal3f(0.f,0.5f,0.5f);
    glVertex3f(-3.0f,5.0f,-9.f);
    glVertex3f(-3.0f,3.0f,-8.f);
    glVertex3f(3.0f,3.0f,-8.f);
    glVertex3f(3.0f,5.0f,-9.f);

    /*** Back ***/
    glColor3ub(100,0,0);
    glNormal3f(0.f,0.5f,-0.5f);
    glVertex3f(-3.0f,5.0f,-18.f);
    glVertex3f(-3.0f,3.0f,-20.f);
    glVertex3f(3.0f,3.0f,-20.f);
    glVertex3f(3.0f,5.0f,-18.f);

    /*** Left ***/
    glColor3ub(100,0,0);
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(-3.0f,5.0f,-18.f);
    glVertex3f(-3.0f,3.0f,-20.f);
    glVertex3f(-3.0f,3.0f,-8.f);
    glVertex3f(-3.0f,5.0f,-9.f);

    /*** Right ***/
    glColor3ub(100,0,0);
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(3.0f,5.0f,-18.f);
    glVertex3f(3.0f,3.0f,-20.f);
    glVertex3f(3.0f,3.0f,-8.f);
    glVertex3f(3.0f,5.0f,-9.f);

    /*** Top ***/
    glColor3ub(0,100,100);
    glNormal3f(0.f,1.f,0.f);
    glVertex3f(-3.0f,5.0f,-18.f);
    glVertex3f(-3.0f,5.0f,-9.f);
    glVertex3f(3.0f,5.0f,-9.f);
    glVertex3f(3.0f,5.0f,-18.f);

    glEnd();

    if (activGiro){
        glPopMatrix();

        /* Gyrophare */
        /** Gyrophare Quadric **/
        GLUquadric* quadrique1 = gluNewQuadric();
        gluQuadricDrawStyle(quadrique1,GLU_FILL);

        /** Draw Gyrophare **/
        glPushMatrix();
        glTranslatef(-1.f,5.1f,-14.f);
        DrawGirophare(quadrique1, iTimeElapsed);

        glPopMatrix();
     }

    /* Window settings */

    /** Material reaction **/
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

    /** Draw Window **/

    DrawWindows();

    /* Headlights */

    DrawHeadLights();

    /* Tiers */

    GLUquadric* quadrique = gluNewQuadric();
    gluQuadricDrawStyle(quadrique, GLU_FILL);

    /** Front left wheel **/
    glPushMatrix();
    glTranslatef(-3.2f,0.f,-20.f);
    DrawTier(quadrique);
    glPopMatrix();

    /** Front right wheel **/
    glPushMatrix();
    glTranslatef(2.8f,0.f,-20.f);
    DrawTier(quadrique);
    glPopMatrix();

    /** Back left wheel **/
    glPushMatrix();
    glTranslatef(-3.2f,0.f,-10.f);
    DrawTier(quadrique);
    glPopMatrix();

    /** Back right wheel **/
    glPushMatrix();
    glTranslatef(2.8f,0.f,-10.f);
    DrawTier(quadrique);
    glPopMatrix();


    /* General light */
    GLfloat colorAmbiante_[] = {0.9f, 0.9f, 0.9f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colorAmbiante_);
}


/**
 * @brief Car::DrawTier
 * Draw tiers, and refresh them on the screen.
 *
 * @param quadrique to draw tier
 */
void Car::DrawTier(GLUquadric* quadrique){
    /* Material */
    GLfloat ambient_wheel[] = {0.f, 0.f, 0.f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_wheel);
    GLfloat diffuse_wheel[] = {0.01f, 0.01f, 0.01f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_wheel);
    GLfloat Speculaire_wheel[] = {0.5f, 0.5f, 0.5f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Speculaire_wheel);
    GLfloat shininess_wheel[] = {32};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess_wheel);

    glPushMatrix();
    glRotatef(90,0,1,0);   // Rotate around Y.
    glColor3ub(0.,0.,0.);
    gluCylinder(quadrique,1., 1., 0.5, 40., 40.); // base top height sliceV stackH

    glColor3f(.25f,.25f,.25f);
    gluDisk(quadrique,0.25,1.0,12,1);

    glTranslatef(0.f,0.f,0.5f);
    gluDisk(quadrique,0.25,1.0,12,1);

    glPopMatrix();
}


/**
 * Draw gyrophare on the car
 *
 * @param quadrique : quadrique to draw gyrophare.
 * @param iTimeElapsed : timer to synchronize on.
 */
void Car::DrawGirophare(GLUquadric* quadrique, uint64_t iTimeElapsed){

    /* light gyrophare */
    GLfloat light_tab[] = { -1.f,5.65f,-14.f, 1.f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_tab);

    /* Definae colors */
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
    glRotatef(90,-1,0,0);   // Rotate around Y.
    glColor3f(.25f,.25f,.25f);
    gluSphere(quadrique, 0.5, 10, 10);
    glPopMatrix();
}


/**
 * @brief Car::DrawWindows
 * Draw windows on the car
 */
void Car::DrawWindows(){

    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /** Draw Window **/

    glBegin(GL_QUADS);

    /*** Left Front ***/
    glColor4f(0, 0, 0, 0.8);
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(-3.01f,4.8f,-17.7f);
    glVertex3f(-3.01f,3.0f,-19.7f);
    glVertex3f(-3.001f,3.0f,-14.f);
    glVertex3f(-3.001f,4.8f,-14.f);

    /*** Right Front ***/
    glColor4f(0, 0, 0, 0.8);
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(3.01f,4.8f,-17.7f);
    glVertex3f(3.01f,3.0f,-19.7f);
    glVertex3f(3.01f,3.0f,-14.f);
    glVertex3f(3.01f,4.8f,-14.f);

    /*** Left Back ***/
    glColor4f(0, 0, 0, 0.8);
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(-3.01f,4.8f,-13.5f);
    glVertex3f(-3.01f,3.0f,-13.5f);
    glVertex3f(-3.01f,3.0f,-8.3f);
    glVertex3f(-3.01f,4.8f,-9.3f);

    /*** Right Back ***/
    glColor4f(0, 0, 0, 0.8);
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(3.01f,4.8f,-13.5f);
    glVertex3f(3.01f,3.0f,-13.5f);
    glVertex3f(3.01f,3.0f,-8.3f);
    glVertex3f(3.01f,4.8f,-9.3f);

    /*** Front ***/
    glColor4f(0, 0, 0, 0.8);
    glNormal3f(0.f,0.5f,-0.5f);
    glVertex3f(-2.8f,4.97f,-8.999f);
    glVertex3f(-2.8f,3.2f,-7.999f);
    glVertex3f(2.8f,3.2f,-7.999f);
    glVertex3f(2.8f,4.97f,-8.999f);

    /*** Back ***/
    glColor4f(0, 0, 0, 0.8);
    glNormal3f(1.f,0.5f,0.5f);
    glVertex3f(-2.8f,4.97f,-18.001f);
    glVertex3f(-2.8f,3.2f,-20.001f);
    glVertex3f(2.8f,3.2f,-20.001f);
    glVertex3f(2.8f,4.97f,-18.001f);

    glEnd();

    glDisable (GL_BLEND);
    glEnable(GL_LIGHTING);
}


/**
 * @brief Car::DrawHeadLights
 * Draw head lights on the car
 */
void Car::DrawHeadLights(){

    /** Headlights settings **/
    GLfloat colorDiffuse5_tab[] = {1.f, 0.01f, 0.01f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDiffuse5_tab);
    GLfloat colorSpeculaire5_tab[] = {0.5f, 0.5f, 0.5f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorSpeculaire5_tab);
    GLfloat shininess5[] = {72};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess5);
    GLfloat colorEmission5_tab[] = {0.3, 0.3, 0.3, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colorEmission5_tab);

    glBegin(GL_QUADS);

    /*** Front ***/
    glColor3ub(255,255,50);
    glNormal3f(0.f,0.f,1.f);
    glVertex3f(-2.5f,2.f,-4.99f);
    glVertex3f(-2.5f,1.f,-4.99f);
    glVertex3f(-1.5f,1.f,-4.99f);
    glVertex3f(-1.5f,2.f,-4.99f);

    glColor3ub(255,255,50);
    glNormal3f(0.f,0.f,1.f);
    glVertex3f(1.5f,2.f,-4.99f);
    glVertex3f(1.5f,1.f,-4.99f);
    glVertex3f(2.5f,1.f,-4.99f);
    glVertex3f(2.5f,2.f,-4.99f);

    glEnd();

    /** Headlights settings **/
    GLfloat colorDiffuse9_tab[] = {1.f, 1.f, 0.01f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorDiffuse9_tab);
    GLfloat colorSpeculaire9_tab[] = {0.5f, 0.5f, 0.5f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colorSpeculaire9_tab);
    GLfloat shininess9[] = {72};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess9);
    GLfloat colorEmission9_tab[] = {0.3, 0.3, 0.3, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colorEmission9_tab);

    glBegin(GL_QUADS);
    /*** Back ***/
    glColor3ub(100,100,50);
    glNormal3f(0.f,0.f,-1.f);
    glVertex3f(-2.5f,2.f,-26.1f);
    glVertex3f(-2.5f,1.f,-26.1f);
    glVertex3f(-1.5f,1.f,-26.1f);
    glVertex3f(-1.5f,2.f,-26.1f);

    glColor3ub(100,100,50);
    glNormal3f(0.f,0.f,-1.f);
    glVertex3f(1.5f,2.f,-26.1f);
    glVertex3f(1.5f,1.f,-26.1f);
    glVertex3f(2.5f,1.f,-26.1f);
    glVertex3f(2.5f,2.f,-26.1f);

    glEnd();



}
