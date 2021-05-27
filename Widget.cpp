#include "Widget.h"

#include <iostream>


/**
 * Constructor of main openGL Widget
 *
 * @param parent : parent widget
 */
MKWidget::MKWidget(QOpenGLWidget * parent):QOpenGLWidget(parent)
{
    /* Window settings */
    setFixedSize(WIN, WIN);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    m_AnimationTimer = new QTimer(this);
    /* Create and set timer */
    m_AnimationTimer->setInterval(15);
    connect(m_AnimationTimer, SIGNAL(timeout()),this, SLOT(refresh()));
    m_AnimationTimer->start();

    /* Initialize arrays of pointers of cars */
    oppositeCars = new Car*[NB_OPPOSITE_CARS];

    /* Generate random seed */
    std::srand(time(0));

    /* Generate cars and fill array of opposite cars */
    for(unsigned int i = 0; i < NB_OPPOSITE_CARS; i++) GenerateCar(i, true);

    /* Create ground. */
    ground = new Ground();

    /* Create main car. */
    car = new Car();

    /* Create fuel bar */
    fuelBar = new FuelBar(CAM_POS);

    /* Create barrel */
    barrel = new Barrel();

    /* Start timer. */
    timer = new QElapsedTimer();
    timer->start();

}

/**
 * Refresh the window
 */
void MKWidget::refresh(){
    m_TimeElapsed += 1.0f;
    update();
}


/**
 * Overriding OpenGL initialization method
 */
void MKWidget::initializeGL()
{
    /* Change background color */
    glClearColor(0.5f,0.5f,0.5f,1.0f); // grey

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                           // Load identity matrix and set it as current.
    gluPerspective(70.f, 1, 0.1f, 500.f);

    /* Light activation */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);


    /* Ambiant light */
    GLfloat light_color_tab[] = { 1.f, 1.f, 1.f, 0.f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color_tab);

    GLfloat light_tab[] = { 0.f, 2.f, 0.f, 1.f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_tab);

}


/**
 * Overriding OpenGL resizing window method.
 *
 * @param width : window width
 * @param height : window height
 */
void MKWidget::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                           // Load identity matrix and set it as current.
    gluPerspective(70.f, 1, 0.1f, 500.f);

    /* Viewport definiton, printing area */
    glViewport(0, 0, width, height);
}


/**
 * Overriding paintEvent printing method.
 */

void MKWidget::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.beginNativePainting();


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);                 // Set items in 3D representation.
    glLoadIdentity();

    // Set camera
             //camX camY camZ targetX targetY targetZ vecX vecY vecZ.
    gluLookAt(CAM_POS[0], CAM_POS[1], CAM_POS[2],0.,0.,0.,0.,1.,0.);
    //gluLookAt(0., 150., 0.,0.,0.,0.,0.,1.,0.);

    /* Display ground. */
    ground->Display(m_TimeElapsed);

    /* Display fuel bar */
    fuelBar->Display();

    DisplayMainCar();

    /* Display opposite cars and check for collisions. */
    DisplayCars();
    CheckCollison();

    barrel->Display(ground, m_barrelPressed, activateMove, pause);
    m_barrelPressed = false;

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    painter.endNativePainting();
    glDisable(GL_DEPTH_TEST);


    /* painter to print text on screen. */
    PrintTimer();

    if (pause){
       PrintPause();
    }

}

/**
 * Keyboard interaction method
 *
 * @param event : key pressed event
 */
void MKWidget::keyPressEvent(QKeyEvent * event)
{
    const float roadWidth = ground->GetRoadWidth();
    const float carWidth = car->GetWidth();

    switch(event->key())
    {
        /* Move car to left side, and make sure car does not get out of the road. */
        case Qt::Key_Left:
              left_right = left_right - carWidth / 2 > - roadWidth / 2 && activateMove ? left_right - 2. : left_right;
              car->setPosition(new float[3] { left_right, 0., 0. });
              degree = activateMove ? 3 : degree;
              break;

        /* Move car to right side, and make sure car does not get out of the road. */
        case Qt::Key_Right:
              left_right = left_right + carWidth / 2 < roadWidth / 2 && activateMove ? left_right + 2. : left_right;
              car->setPosition(new float[3] { left_right, 0., 0. });
              degree  = activateMove ? -3 : degree;
              break;

        case Qt::Key_P:

            if(barrel->CarInStopZone(car)){
                StopAnimation();
            }else{
                pause = true;
                StopAnimation();
            }

            break;

        case Qt::Key_Q:
              exit(0);

        /* Default case. */
        default:
        {
            /* Ignore event. */
            event->ignore();
            return;
        }
    }

    /* Accept event and update scene */
    event->accept();
    update();
}


/**
 * Keyboard interaction method
 *
 * @param event : key release event
 */
void MKWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat())
    {
        degree = 0;
    }

}


/**
 * @brief MKWidget::mousePressEvent
 * Override mousPressEvent method.
 * @param event : mouse press event.
 */
void MKWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        GLint hits;
        GLuint selectBuf[512];
        glSelectBuffer(512, selectBuf);

        glRenderMode(GL_SELECT);
        glInitNames();
        glPushName(0);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        gluPickMatrix(event->x(), (viewport[3] - event->y()), 5.0, 5.0, viewport);

        gluPerspective(70.f, width()/height(), 0.1f, 300.f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        /* camX camY camZ targetX targetY targetZ vecX vecY vecZ. */
        gluLookAt(0.,25.,60.,0.,0.,0.,0.,1.,0.);

        glLoadName(1);

        /* Draw a drum shaped figure at the drums placement to be clicked. */
        GLUquadric* quadrique = gluNewQuadric();
        gluQuadricDrawStyle(quadrique, GLU_FILL);

        glPushMatrix();
        glTranslated(barrel->GetXPos(), 5.f, barrel->GetZPos());
        barrel->DrawBarrel(quadrique);
        glPopMatrix();

        gluDeleteQuadric(quadrique);

        glFlush();

        hits = glRenderMode(GL_RENDER);
        if (hits == 1){
            m_barrelPressed = true;
            fuelBar->Fill(!(pause));
            event->accept();
            update();
        }
    }
}


/**
 * @brief DisplayMainCar
 * Display main car on screen.
 */
void MKWidget::DisplayMainCar() {
    glPushMatrix();
    /* Print main car */
    glTranslated(left_right ,1., 0.);
    glRotated(degree, 0 ,1., 0.);

    /* Main car */;
    car->Display(m_TimeElapsed, true);
    glPopMatrix();
}


/**
 * Generate car coming from opposite side.
 *
 * @param i : index of array to generate car
 * @param init : boolean to set initialisation of the game or not
 */
void MKWidget::GenerateCar(unsigned int i, bool init) {

        GLfloat * color = new GLfloat[3] { static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX) };

        /* Get random percent of the road (0% left side of the road; 10% right side of the road). */
        float percentOfXRoad = (std::rand() % 100 + 1) / 100.;

        GLfloat * scopeRoad = new GLfloat[2] { (car->GetWidth() - ground->GetRoadWidth())/2, (ground->GetRoadWidth() - car->GetWidth())/2};

        /* Set the opposite car position. */
        float * pos = new float[3];
        pos[0] = scopeRoad[0] + percentOfXRoad * (scopeRoad[1] - scopeRoad[0]);
        pos[1] = 1.;
        distBetOppCars = (ground->GetRoadHeight() + CAM_POS[2]) * (i + 1 + NB_OPPOSITE_CARS)/NB_OPPOSITE_CARS;
        /* If initialisation of game, generate other car further */
        pos[2] = !init ? ground->GetRoadHeight() : distBetOppCars;

        /* Create opposite car and set position. */
        Car * oppositeCar = new Car(color);
        oppositeCar->setPosition(pos);

        /* Fill array. */
        *(oppositeCars + i) = oppositeCar;

        /* If a new car was generated and it was not an initialization of the scene, then increase score. */
        score = init ? score : score + 1;
}


/**
 * Display opposite cars stored in oppositeCars array.
 */
void MKWidget::DisplayCars() {

    /* For all cars stored in array. */
    for(unsigned int i = 0; i < NB_OPPOSITE_CARS; i++) {
        /* Save main matrix. */
        glPushMatrix();
        /* Rotate car. */
        glRotatef(180, 0, 1, 0);

        /* Get car in array. */
        Car * currentCar = *(oppositeCars + i);

        /* Decrease car's depth. */
        if(activateMove){
            currentCar->DecreaseZ(ground->GetRoadSpeed() + 3.5);
        }

        float * pos = currentCar->GetPosition();

        if(pos[2] <  - CAM_POS[2]) GenerateCar(i);

        /* Translate position matrix. */
        glTranslated(pos[0], pos[1], pos[2]);
        /* Resfresh car printing. */
        currentCar->Display(m_TimeElapsed, false);

        /* Load main matrix. */
        glPopMatrix();
    }
}


/**
 * Check if there is colision cars.
 */
void MKWidget::CheckCollison() {
    /* Get main car current position */
    float xCarPos = -left_right; // Invert pos to compare to opposite
    float zCarPos = -18.;

    /* Check for all opposite cars. */
    for (unsigned int i = 0; i < NB_OPPOSITE_CARS; i++) {

        float * oppPos = oppositeCars[i]->GetPosition();

        /* Check for collisions with main car. */
        if (
                ((-oppPos[2] - oppositeCars[i]->GetHeight() >= zCarPos - car->GetHeight()/2
                 && -oppPos[2] - oppositeCars[i]->GetHeight() <= zCarPos + car->GetHeight()/2.)
                 || (-oppPos[2] + oppositeCars[i]->GetHeight() >= zCarPos - car->GetHeight()/2
                 && -oppPos[2] + oppositeCars[i]->GetHeight() <= zCarPos + car->GetHeight()/2))
                && ((oppPos[0] <= xCarPos
                 && oppPos[0] + oppositeCars[i]->GetWidth() > xCarPos)
                 ||( oppPos[0] < xCarPos + car->GetWidth()
                 && oppPos[0] + oppositeCars[i]->GetWidth() >= xCarPos + car->GetWidth()))
            ) {
                exit(0);
        }
    }
}


/**
 * @brief MKWidget::PrintTimer
 * Print timer on screen.
 */
void MKWidget::PrintTimer()
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    /* New painter to print text on screen. */
    painter.setPen(Qt::black);

    QFont font("Monospace", 30);
    painter.setFont(font);

    painter.drawText(width() / 10, height() / 20, QString("Score : ") + QString::number(score) + QString(" pts"));
    painter.drawText(width() / 2, height() / 20, QString("Timer : ") + QString::number(timer->elapsed() / 1000) + QString(" sec"));

    painter.end();
}

/**
 * @brief MKWidget::PrintPause
 * Print Pause on screen.
 */
void MKWidget::PrintPause()
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);

    QFont font("Monospace", 70);
    painter.setFont(font);
    painter.drawText(width() / 3, height() / 2, QString("Pause"));

    QFont font2("Monospace", 15);
    painter.setFont(font2);
    painter.drawText(width() / 3, 2*height() /3, QString("Press P to resume"));
    painter.end();
}



/**
 * Stop all movement in the scene.
 */
void MKWidget::StopAnimation(){
    if(m_AnimationTimer->isActive())
    {
          m_AnimationTimer->stop();
          activateMove = false; 
    }
    else
    {
        m_AnimationTimer->start();
        activateMove = true;
        pause = false;
    }

}




