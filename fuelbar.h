#ifndef FUELBAR_H
#include <qopengl.h>
#include <GL/glu.h>
#define FUELBAR_H

class FuelBar {
private:
    float value;
    const float MAX = 100.;
    float * XYZ;
public:
    FuelBar(float * CAM_POS) { value = MAX; XYZ = CAM_POS; };
    void Decrease(float v) { value -= v; };
    void Fill() { value = MAX; };
    void Display();
    float GetValue() const { return value; }
};

#endif // FUELBAR_H
