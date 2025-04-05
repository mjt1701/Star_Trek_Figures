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

enum figStates figState;

class Figures {
private:
int figureNumber;
int TALKING_MIN;
int FIGURE_RED_VALUE;
int FIGURE_GREEN_VALUE;
int FIGURE_BLUE_VALUE;
int FIGURE_WHITE_VALUE;
figStates figState;
unsigned long lastKnownTalkingTime;
unsigned long dimmingStartTime;
int dimmingStep;


public:
Figures(int m_figNum, 
    int m_red, int m_green, int m_blue, int m_white ) ;

    void didFigureStartTalking(int figureNumber);

};

#endif // FIGURES_H
