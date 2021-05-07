#ifndef BARREL_H
#define BARREL_H

#include <qopengl.h>
#include <GL/glu.h>
#include <QGLWidget>

#include "Ground.h"

/**
 * Manage fuel barrels displayed along the road.
 *
 * @param textureID : contains all textures.
 * @param prevClicked_ : contains event clicked.
 */
class Barrel
{
private:
    GLuint* textureID = new GLuint[1];
    bool prevClicked_ = false;

public:
    Barrel();
    void Display(uint64_t, Ground *, bool);
    static void drawBarrel(GLUquadric *);
    ~Barrel();
};

# endif
