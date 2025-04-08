// Star Trek Figures Project
//
//  My Matt Troha

#include <Arduino.h>
#include "LEDControl.h"
#include "PhotoresistorControl.h"
#include "Figures.h"

// TODO CLEAN UP GLOBAL CONSTANTS into config.h
// todo dupe varialbe in ledcontrol
const int LED_PIN = 2;
const int LED_IN_GROUP = 8;
const int NUMBER_OF_FIGS = 7;
const int LED_NUM_TOTAL = NUMBER_OF_FIGS * LED_IN_GROUP;

unsigned long delayLEDon = 1300; // delay LED on from when Fig stopped talking
const int dimmingSteps = 70;     // Number of steps for dimming
const int dimmingDuration = 550; // Total time for dimming in milliseconds

// Initialize the LEDs
LEDControl LEDobj(LED_PIN, LED_NUM_TOTAL);

// Initialize the photoresistor reader
PhotoresistorControl PhotoResObj;

// Num,Thres,R,G,B,W,mux0,mux1,mux2
Figures figArray[] = {
    Figures(0, 100, 0, 0, 122, 122, 0, 0, 0),
    Figures(1, 170, 76, 46, 0, 122, 1, 0, 0),
    Figures(2, 170, 122, 0, 0, 122, 0, 1, 0),
    Figures(3, 135, 122, 0, 0, 122, 1, 1, 0),
    Figures(4, 110, 122, 0, 0, 122, 0, 0, 1),
    Figures(5, 110, 0, 0, 122, 122, 1, 0, 1),
    Figures(6, 175, 76, 46, 0, 122, 0, 1, 1)};

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("Starting Program");

  LEDobj.begin();
  delay(50);

  // simple LED flash to indicated start up
  LEDobj.LEDsAllOff();
  LEDobj.LEDsAllOn();
  delay(2000); // todo modify
  LEDobj.LEDsAllOff();

  PhotoResObj.setPinMode();
}

// ********************************************* LOOP starts

void loop()
{
  for (int i = 0; i < NUMBER_OF_FIGS; i++)
  {

    int photoVal = PhotoResObj.readLightLevel(figArray[i]);
    unsigned long timeRead = millis();
    
    switch (figArray[i].getFigState())
    {
    case LED_OFF_NOT_TALKING: //  do nothing

      // did figure start talking
      if (photoVal > figArray[i].getTALKING_MIN())
      {
        LEDobj.setFigIllum(figArray[i].getFigNum(),
                           figArray[i].getFigColorRed(),
                           figArray[i].getFigColorGreen(),
                           figArray[i].getFigColorBlue(),
                           figArray[i].getFigColorWhite());

        figArray[i].setLastKnowntalkTime(timeRead);
        figArray[i].setFigState(LED_ON_TALKING);
      }
      break;

    case LED_ON_TALKING: //  Figure talking

      if (photoVal > figArray[i].getTALKING_MIN())
      {
        figArray[i].setLastKnowntalkTime(timeRead);
      }
      else
      {
        figArray[i].setFigState(LED_KEEP_ON);
      }

      break;

    case LED_KEEP_ON: //  Figure stay lit for a bit after stop talking

      if (photoVal > figArray[i].getTALKING_MIN())
      {
        figArray[i].setLastKnowntalkTime(timeRead);
        figArray[i].setFigState(LED_ON_TALKING);
      }
      else if (timeRead - figArray[i].getLastKnowntalkTime() > delayLEDon)
      {
        // Dimming
        figArray[i].setFigState(LED_DIMMING);
        figArray[i].setDimmingStep(0);
        figArray[i].setDimStartTime(timeRead);
      }
      break;

    case LED_DIMMING:

      //  Figure stopped talking, led dimming
      if (photoVal > figArray[i].getTALKING_MIN()) // check to if fig started talking
      {
        figArray[i].setLastKnowntalkTime(timeRead);
        figArray[i].setFigState(LED_ON_TALKING);
      }

      if (timeRead - figArray[i].getLastKnowntalkTime() < delayLEDon)
      {
        /* code */ // still in delay period , do nothing  // todo clean up logic to remove this dead zone
      }

      else

          if (figArray[i].getDimmingStep() < dimmingSteps)
      {
        int brightness = 255 * (dimmingSteps - figArray[i].getDimmingStep()) / dimmingSteps;
        LEDobj.setFigIllum(figArray[i].getFigNum(),
                           figArray[i].getFigColorRed() * brightness / 255,
                           figArray[i].getFigColorGreen() * brightness / 255,
                           figArray[i].getFigColorBlue() * brightness / 255,
                           figArray[i].getFigColorWhite() * brightness / 255);

        if (timeRead - figArray[i].getDimStartTime() > (dimmingDuration / dimmingSteps))
        {
          figArray[i].incDimmingStep();
          figArray[i].setDimStartTime(timeRead);
        }
      }
      else

      {
        LEDobj.setFigIllum(figArray[i].getFigNum(), 0, 0, 0, 0);
        figArray[i].setFigState(LED_OFF_NOT_TALKING);
      }
      break;
    }
  }
}
