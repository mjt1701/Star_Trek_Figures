#ifndef PHOTORESISTORCONTROL_H
#define PHOTORESISTORCONTROL_H

class PhotoresistorControl {
private:
    // Mux control pins for photoresistors
 int S0;
 int S1;
 int S2;

// Mux in "Z" pin
 int Z_PIN;

public:
    PhotoresistorControl( );

    void readLightLevel();
    void setPinMode();
void setFigToRead(int figNum);
};

#endif // PHOTORESISTORCONTROL_H
