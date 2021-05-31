#include "FuelBar.h"
#include "math.h"
#include <QtMath>


/**
 * @brief FuelBar::Decrease
 * Decrease fuel bar value and limitate to 0.
 * @param decrement : value of the decrement.
 */
void FuelBar::Decrease(float decrement) {
    value = value - decrement <= 0. ? 0. : value; // Limitate min value to 0.

    /* Exit if fuel bar is empty */
    if (value == 0.0) exit(0);

    /* Decrease fuael bar value. */
    value -= decrement;
}


/**
 * Display fuelbar on the screen.
 */
void FuelBar::Display() {
    glDisable(GL_LIGHTING);
    /* Decrease fuelbar value. */
    Decrease(.2);

    glPushMatrix();

    float x = 5 * (float)value/MAX - 2.5; // Set fuel bar X component.

    /* Draw fuel bar */
    glBegin(GL_QUADS);

    glLoadIdentity();

    if( value >= 60.) {glColor3f(0.1, 1, 0.1);}
    else if (value < 60. && value >= 30.) {glColor3f(1, 1, 0.1);}
    else{glColor3f(1, 0.1, 0.1);}

    glVertex3f(xyz[0] - 2.5, xyz[1] + 1.5, xyz[2] - 10);
    glVertex3f(x, xyz[1] + 1.5, xyz[2] - 10);
    glVertex3f(x, xyz[1] + 1., xyz[2] - 10);
    glVertex3f(xyz[0] - 2.5, xyz[1] + 1., xyz[2] - 10);
    glEnd();
    glPopMatrix();


    /* back of fuel bar */
    glPushMatrix();
    glBegin(GL_QUADS);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.1, 0.1, 0.1);
    glVertex3f(xyz[0] - 2.5, xyz[1] + 1.5, xyz[2] - 10);
    glVertex3f(5 * (float)MAX/MAX - 2.5, xyz[1] + 1.5, xyz[2] - 10);
    glVertex3f(5 * (float)MAX/MAX - 2.5, xyz[1] + 1., xyz[2] - 10);
    glVertex3f(xyz[0] - 2.5, xyz[1] + 1., xyz[2] - 10);
    glEnd();
    glPopMatrix();


    glEnable(GL_LIGHTING);
}



