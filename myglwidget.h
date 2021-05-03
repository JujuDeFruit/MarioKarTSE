#include "Car.h"
#include "barrel.h"
#include "fuelbar.h"

#include <QOpenGLWidget>
#include <GL/glu.h>
#include <QKeyEvent>
#include <QTimer>

// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QOpenGLWidget
{
private:
    // Const declaration
    const unsigned int WIN = 900;
    const unsigned int NB_OPPOSITE_CARS = 3;

    float * CAM_POS = new float[3]{0.,25., 60.};

    double left_right = 0.;

    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;

    Ground * ground;
    Barrel * barrel;
    FuelBar * fuelBar;
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
    void PrintTimer();
};
