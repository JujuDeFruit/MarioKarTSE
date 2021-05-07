#ifndef GROUND_H
#define GROUND_H

#include <qopengl.h>
#include <GL/glu.h>
#include <QGLWidget>


/**
 * @brief The Ground class
 * Generate and manage ground displaying on the screen.
 *
 * @param textureID : Array containning all textures to print ground.
 * @param roadSpeed : current speed of the road.
 * @param grassSpeed : current speed of the grass.
 */
class Ground
{
private:
    GLuint* textureID = new GLuint[3];
    double roadSpeed;
    double grassSpeed;

public:
    /* Contructor */
    Ground(uint64_t);

    /* Methods */
    void Display();

    /* Getters */
    float getRoadWidth() const { return 50.; }
    float getRoadHeight() const {return 200.; }
    float getRoadSpeed() const { return roadSpeed; }

    /* Destructor */
    ~Ground();
};

#endif
