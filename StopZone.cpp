#include "stopzone.h"


/**
 * @brief StopZone::Display
 * Dispalay stop zone next to barrel.
 */
void StopZone::Display()
{
    float xBegin = position[0] > 0 ? position[0] - 3 : position[0] + 3;
    float xEnd = position[0] > 0 ? position[0] - 1 - 2*width/3 : position[0] + 1 + 2*width/3;
    float y = 0.;
    float z = position[2];

    /* Disable lightig and enable transparency. */
    glDisable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Draw stoping zone. */
    glBegin(GL_QUADS);

    /*** Bottom ***/
    glColor4f(150, 0, 0, 0.3);
    glVertex3f(xBegin, y+0.11, z + heigth / 2);
    glVertex3f(xEnd, y+0.11, z + heigth / 2);
    glVertex3f(xEnd, y+0.11, z - heigth / 2);
    glVertex3f(xBegin, y+0.11, z - heigth / 2);

    /*** Front ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(xBegin, y, z - heigth / 2);
    glVertex3f(xEnd, y, z - heigth / 2);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(xEnd, y + 4.0f, z - heigth / 2);
    glVertex3f(xBegin, y + 4.0f, z - heigth / 2);


    /*** Left ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(xBegin, y, z - heigth / 2);
    glVertex3f(xBegin, y, z + heigth / 2);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(xBegin, y + 4.0f, z + heigth / 2);
    glVertex3f(xBegin, y + 4.0f, z - heigth / 2);

    /*** Right ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(xEnd, y, z - heigth / 2);
    glVertex3f(xEnd, y, z + heigth / 2);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(xEnd, y + 4.0f, z + heigth / 2);
    glVertex3f(xEnd, y + 4.0f, z - heigth / 2);

    /*** Back ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(xBegin, y, z + heigth / 2);
    glVertex3f(xEnd, y, z + heigth / 2);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(xEnd, y + 4.0f, z + heigth / 2);
    glVertex3f(xBegin, y + 4.0f, z + heigth / 2);

    glEnd();

    /* Enable lighting and disable transparency. */
    glDisable (GL_BLEND);
    glEnable(GL_LIGHTING);
}
