#ifndef PHOTORESISTORCONTROL_H
#define PHOTORESISTORCONTROL_H

#include <Arduino.h>

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

    int readLightLevel(int m_mux0, int m_mux1, int m_mux2 );
    void setPinMode();
// void setFigToRead(int figNum);
};

#endif // PHOTORESISTORCONTROL_H
