#include "LEDControl.h"
#include "Figures.h"

// Constructor: Initializes the NeoPixel strip with the specified pin and number of pixels
LEDControl::LEDControl(int pin, int numPixels)
    : LEDStrip(numPixels, pin, NEO_GRBW + NEO_KHZ800) { Serial.println("LED objected created."); }

// Initialize the NeoPixel strip (this will set up the pin and begin communication)
void LEDControl::begin()
{
    LEDStrip.begin();
}

void LEDControl::turnFigOn(int figNum)  //??? what is goal of this method?
{
    LEDStrip.fill(LEDStrip.Color(0, 0, 122, 122),  //??? s it figure based or ALL leds
                  figNum * LED_IN_GROUP, LED_IN_GROUP);
    LEDStrip.show();
}

// ? not used???
void LEDControl::show()
{
    LEDStrip.show();
    Serial.println("LEDControl::show.");
}

// ? not used???
void LEDControl::setFigureLED(int m_figruenumberxxx)
{
    //  getFigureChannel
    //  getFigureColor
    /*
        LEDStrip.fill(LEDStrip.Color(FIGURE_COLOR[inChannel][0], FIGURE_COLOR[inChannel][1],
       FIGURE_COLOR[inChannel][2], FIGURE_COLOR[inChannel][3]),
       inChannel * LED_IN_GROUP, LED_IN_GROUP);
    */
}

// Function to set all LEDs off
void LEDControl::LEDsAllOff()
{
    // Cycle through all LEDs for figure in loop
    for (int i = 0; i < LEDControl::LED_NUM_TOTAL; i++)
    {
        // Set color to zero which is off
        LEDStrip.setPixelColor(i, 0);
    }
    LEDStrip.show();
    Serial.println("All LEDs Off.");
}

// Function to set all LEDs on
void LEDControl::LEDsAllOn()
{
    // Cycle through all LEDs for figure in loop
    for (int i = 0; i < LEDControl::LED_NUM_TOTAL; i++)
    {
        // Set color to
        // todo update color variable
        LEDStrip.setPixelColor(i, 125);
    }
    LEDStrip.show();
    Serial.println("All LEDs On.");
}
//todo do with only the fignum coming thru
void LEDControl::setFigLEDtoIllum(
    int m_figNum, int m_red, int m_green, int m_blue, int m_white)
{
    LEDStrip.fill(LEDStrip.Color(m_red, m_green, m_blue, m_white),
                  m_figNum * LED_IN_GROUP, LED_IN_GROUP);
    LEDStrip.show();
}