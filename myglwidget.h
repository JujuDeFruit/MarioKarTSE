#include "Car.h"

#include "barrel.h"
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <QKeyEvent>
#include <QTimer>

// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QOpenGLWidget
{
private:
    const float CAMERA_Z_POSITION = 60.;
    const unsigned int NB_OPPOSITE_CARS = 3;

    double left_right = 0.;

    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;

    Ground * ground;
    Barrel * barrel;
    Car * car;

    Car ** oppositeCars;
    GLfloat distBetOppCars;

public:
    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);

private:
    // Fonction d'initialisation
    void initializeGL();
    // Fonction de redimensionnement
    void resizeGL(int width, int height);
    // Fonction d'affichage
    void paintGL();
    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent* event);
    // Generate car coming from opposite side
    void generateCar(unsigned int, bool = false);
    // Display opposite cars
    void displayCars();
    // Check if there is a collision
    void checkCollison();
};
