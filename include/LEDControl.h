#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class LEDControl
{
private:
    Adafruit_NeoPixel LEDStrip; // NeoPixel object that controls the strip

public:
    LEDControl(int LED_PIN, int LED_NUM_TOTAL);  //Constructor

    void begin();
    void LEDsAllOff();
    void LEDsAllOn();
    void turnFigOn(int figNum);
    void setFigIllum(int m_figNum,int m_red,int m_green,int m_blue,int m_white);
};

#endif // LEDCONTROL_H
