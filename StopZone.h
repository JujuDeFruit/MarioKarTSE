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
    const float WIDTH = 25.;
    const float HEIGHT = 15.;

    /* Current position of the barrel. */
    float * position;

public:
    /* Constructor. */
    StopZone() { position = new float[3]; }

    /* Methods. */
    void Display();

    /* Setter. */
    void SetPosition(float * newPosition) { position = newPosition; }

    /* Getters. */
    float * GetPosition() const { return position; }
    float * GetXRange() const;
    float * GetZRange() const { return new float[2] {position[2] - 2 * HEIGHT / 3, position[2] + 2 * HEIGHT / 3 }; }
    float * GetAreaDimensions() const { return new float[2] { WIDTH, HEIGHT }; }

};

#endif // STOPZONE_H
