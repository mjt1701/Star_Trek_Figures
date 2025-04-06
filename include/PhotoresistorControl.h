#ifndef PHOTORESISTORCONTROL_H
#define PHOTORESISTORCONTROL_H

#include <Arduino.h>

#include "Figures.h"

class PhotoresistorControl {
private:
    // Mux control pins for reading photoresistors
 int S0;
 int S1;
 int S2;

// Mux in "Z" pin
 int Z_PIN;

public:
    PhotoresistorControl( );

    int readLightLevel(int m_0, int m_1, int m_2);
    int readLL(Figures &m_figObj);
    void setPinMode();
// void setFigToRead(int figNum);
};

#endif // PHOTORESISTORCONTROL_H
