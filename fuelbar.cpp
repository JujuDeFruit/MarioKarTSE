#include "FuelBar.h"

/**
 * Display fuelbar on the screen.
 */
void FuelBar::Display() {

    glPushMatrix();

    value = value <= 0. ? 0. : value; // Limitate min value to 0.

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
