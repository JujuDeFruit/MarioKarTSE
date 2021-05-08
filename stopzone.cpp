#include "stopzone.h"


/**
 * @brief StopZone::StopZone
 * Constructor of StopZone object.
 *
 */

StopZone::StopZone()
{
}

StopZone::~StopZone()
{
}


void StopZone::Display()
{
    /* disable lightig and enable transparency */
    glDisable(GL_LIGHTING);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* draw stoping zone */
    glBegin(GL_QUADS);

    /*** Bottom ***/
    glColor4f(150, 0, 0, 0.3);
    glVertex3f(-5.0f,0.11f,25.f);
    glVertex3f(5.0f,0.11f,25.f);
    glVertex3f(5.0f,0.11f,0.f);
    glVertex3f(-5.0f,0.11f,0.f);

    /*** Front ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(-5.0f, 0.0f,0.0f);
    glVertex3f(5.0f, 0.0f,0.0f);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(5.0f, 4.0f,0.0f);
    glVertex3f(-5.0f, 4.0f,0.0f);


    /*** Left ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(-5.0f,0.0f,0.f);
    glVertex3f(-5.0f,0.0f,25.f);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(-5.0f,4.0f,25.f);
    glVertex3f(-5.0f,4.0f,0.f);

    /*** Right ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(5.0f,0.0f,0.f);
    glVertex3f(5.0f,0.0f,25.f);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(5.0f,4.0f,25.f);
    glVertex3f(5.0f,4.0f,0.f);

    /*** Back ***/
    glColor4f(150, 0, 0, 0.8);
    glVertex3f(-5.0f, 0.0f,25.0f);
    glVertex3f(5.0f, 0.0f,25.0f);
    glColor4f(150, 0, 0, 0.1);
    glVertex3f(5.0f, 4.0f,25.0f);
    glVertex3f(-5.0f, 4.0f,25.0f);

    glEnd();

    /* enable lighting and disable transparency */
    glDisable (GL_BLEND);
    glEnable(GL_LIGHTING);
}
