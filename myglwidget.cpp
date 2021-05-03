#include "myglwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <GL/glu.h>
#include <stdlib.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>

/*
 * Constructor of main openGL Widget
 *
 * @param parent : parent widget
 */
MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent)
{
    // Window settings
    setFixedSize(WIN, WIN);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    // Set interval to refresh window
    connect(&m_AnimationTimer,  &QTimer::timeout, [&] {
        m_TimeElapsed += 1.0f;
        update();
    });

    // Initialize arrays of pointers of cars
    oppositeCars = new Car*[NB_OPPOSITE_CARS];

    // Generate random seed
    std::srand(time(0));
    // Generate cars and fill array
    for(unsigned int i = 0; i < NB_OPPOSITE_CARS; i++) generateCar(i, true);

    m_AnimationTimer.setInterval(15);
    m_AnimationTimer.start();

    fuelBar = new FuelBar(CAM_POS);
}


/*
 * Overriding OpenGL initialization method
 *
 * @return void
 */
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


/*
 * Overriding OpenGL resizing window method.
 *
 * @params width : window width
 * @params height : window height
 * @return void
 */
void MyGLWidget::resizeGL(int width, int height)
{
    // Viewport definiton, printing area
    glViewport(0, 0, width, height);
}


/*
 * Overriding OpenGL printing method
 *
 * @return void
 */
void MyGLWidget::paintGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Reinitialisation de la matrice courante
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                           // affecter la matrice identité à la matrice courante
    gluPerspective(70.f, 1, 0.1f, 500.f);

    glMatrixMode(GL_MODELVIEW);                 // pour placer nos objets dans un monde 3D
    glLoadIdentity();

    // Set the camera
             //camX camY camZ cibleX cibleY cibleZ vecX vecY vecZ
    gluLookAt(CAM_POS[0], CAM_POS[1], CAM_POS[2],0.,0.,0.,0.,1.,0.);
    //gluLookAt(0.,150., 0,0.,0.,0.,0.,0.,1.);

    // Display road
    ground = new Ground(m_TimeElapsed);
    ground->Display();

    // Display barrels
    barrel = new Barrel();
    barrel->Display(m_TimeElapsed, ground);

    fuelBar->Decrease(.2);
    fuelBar->Display();
    if (fuelBar->GetValue() == 0.0) exit(0);

    glPushMatrix();
    // Print main car
    glTranslated(left_right ,1., 0.);

    car = new Car();
    car->Display(m_TimeElapsed);
    glPopMatrix();

    displayCars();

    checkCollison();
}


/*
 * Keyboard interaction method
 *
 * @param event : key pressed event
 * @return void
 */
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


/*
 * Generate car coming from opposite side
 *
 * @param i : index of array to generate car
 * @param init : boolean to set initialisation of the game or not
 * @return void
 */
void MyGLWidget::generateCar(unsigned int i, bool init) {

        GLfloat * color = new GLfloat[3] { 1., 0., 0. };

        // Get random percent of the road (0% left side of the road; 10% right side of the road)
        float percentOfXRoad = (std::rand() % 100 + 1) / 100.;

        GLfloat * scopeRoad = new GLfloat[2] { (car->getWidth() - ground->getRoadWidth())/2, (ground->getRoadWidth() - car->getWidth())/2};

        // Set the opposite car position
        float * pos = new float[3];
        pos[0] = scopeRoad[0] + percentOfXRoad * (scopeRoad[1] - scopeRoad[0]);
        pos[1] = 1.;
        distBetOppCars = (ground->getRoadHeight() + CAM_POS[2]) * (i + 1 + NB_OPPOSITE_CARS)/NB_OPPOSITE_CARS;
        // If initialisation of game, generate other car further
        pos[2] = !init ? ground->getRoadHeight() : distBetOppCars;

        Car * oppositeCar = new Car(color);
        oppositeCar->setPosition(pos);

        *(oppositeCars + i) = oppositeCar;
}


/*
 * Display opposite cars stored in oppositeCars array
 *
 * @return void
 */
void MyGLWidget::displayCars() {

    // For all cars stored in array
    for(unsigned int i = 0; i < NB_OPPOSITE_CARS; i++) {
        // Save main matrix
        glPushMatrix();
        // Rotate car
        glRotatef(180, 0, 1, 0);

        // Get car in array
        Car * currentCar = *(oppositeCars + i);
        // Decrease car's depth
        currentCar->decreaseZ(ground->getRoadSpeed() + 3.5);
        float * pos = currentCar->getPosition();

        if(pos[2] <  - CAM_POS[2]) generateCar(i);

        // Translate position matrix
        glTranslated(pos[0], pos[1], pos[2]);
        // Resfresh car printing
        currentCar->Display(m_TimeElapsed);

        // Load main matrix
        glPopMatrix();
    }
}


/*
 * Check if there is colision cars
 *
 * @return void
 */
void MyGLWidget::checkCollison() {
    /* Get main car current position */
    float xCarPos = -left_right; // Invert pos to compare to opposite
    float zCarPos = -18.;

    for (unsigned int i = 0; i < NB_OPPOSITE_CARS; i++) {

        float * oppPos = oppositeCars[i]->getPosition();

        if (
                (-oppPos[2] - oppositeCars[i]->getHeight() >= zCarPos - car->getHeight()/2
                 && -oppPos[2] - oppositeCars[i]->getHeight() <= zCarPos + car->getHeight()/2.
                 ||-oppPos[2] + oppositeCars[i]->getHeight() >= zCarPos - car->getHeight()/2
                 && -oppPos[2] + oppositeCars[i]->getHeight() <= zCarPos + car->getHeight()/2)
                && (oppPos[0] <= xCarPos
                 && oppPos[0] + oppositeCars[i]->getWidth() > xCarPos
                 || oppPos[0] < xCarPos + car->getWidth()
                 && oppPos[0] + oppositeCars[i]->getWidth() >= xCarPos + car->getWidth())
            ) {
                exit(0);
        }
    }
}


void MyGLWidget::PrintTimer()
{
  /*glColor3f(1., 1., 1.);
  glRasterPos2f(0, 0);
  char * timer, font;
  for (int i = 0; i < (int)strlen(timer); i++) {
    glutBitmapCharacter(font, timer[i]);
  }*/
}
