#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <GL/glu.h>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <GL/glu.h>
#include <stdlib.h>
#include <windows.h>

#include "Car.h"
#include "Barrel.h"
#include "FuelBar.h"
#include "StopZone.h"


#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>

#include <cstdio>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

/**
 * @brief The MyGLWidget class
 * Generate and manage OpenGL scene.
 *
 * @param WIN : window size.
 * @param NB_OPPOSITE_CARS : numbers of opposite cars to generate.
 * @param CAM_POS : position {x, y, z} of the camera.
 * @param left_right : translation of main car.
 * @param degree : rotation of main car.
 * @param m_TimeElapsed
 * @param m_AnimationTimer : timer to synchronize on.
 * @param ground : ground pointer.
 * @param barrel : barrel pointers.
 * @param fuelBar : fuel bar pointer.
 * @param car : main car pointer.
 * @param oppositeCars : pointer of pointer of cars to generate opposite cars.
 * @param distBetOppCars : distance between 2 opposite cars.
 * @param m_barrelPressed : check if barrel is clicked or not.
 * @param score : score of the player. Score is increased by 1 for each exceeded opposite car.
 * @param cap : Default video capture.
 * @param hand_cascade : Cascade containning values trained to detect hands.
 * @param frameWidth : Frame width.
 * @param frameHeight : Frame height.
 * @param stop : stop animation bool.
 * @param rightPositions : current right hand positions (vector of points).
 * @param leftPositions : current left hand positions (vector of points).
 * @param error : detection sensibility
 */
class MKWidget : public QOpenGLWidget
{
    Q_OBJECT

private:
    /* Const declaration */
    const unsigned int WIN = 900;
    const unsigned int NB_OPPOSITE_CARS = 3;

    float * CAM_POS = new float[3]{0.,25., 60.};

    float left_right = 0.;
    double degree = 0.;

    float m_TimeElapsed { 0.0f };
    QTimer * m_AnimationTimer;

    StopZone * zone;
    Ground * ground;
    Barrel * barrel;
    FuelBar * fuelBar;
    Car * car;

    Car ** oppositeCars;
    GLfloat distBetOppCars;

    bool m_barrelPressed = false;
    bool activateMove = true;
    bool pause = false;

    int score = 0;
    QElapsedTimer * timer;


    VideoCapture cap;
    CascadeClassifier hand_cascade;
    int frameWidth=640;
    int frameHeight=480;
    bool stop = false;


    vector<Point> leftPositions;
    vector<Point> rightPositions;

    double error = 20;

public:
    /* Constructor */
    MKWidget(QOpenGLWidget * parent = nullptr);

private:
    /* Herited methods from QOpenGLWidget. Overrided methods */
    virtual void initializeGL();
    virtual void resizeGL(int, int);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent *event);

    /* Methods */
    void DisplayMainCar();
    void GenerateCar(unsigned int, bool = false);
    void DisplayCars();
    void CheckCollison();
    void PrintTimer();
    void StopAnimation();
    void PrintPause();
    void Camera();
    void RotationCheck();
    void DrawZonePos(Mat);

private slots:
    void Refresh();

};

# endif
