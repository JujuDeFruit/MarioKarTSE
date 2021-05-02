#include <qopengl.h>
#include <GL/glu.h>
#include <QGLWidget>


// Classe dediee pour la gestion du sol
class Ground
{
private:
    GLuint* TextureID = new GLuint[3];

    double roadSpeed;
    double grassSpeed;

public:
    // Constructeur avec parametres
    Ground(uint64_t);

    // Destructeur
    ~Ground();

    // Methode d'affichage
    void Display();

    // Getters
    float getRoadWidth() const { return 50.; }
    float getRoadHeight() const {return 200.; }
    float getRoadSpeed() const { return roadSpeed; }
};
