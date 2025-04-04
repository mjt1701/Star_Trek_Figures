#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <Adafruit_NeoPixel.h>

class LEDControl
{
private:
    const int LED_PIN = 2;
    const int LED_IN_GROUP = 8;
    const int NUMBER_OF_FIGS = 7; // todo move to main
    const int LED_NUM_TOTAL = NUMBER_OF_FIGS * LED_IN_GROUP;
    Adafruit_NeoPixel LEDStrip; // NeoPixel object that controls the strip

public:
    LEDControl(int LED_PIN, int LED_NUM_TOTAL);  //Constructor

    void begin();
    void clearLEDs();
    void setFigureLED(int figruenumberxxx);
    void turnFigOn(int figNum);
    void show();
};

#endif // LEDCONTROL_H
