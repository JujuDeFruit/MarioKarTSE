#ifndef BARREL_H
#define BARREL_H

#include <qopengl.h>
#include <GL/glu.h>
#include <QGLWidget>
#include <time.h>

#include "Ground.h"
#include "StopZone.h"
#include "Car.h"

/**
 * Manage fuel barrels displayed along the road.
 *
 * @param textureID : contains all textures.
 * @param prevClicked_ : contains event clicked.
 */
class Barrel
{
private:
    const int zInitBarrel = -200;
    const int areaSide = 20;

    GLuint* textureID = new GLuint[1];
    bool prevClicked_ = false;
    float xPos, zPos;
    int speed;
    bool created;

    StopZone * stopZone;

public:
    /* Constructor. */
    Barrel();

    /* Methods. */
    void LoadTextures();
    void Display(Ground *, bool, bool);
    void DrawBarrel(GLUquadric *);
    void DrawArea();
    bool CarInStopZone(Car *);

    /* Getter. */
    int GetXPos() const { return xPos; }
    int GetZPos() const { return zPos; }

    /* Destructor. */
    ~Barrel();
};

# endif
