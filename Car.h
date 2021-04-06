#include <qopengl.h>
#include <GL/glu.h>

// Classe dediee pour la gestion de la voiture
class Car
{
public:
    // Constructeur avec parametres
    Car();

    // Destructeur
    ~Car();

    // Methode d'affichage
     void Display(uint64_t iTimeElapsed);
     static void drawTier(GLUquadric* quadrique);
     static void drawGirophare(GLUquadric* quadrique, uint64_t iTimeElapsed);

};
