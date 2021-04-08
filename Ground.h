#include <qopengl.h>
#include <GL/glu.h>
#include <QGLWidget>


// Classe dediee pour la gestion du sol
class Ground
{
private:
    GLuint* TextureID = new GLuint[3];

public:
    // Constructeur avec parametres
    Ground();

    // Destructeur
    ~Ground();

    // Methode d'affichage
    void Display(uint64_t iTimeElapsed);

    // Getters
    float getRoadWidth() const { return 50.; }
};
