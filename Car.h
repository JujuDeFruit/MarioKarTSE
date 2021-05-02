#include <qopengl.h>
#include <GL/glu.h>

// Classe dediee pour la gestion de la voiture
class Car
{
private:
    GLfloat * color; // Color of the car
    float * position; // Position of the car on the road (x axis)

public:
    // Constructeur avec parametres
    Car(GLfloat * = new GLfloat[3]{0.25f, 0.25f, 0.25f});

    // Destructeur
    ~Car();

    // Methode d'affichage
     void Display(uint64_t);
     static void drawTier(GLUquadric*);
     static void drawGirophare(GLUquadric*, uint64_t);
     void decreaseZ(float);

     //Getter
     float getWidth() const { return 6.; }
     float getHeight() const { return 19.; }
     float * getPosition() { return position; }

     // Setter
     void setPosition(float * pos) { position = pos; }

};
