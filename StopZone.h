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
private:
    /* Dimensions of area. */
    const float width = 25.;
    const float heigth = 10.;

    /* Current position of the barrel. */
    float * position;

public:
    /* Constructor. */
    StopZone() { position = new float[3]; }

    /* Methods. */
    void Display();

    /* Setter. */
    void setPosition(float * newPosition) { position = newPosition; }

    /* Getter. */
    float * GetPosition() const { return position; }
};

#endif // STOPZONE_H
