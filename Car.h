#ifndef CAR_H
#define CAR_H

#include <qopengl.h>
#include <GL/glu.h>

/**
 * @brief The Car class
 * Manage car creation and displaying.
 *
 * @param color : RGB color of the car.
 * @param position : current position of the car {x, y, z}.
 */
class Car
{
private:
    GLfloat * color;
    float * position;

public:
    /* Constructor */
    Car(GLfloat * = new GLfloat[3]{0.25f, 0.25f, 0.25f});

    /* Displaying methods */
    void Display(uint64_t);
    static void drawTier(GLUquadric*);
    static void drawGirophare(GLUquadric*, uint64_t);
    void decreaseZ(float decrement) { position[2] = position[2] - decrement; }; // Approach car.

    /* Getters */
    float GetWidth() const { return 6.; }
    float GetHeight() const { return 19.; }
    float * GetPosition() { return position; }

    /* Setters */
    void setPosition(float * pos) { position = pos; }

};

#endif
