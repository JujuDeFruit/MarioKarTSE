#include <qopengl.h>
#include <GL/glu.h>
#include <QGLWidget>

// Classe dediee pour la gestion des bidon
class Barrel
{
public:
    // Constructeur avec parametres
    Barrel();

    // Destructeur
    ~Barrel();

    // Methode d'affichage
     void Display(uint64_t iTimeElapsed);
     static void drawBarrel(GLUquadric* quadrique);

private:
    GLuint* TextureID = new GLuint[1];

};


