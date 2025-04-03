#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#include "LEDControl.h"
#include "PhotoresistorControl.h"

class LightControl {
private:
    LEDControl ledControl;
    PhotoresistorControl photoControl;

public:
    LightControl(int ledPin, int photoPin, int threshold = 512);

    void controlLED();
    void adjustThreshold(int newThreshold);
};

#endif // LIGHTCONTROL_H
