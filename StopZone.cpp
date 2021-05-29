#include "stopzone.h"


/**
 * @brief StopZone::Display
 * Dispalay stop zone next to barrel.
 */
void StopZone::Display()
{
    float xBegin = GetXRange()[0];
    float xEnd = GetXRange()[1];

    float y = 0.;

    float zBegin = GetZRange()[0];
    float zEnd = GetZRange()[1];

    /* Disable lightig and enable transparency. */
    glDisable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Draw stoping zone. */
    glBegin(GL_QUADS);

    /*** Bottom ***/
    glColor4f(150, 0, 0, 0.3);
    glVertex3f(xBegin, y + 0.11, zEnd);
    glVertex3f(xEnd, y + 0.11, zEnd);
    glVertex3f(xEnd, y + 0.11, zBegin);
    glVertex3f(xBegin, y + 0.11, zBegin);

    /*** Front ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(xBegin, y, zBegin);
    glVertex3f(xEnd, y, zBegin);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(xEnd, y + 4.0f, zBegin);
    glVertex3f(xBegin, y + 4.0f, zBegin);


    /*** Left ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(xBegin, y, zBegin);
    glVertex3f(xBegin, y, zEnd);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(xBegin, y + 4.0f, zEnd);
    glVertex3f(xBegin, y + 4.0f, zBegin);

    /*** Right ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(xEnd, y, zBegin);
    glVertex3f(xEnd, y, zEnd);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(xEnd, y + 4.0f, zEnd);
    glVertex3f(xEnd, y + 4.0f, zBegin);

    /*** Back ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(xBegin, y, zEnd);
    glVertex3f(xEnd, y, zEnd);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(xEnd, y + 4.0f, zEnd);
    glVertex3f(xBegin, y + 4.0f, zEnd);

    glEnd();

    /* Enable lighting and disable transparency. */
    glDisable (GL_BLEND);
    glEnable(GL_LIGHTING);
}


/**
 * @brief StopZone::GetXRange
 * Get x range of area.
 */
float * StopZone::GetXRange() const {
    float xBegin = position[0] > 0 ? position[0] - 3 : position[0] + 3;
    float xEnd = position[0] > 0 ? position[0] - 1 - 2 * WIDTH / 3 : position[0] + 1 + 2 * WIDTH / 3;
    return new float[2] {xBegin, xEnd};
}
