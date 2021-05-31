#ifndef FUELBAR_H
#define FUELBAR_H

#include <qopengl.h>
#include <GL/glu.h>

/**
 * @brief The FuelBar class
 * Display fuel bar of the car on the screen.
 *
 * @param value : current value (0 - 100) of available fuel in the car.
 * @param MAX : const to maximize fuelbar.
 * @param xyz : array of current coordonates of the camera wathing scene.
 * @param gameOverFuel : determins if fuel is at 0
 */
class FuelBar {
private:
    float value;
    const float MAX = 100.;
    float * xyz;
    bool gameOverFuel = false;
public:
    /* Constructor */
    FuelBar(float * CAM_POS) { value = MAX; xyz = CAM_POS; };

    /* Methods */
    void Decrease(float v);
    void Fill(bool pause) { value = pause ? MAX : value; };
    void Display();

    /* getters */
    bool getGameOver(){return gameOverFuel; };
};

#endif // FUELBAR_H
