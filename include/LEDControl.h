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
    // Constructor: Initializes the strip with the given pin and number of pixels
    LEDControl(int LED_PIN, int LED_NUM_TOTAL);

    void begin();
    void setColor(const std::string &newColor);

    bool getState() const; // todo delete??  leddoes not have state
    void clearLEDs();
    void setFigureTalking( int figruenumberxxx)

};

#endif // LEDCONTROL_H
