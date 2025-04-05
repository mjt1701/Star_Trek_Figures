#ifndef FIGURES_H
#define FIGURES_H

#include <Arduino.h>

enum figStates
{
  LED_OFF_NOT_TALKING,     //  Setup any initial conditions first time thru
  LED_ON_TALKING,      //  Figure started talking
  LED_KEEP_ON,        //  Figure stay lit for a bit after stop talking
  LED_DIMMING         //  Figure stopped talking, led dimming
                        //  all Figures not taking long enough that prettly lights start ; maybe will need additianal states for tbat
};

// enum figStates figState;

class Figures {
private:
const int figureNumber;
const int TALKING_MIN;
const int FIGURE_RED_VALUE;
const int FIGURE_GREEN_VALUE;
const int FIGURE_BLUE_VALUE;
const int FIGURE_WHITE_VALUE;
//todo mux channel, or does it in photores?? no
figStates figState;
unsigned long lastKnownTalkingTime;
unsigned long dimmingStartTime;
int dimmingStep;


public:
Figures(int m_figNum, int TALKING_MIN,
    int m_red, int m_green, int m_blue, int m_white ) ;

    void didFigureStartTalking(int figureNumber);

int getFigNum();
void getFigColor();






};

#endif // FIGURES_H
