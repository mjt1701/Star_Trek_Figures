#include "LEDControl.h"

 // Constructor: Initializes the NeoPixel strip with the specified pin and number of pixels
 LEDControl::LEDControl(int pin, int numPixels)
: LEDStrip(numPixels, pin, NEO_GRBW + NEO_KHZ800) {}

// Initialize the NeoPixel strip (this will set up the pin and begin communication)
void LEDControl::begin() {
    LEDStrip.begin();
LEDStrip.show();  // Initialize all pixels to 'off'
}   

/*
this will need to grab the color of the selected ifgure
    void LEDControl::setColor(const std::string& newColor) {
    color = newColor;
    Serial.print("LED color set to: ") ;
    Serial.println("pput some variable here");
}
*/



void LEDControl::setFigureTalking(int m_figruenumberxxx){
    //  getFigureChannel 
    //  getFigureColor
  
    LEDStrip.fill(LEDStrip.Color(FIGURE_COLOR[inChannel][0], FIGURE_COLOR[inChannel][1], 
    FIGURE_COLOR[inChannel][2], FIGURE_COLOR[inChannel][3]), 
    inChannel * LED_IN_GROUP, LED_IN_GROUP);

}



// Function to set all LEDs off
void LEDControl::clearLEDs()  
{
  // Cycle through all LEDs for figure in loop
  for (int i = 0; i < LEDControl::LED_NUM_TOTAL; i++)
  {
    // Set color to zero which is off
    LEDStrip.setPixelColor(i, 0);
  }
  LEDStrip.show(); 
}


