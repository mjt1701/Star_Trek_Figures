#ifndef PHOTORESISTORCONTROL_H
#define PHOTORESISTORCONTROL_H

#include <Arduino.h>

#include "Figures.h"

class PhotoresistorControl
{
private:
    // Mux control pins for reading photoresistors
    int S0, S1, S2;

    // Mux in "Z" pin
    int Z_PIN;

public:
    PhotoresistorControl();
    int readLightLevel(Figures &m_figObj);
    void setPinMode();
};

#endif // PHOTORESISTORCONTROL_H
