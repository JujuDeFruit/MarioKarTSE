#include "Car.h"
#include "Ground.h"
#include "barrel.h"
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <QKeyEvent>
#include <QTimer>

// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QOpenGLWidget
{
public:

    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);

    int W = 1;
    int H = 1;

    double up_down = 30.;
    double left_right = 0.;

    float m_TimeElapsed { 0.0f };
    QTimer m_AnimationTimer;

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent* event);
};
