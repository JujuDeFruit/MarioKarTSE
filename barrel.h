#include <qopengl.h>
#include <GL/glu.h>
#include <QGLWidget>
#include "Ground.h"

// Classe dediee pour la gestion des bidon
class Barrel
{
private:
    GLuint* TextureID = new GLuint[1];
    bool prevClicked_ = false;

public:
    // Constructeur avec parametres
    Barrel();

    // Destructeur
    ~Barrel();

    // Methode d'affichage
     void Display(uint64_t, Ground *, bool);
     static void drawBarrel(GLUquadric *);

};


