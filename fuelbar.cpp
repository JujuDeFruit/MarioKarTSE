#include "fuelbar.h"

/*
 * Display fuelbar on the screen.
 *
 * @return void
 */
void FuelBar::Display() {

    glPushMatrix();

    value = value <= 0. ? 0. : value;

    float * color = value > 30.
            ? new float[3]{34./255., 139./255., 34./255.}
            : new float[3]{255., 0., 0.};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);

    float x = 5 * (float)value/MAX - 2.5;

    glBegin(GL_QUADS);
    glLoadIdentity();
    glVertex3f(XYZ[0] - 2.5, XYZ[1] + 1.5, XYZ[2] - 10);
    glVertex3f(x, XYZ[1] + 1.5, XYZ[2] - 10);
    glVertex3f(x, XYZ[1] + 1., XYZ[2] - 10);
    glVertex3f(XYZ[0] - 2.5, XYZ[1] + 1., XYZ[2] - 10);
    glEnd();

    glPopMatrix();
}
