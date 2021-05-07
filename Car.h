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
    void decreaseZ(float);

    /* Getters */
    float getWidth() const { return 6.; }
    float getHeight() const { return 19.; }
    float * getPosition() { return position; }

    /* Setters */
    void setPosition(float * pos) { position = pos; }

};

#endif
