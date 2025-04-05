#include "Figures.h"

// Constructor: Initializes the NeoPixel strip with the specified pin and number of pixels
Figures::Figures(int m_figNum, 
        int m_red, int m_green, int m_blue, int m_white ) 
: figureNumber(m_figNum),
FIGURE_RED_VALUE(m_red),
 FIGURE_GREEN_VALUE(m_green),
 FIGURE_BLUE_VALUE(m_blue),
 FIGURE_WHITE_VALUE(m_white),
 figState(LED_OFF_NOT_TALKING)
 {};

 void Figures::didFigureStartTalking(int figureNumber) {
// stuff 
Serial.println("fig started talking...");
 }
