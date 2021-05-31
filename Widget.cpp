#include "Widget.h"
#include <QtMath>


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
    connect(m_AnimationTimer, SIGNAL(timeout()),this, SLOT(Refresh()));
    m_AnimationTimer->start();

    /* Initialize arrays of pointers of cars */
    oppositeCars = new Car*[NB_OPPOSITE_CARS];

    /* Generate random seed */
    srand(time(0));

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


    /* Camera */
    cap = VideoCapture(0); // open the default camera
    if(!cap.isOpened()) { // check if we succeeded
        cerr << "Error openning the default camera" << endl;
    }


    if(!hand_cascade.load( "../mario-kartse/fist3.xml" )) {
        cerr << "Error loading haarcascade" << endl;
        std::cerr<<"Error openning the default camera"<<std::endl;
        exit(0);
    }

    /* Init output window */
    camFrame = new QLabel(this);
    camFrame->resize(2*width()/5,2*height()/5);
    camFrame->move(width()/2-camFrame->width()/2,height()-camFrame->height());
}


/**
 * @brief MKWidget::~MKWidget
 * Destructor
 */
MKWidget::~MKWidget() {
    delete m_AnimationTimer;
    delete zone;
    delete ground;
    delete barrel;
    delete fuelBar;
    delete car;
    delete oppositeCars;
    delete timer;
}


/**
 * Refresh the window
 */
void MKWidget::Refresh(){
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
 *
 * @param QPaintEvent : paint event
 */
void MKWidget::paintEvent(QPaintEvent *)
{   
    /*Camera part */
    Camera();

    /* OpenGL part */

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

    /* Set camera
    camX camY camZ targetX targetY targetZ vecX vecY vecZ. */
    gluLookAt(CAM_POS[0], CAM_POS[1], CAM_POS[2],0.,0.,0.,0.,1.,0.);

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


    /* Painter to print text on screen. */
    PrintTimer();

    if (pause){
        PrintPause();
    }
    else if (gameOver){
        PrintGameOver();
        car->SetPosition(new float[3] { 0, 0., 0. });
    }
    else if (colision){
        PrintGameOver();
        car->SetPosition(new float[3] { 0, 0., 0. });
    }
    else if (fuelBar->GetGameOver()){
        PrintGameOver();
        car->SetPosition(new float[3] { 0, 0., 0. });
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

    switch(event->key()) {
    /* Move car to left side, and make sure car does not get out of the road. */
    case Qt::Key_Left:
        left_right = left_right - carWidth / 2 > - roadWidth / 2 && activateMove ? left_right - 2. : gameOver = true;
        car->SetPosition(new float[3] { left_right, 0., 0. });
        degree = activateMove ? 3 : degree;
        break;

        /* Move car to right side, and make sure car does not get out of the road. */
    case Qt::Key_Right:
        left_right = left_right + carWidth / 2 < roadWidth / 2 && activateMove ? left_right + 2. : gameOver = true;
        car->SetPosition(new float[3] { left_right, 0., 0. });
        degree  = activateMove ? -3 : degree;
        break;

    case Qt::Key_P:
        pause = true;
        StopAnimation();
        break;

    case Qt::Key_Q:
        exit(0);

    case Qt::Key_R:
        score = 0;
        timer->restart();
        fuelBar->Fill(!(pause));
        for (int i = 0; i < NB_OPPOSITE_CARS; i++) GenerateCar(i, true);
        gameOver = false;
        colision = false;
        break;

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
    if (!event->isAutoRepeat()) degree = 0;
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
            activateMove = true;
            m_AnimationTimer->start();
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
    float percentOfXRoad = (rand() % 100 + 1) / 100.;

    GLfloat * scopeRoad = new GLfloat[2] { (car->GetWidth() - ground->GetRoadWidth())/2, (ground->GetRoadWidth() - car->GetWidth())/2 };

    /* Set the opposite car position. */
    float * pos = new float[3];
    pos[0] = scopeRoad[0] + percentOfXRoad * (scopeRoad[1] - scopeRoad[0]);
    pos[1] = 1.;
    distBetOppCars = (ground->GetRoadHeight() + CAM_POS[2]) * (i + 1 + NB_OPPOSITE_CARS)/NB_OPPOSITE_CARS;
    /* If initialisation of game, generate other car further */
    pos[2] = !init ? ground->GetRoadHeight() : distBetOppCars;

    /* Create opposite car and set position. */
    Car * oppositeCar = new Car(color);
    oppositeCar->SetPosition(pos);

    /* Fill array. */
    *(oppositeCars + i) = oppositeCar;

    /* If a new car was generated and it was not an initialization of the scene, then increase score. */
    score = init || gameOver ? score : score + 1;
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
    float zCarPos = -13;

    /* Check for all opposite cars. */
    for (unsigned int i = 0; i < NB_OPPOSITE_CARS; i++) {

        float * oppPos = oppositeCars[i]->GetPosition();

        float zOpp = -oppPos[2];

        /* Check for collisions with main car. */
        if (
            ((zOpp + oppositeCars[i]->GetHeight() >= zCarPos - car->GetHeight()
              && zOpp + oppositeCars[i]->GetHeight() <= zCarPos)
             || (zOpp >= zCarPos - car->GetHeight() && zOpp <= zCarPos))
            && ((oppPos[0] <= xCarPos
                 && oppPos[0] + oppositeCars[i]->GetWidth() > xCarPos)
                ||( oppPos[0] < xCarPos + car->GetWidth()
                    && oppPos[0] + oppositeCars[i]->GetWidth() >= xCarPos + car->GetWidth()))
            ) {
            colision = true;
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
    painter.setPen(Qt::red);

    QFont font("Arial", 30);
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
    painter.setBrush(Qt::gray);
    QRectF rectangle(width() / 4, height()/3, width()/2, height()/3);
    painter.drawRoundedRect(rectangle, 20.0, 15.0);
    painter.setPen(Qt::white);

    QFont font("Arial", 70);
    painter.setFont(font);
    painter.drawText(width() / 3, height() / 2, QString("Pause"));

    QFont font2("Arial", 15);
    painter.setFont(font2);
    painter.drawText(width() / 3, 3*height() /5, QString("Press P to resume"));
    painter.end();
}


/**
 * @brief MKWidget::PrintGameOver
 * Print game over on screen.
 */
void MKWidget::PrintGameOver()
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::gray);
    QRectF rectangle(width() / 4, height()/3, width()/2, height()/3);
    painter.drawRoundedRect(rectangle, 20.0, 15.0);
    painter.setPen(Qt::red);

    QFont font("Monospace", 30);
    painter.setFont(font);
    painter.drawText(width() / 3, height() / 2, QString("Game over"));

    QFont font3("Monospace", 10);
    painter.setFont(font3);
    painter.drawText(width() / 3, 2*height() / 5, QString("Your score : ") + QString::number(score));

    QFont font2("Monospace", 15);
    painter.setPen(Qt::white);
    painter.setFont(font2);
    painter.drawText(width() / 3, 3*height() /5, QString("Press R to resume"));
    painter.end();
}


/**
 * Stop all movement in the scene.
 */
void MKWidget::StopAnimation(){
    if(m_AnimationTimer->isActive()) {
        m_AnimationTimer->stop();
        activateMove = false;
    }
    else {
        m_AnimationTimer->start();
        activateMove = true;
        pause = false;
    }
}


/**
 * Turn to the left or right based on hand positions
 */
void MKWidget::RotationCheck(){

    const float carWidth = car->GetWidth();
    const float roadWidth = ground->GetRoadWidth();

    /* Get last detected elements */
    Point leftPosition = leftPositions.back();
    Point rightPosition = rightPositions.back();

    /* Turn left */
    if ((leftPosition.y - rightPosition.y) > error){

        /* Move to the left */
        left_right = left_right - carWidth / 2 > - roadWidth / 2 && activateMove ? left_right - 1. : gameOver = true;
        car->SetPosition(new float[3] { left_right, 0., 0. });
        degree = activateMove ? 3 : degree;

        /* Remove the point */
        leftPositions.pop_back();
        rightPositions.pop_back();
    }

    /* Turn right */
    if ((rightPosition.y - leftPosition.y) > error){

        /* Move to the right */
        left_right = left_right + carWidth / 2 < roadWidth / 2 && activateMove ? left_right + 1. : gameOver = true;
        car->SetPosition(new float[3] { left_right, 0., 0. });
        degree  = activateMove ? -3 : degree;

        /* Remove the point */
        leftPositions.pop_back();
        rightPositions.pop_back();

    }
}


/**
 * Draw delimitations on the camera
 * @param frame : matrix containning frame infos to draw
 */
void MKWidget::DrawZonePos(Mat frame){
    rectangle(frame, Point(frameWidth / 3, frameHeight / 3), Point(2 * frameWidth / 3, 2 * frameHeight / 3), Scalar(255, 0, 0), 2, LINE_8);

    putText(frame, "left", Point(5, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(200, 200, 200), 2);

    putText(frame, "right", Point(2 * frameWidth / 3 + 5, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(200, 200, 200), 2);

    putText(frame, "Place both your hands inside the box while in", Point(20, frameHeight / 4 - 40), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(200, 200, 200), 2);
    putText(frame, "a stop zone to brake", Point(frameWidth / 3 - 5, frameHeight / 4 + 20), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(200, 200, 200), 2);
}


/**
 * Display webcam
 */
void MKWidget::Camera() {

    Mat frame,frame_gray;
    vector<Rect> hands;
    /* Get frame */
    cap >> frame;
    /* Mirror effect */
    flip(frame,frame,1);
    /* Convert to gray */
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

    /* Detect hands */
    hand_cascade.detectMultiScale(frame_gray, hands, 1.1, 4, 0, Size(60, 60));

    DrawZonePos(frame);

    if (hands.size()>0 && hands.size()<3 ){  // limit to 2 hands

        // Draw green rectangle
        for (int i=0;i<(int)hands.size();i++){

            // check if hand on the left side of screen
            if (hands[i].x<= (frameWidth/3 - hands[i].width) ){
                rectangle(frame,hands[i],Scalar(0,255,0),2);

                // Add the left hand coordinants to the list
                Point p;
                p.x = hands[i].x;
                p.y = hands[i].y;
                leftPositions.push_back(p);
            }

            // check if hand on the right side of the screen
            if (hands[i].x>=(2*frameWidth/3)){
                rectangle(frame,hands[i],Scalar(0,0,255),2);

                // Add the Right hand coordinants to the list
                Point p;
                p.x = hands[i].x;
                p.y = hands[i].y;
                rightPositions.push_back(p);
            }


            // check if the hand is in the center box of the screen
            if ((hands[i].x>(frameWidth/3 - hands[i].width )) && (hands[i].x < (2*frameWidth/3))
                  && (hands[i].y>(frameHeight/3))  && (hands[i].y <(2*frameHeight/3))
                    && (int)hands.size()==2
                    ){
                rectangle(frame,hands[i],cv::Scalar(255,0,0),2);

                if(barrel->CarInStopZone(car)){
                    degree = 0;
                    m_AnimationTimer->stop();
                    activateMove = false;            
                }
            }
        }

        if (!(leftPositions.empty()) && !(rightPositions.empty())){
            RotationCheck();
        }

    }
    else {
        degree = 0;
    }

    /* Displays frame */
    Mat displayFrame;
    frame.copyTo(displayFrame);

    QImage qImage(displayFrame.data, displayFrame.cols, displayFrame.rows, displayFrame.step, QImage::Format_BGR888);
    QPixmap qPix = QPixmap::fromImage(qImage);

    camFrame->setPixmap(qPix.scaled(camFrame->width(), camFrame->height(), Qt::KeepAspectRatio));
}
