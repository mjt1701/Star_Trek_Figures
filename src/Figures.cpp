//  Figures.cpp

#include "Figures.h"

// Constructor: Initializes the NeoPixel strip with the specified pin and number of pixels
Figures::Figures(int m_figNum, int m_min,
                 int m_red, int m_green, int m_blue, int m_white,
                 int m_mux0, int m_mux1, int m_mux2)
    : figureNumber(m_figNum),
      TALKING_MIN(m_min),
      FIGURE_RED_VALUE(m_red),
      FIGURE_GREEN_VALUE(m_green),
      FIGURE_BLUE_VALUE(m_blue),
      FIGURE_WHITE_VALUE(m_white),
      figState(LED_OFF_NOT_TALKING),
      MMUX0(m_mux0),
      MMUX1(m_mux1),
      MMUX2(m_mux2) {};

int Figures::getFigNum() { return figureNumber; }
int Figures::getFigColorRed() { return FIGURE_RED_VALUE; }
int Figures::getFigColorGreen() { return FIGURE_GREEN_VALUE; }
int Figures::getFigColorBlue() { return FIGURE_BLUE_VALUE; }
int Figures::getFigColorWhite() { return FIGURE_WHITE_VALUE; }

void Figures::setFigBrightness(int m_brght) { Figures::figureBrightness = m_brght; }
int Figures::getFigBrightness() { return figureBrightness; }

int Figures::getFigMux0() { return MMUX0; }
int Figures::getFigMux1() { return MMUX1; }
int Figures::getFigMux2() { return MMUX2; }

figStates Figures::getFigState() { return figState; }
void Figures::setFigState(figStates m_figState)
{
        Figures::figState = m_figState;
}

int Figures::getTALKING_MIN() { return TALKING_MIN; }

void Figures::setLastKnowntalkTime(unsigned long m_lastTime)
{
        Figures::lastKnownTalkingTime = m_lastTime ;
}
unsigned long Figures::getLastKnowntalkTime()
{
        return lastKnownTalkingTime;
}

void Figures::setDimmingStep(int m_dimStep)
{
        Figures::dimmingStep = m_dimStep;
}
int Figures::getDimmingStep()
{
        return dimmingStep;
}

void Figures::setDimStartTime(unsigned long m_dimTime)
{
        dimmingStartTime = m_dimTime;
}
unsigned long Figures::getDimStartTime()
{
        return dimmingStartTime;
}

void Figures::incDimmingStep() {dimmingStep++;}

