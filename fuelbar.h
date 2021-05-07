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
 * @param XYZ : array of current coordonates of the camera wathing scene.
 */
class FuelBar {
private:
    float value;
    const float MAX = 100.;
    float * XYZ;
public:
    /* Constructor */
    FuelBar(float * CAM_POS) { value = MAX; XYZ = CAM_POS; };

    /* Methods */
    void Decrease(float v) { value -= v; };
    void Fill() { value = MAX; };
    void Display();

    /* Getter */
    float GetValue() const { return value; }
};

#endif // FUELBAR_H
