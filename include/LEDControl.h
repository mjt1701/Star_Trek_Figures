#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <Arduino.h>
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
    void LEDsAllOff();
    void LEDsAllOn();
    void setFigureLED(int figruenumberxxx);
    void turnFigOn(int figNum);
    void show();

    void setFigLEDtoIllum();
    void setFigLEDtoIllum2(int m_figNum,int m_red,int m_green,int m_blue,int m_white);


};

#endif // LEDCONTROL_H
