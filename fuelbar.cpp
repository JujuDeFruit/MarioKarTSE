#include "FuelBar.h"


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

    /* Decrease fuelbar value. */
    Decrease(.2);

    glPushMatrix();

    float * color = value > 30.
            ? new float[3]{34./255., 139./255., 34./255.}
            : new float[3]{255., 0., 0.}; // Set fuel bar color.

    /* Create material */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);

    float x = 5 * (float)value/MAX - 2.5; // Set fuel bar X component.

    /* Draw fuel bar */
    glBegin(GL_QUADS);
    glLoadIdentity();
    glVertex3f(XYZ[0] - 2.5, XYZ[1] + 1.5, XYZ[2] - 10);
    glVertex3f(x, XYZ[1] + 1.5, XYZ[2] - 10);
    glVertex3f(x, XYZ[1] + 1., XYZ[2] - 10);
    glVertex3f(XYZ[0] - 2.5, XYZ[1] + 1., XYZ[2] - 10);
    glEnd();

    glPopMatrix();
}
