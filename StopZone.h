#ifndef STOPZONE_H
#define STOPZONE_H

#include <qopengl.h>
#include <GL/glu.h>

/**
 * @brief The StopZone class
 * Display stop zones for the cas on the screen.
 *
 */

class StopZone
{
public:
    /* Constructor */
    StopZone();
    ~StopZone();

    /* Methods */
    void Display();
};

#endif // STOPZONE_H
