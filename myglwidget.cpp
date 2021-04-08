#include "myglwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <GL/glu.h>

// Declarations des constantes
const unsigned int WIN = 900;

// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN, WIN);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    // Timer pour le clignotement
        // Connexion du timer
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        m_TimeElapsed += 1.0f;
        update();
    });

    m_AnimationTimer.setInterval(15);
    m_AnimationTimer.start();
}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    // changer la couleur du fond
    glClearColor(0.5f,0.5f,0.5f,1.0f); // gris

    glEnable(GL_DEPTH_TEST);

    // Light activation
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // ambiant lignt
    GLfloat light_color_tab[] = { 1.f, 1.f, 1.f, 0.f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color_tab);

    GLfloat light_tab[] = { 0.f, 2.f, 0.f, 1.f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_tab);

}


// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
    W = width;
    H = height;
}

// Fonction d'affichage
void MyGLWidget::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Reinitialisation de la matrice courante
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                           // affecter la matrice identité à la matrice courante
    gluPerspective(70.f, W/H, 0.1f, 500.f);

    glMatrixMode(GL_MODELVIEW);                 // pour placer nos objets dans un monde 3D
    glLoadIdentity();

    // Placer la caméra
             //camX camY camZ cibleX cibleY cibleZ vecX vecY vecZ
    gluLookAt(0.,25.,60.,0.,0.,0.,0.,1.,0.);

    //gluLookAt(0.,0.2,60.,0.,0.,0.,0.,1.,0.);

    // Affichage des bidon
    barrel = new Barrel();
    barrel->Display(m_TimeElapsed);

    // Affichage de la route
    ground = new Ground();
    ground->Display(m_TimeElapsed);

    // Affichage de la voiture
    glTranslated(left_right ,1., up_down);

    car = new Car();
    car->Display(m_TimeElapsed);
}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    const float roadWidth = ground->getRoadWidth();
    const float carWidth = car->getWidth();

    switch(event->key())
    {
        // Move car to left side, and make sure car does not get out of the road
        case Qt::Key_Left:
              left_right = left_right - carWidth / 2 > - roadWidth / 2 ? left_right - 2. : left_right;
              break;

        // Move car to right side, and make sure car does not get out of the road
        case Qt::Key_Right:
              left_right = left_right + carWidth / 2 < roadWidth / 2 ? left_right + 2. : left_right;
              break;

        // Cas par defaut
        default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    update();
}
