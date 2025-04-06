// Star Trek Figures Project
//
//  My Matt Troha

#include <Arduino.h>
#include "LEDControl.h"
#include "PhotoresistorControl.h"
#include "Figures.h"

// TODO CLEAN UP GLOBAL CONSTANTS into config.h
//   look at ledcontrol especially
const int LED_PIN = 2;
const int LED_IN_GROUP = 8;
const int NUMBER_OF_FIGS = 8;
const int LED_NUM_TOTAL = NUMBER_OF_FIGS * LED_IN_GROUP;

//  todo needed???
// factor to reduce brightness each loop when dimming
const int reduceFactor = 20; // in percentage  // ? not needed

// delay LED on from when Fig stopped talking
unsigned long delayLEDon = 1300;
//  unsigned long lastKnownTalkingTime[7];

const int dimmingSteps = 70;     // Number of steps for dimming
const int dimmingDuration = 550; // Total time for dimming in milliseconds

unsigned long dimmingStartTime[7];
int dimmingStep[7];

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("Starting Program");

  // Initialize the LEDs
  LEDControl LEDobj(LED_PIN, LED_NUM_TOTAL);
  LEDobj.begin();
  delay(50);

  // simple LED flash to indicated start up
  LEDobj.LEDsAllOff();
  LEDobj.LEDsAllOn(); // todo chanhe to flash
  delay(2000);
  LEDobj.LEDsAllOff();

  Serial.println("after startup flash...");

  // Initialize the photoresistor reader
  PhotoresistorControl PhotoResObj;
  PhotoResObj.setPinMode();

  // figNum,figThres,R,G,B,W,mux0,mux1,mux2
  Figures figArray[] = {
      Figures(0, 100, 0, 0, 122, 122, 0, 0, 0),
      Figures(1, 170, 76, 46, 0, 122, 1, 0, 0),
      Figures(2, 170, 122, 0, 0, 122, 0, 1, 0),
      Figures(3, 135, 122, 0, 0, 122, 1, 1, 0),
      Figures(4, 110, 122, 0, 0, 122, 0, 0, 1),
      Figures(5, 110, 0, 0, 122, 122, 1, 0, 1),
      Figures(6, 175, 76, 46, 0, 122, 1, 1, 1)};

  Serial.println("array with 7 objects has been created.");

  //  ------   TEST FOR LOOP---------

  for (int i; i < NUMBER_OF_FIGS; i++)
  {
    // Read the photoresistor for this figure
    int photoVal = PhotoResObj.readLightLevel(
        figArray[i].getFigMux0(),
        figArray[i].getFigMux1(),
        figArray[i].getFigMux2());
    Serial.println(photoVal);
    photoVal = PhotoResObj.readLL(figArray[i]);
    Serial.println(photoVal);

    unsigned long timeRead = millis();
    Serial.println(timeRead);

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

      Serial.print("in case 1...");
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

      Serial.print("in case 2...");
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

      Serial.print("in case 3...");

      break;

    case LED_DIMMING:                              //  Figure stopped talking, led dimming
      if (photoVal > figArray[i].getTALKING_MIN()) // check to if fig started talking
      {
        figArray[i].setLastKnowntalkTime(timeRead);
        figArray[i].setFigState(LED_ON_TALKING);
      }
      else if (figArray[i].getDimmingStep() < dimmingSteps)
      {
        int brightness = 255 * (dimmingSteps - figArray[i].getDimmingStep()) / dimmingSteps;
        LEDobj.setFigIllum(figArray[i].getFigNum(),
                           figArray[i].getFigColorRed() * brightness / 255,
                           figArray[i].getFigColorGreen() * brightness / 255,
                           figArray[i].getFigColorBlue() * brightness / 255,
                           figArray[i].getFigColorWhite() * brightness / 255);
      }

      else if (timeRead - figArray[i].getDimStartTime() > (dimmingDuration / dimmingSteps))
      {
        figArray[i].incDimmingStep();
        figArray[i].setDimStartTime(timeRead);
      }

      else

      {
        LEDobj.setFigIllum(figArray[i].getFigNum(), 0, 0, 0, 0);
        figArray[i].setFigState(LED_OFF_NOT_TALKING);
      }

      Serial.print("in case 4...");
      break;
    }
  }

  Serial.println("in long delay...");
  delay(90000);
}

// ********************************************* LOOP starts

void loop()
{

  /*


    // Loop through each figure
    for (int i = 0; i < NUMBER_OF_FIGS; i++)
    {
      // Read the photoresistor for this figure
      int photoVal = readMux(i);
      unsigned long timeRead = millis();

      switch (figState[i])
      {
      case LED_OFF_NOT_TALKING:
      isFigureNowTalking( i, photoVal, timeRead);
        break;

      case LED_ON_TALKING: //  On,  talking

        if (photoVal > TALKING_MIN[i]) //  is figure is still talking
        {
          lastKnownTalkingTime[i] = timeRead;
        }

        else //  figure has stopped talking (LED still on)
        {
          figState[i] = LED_KEEP_ON;
        }
        break;

      case LED_KEEP_ON: //  On, stopped talking, so that ligiht is not choppy when cont talking
  // todo need to see if figure started talking again
  isFigureNowTalking( i, photoVal, timeRead);

        if (timeRead - lastKnownTalkingTime[i] < delayLEDon)
        {
          // Still in the delay period, do nothing
        }
        else
        {
          figState[i] = LED_DIMMING;
          dimmingStep[i] = 0;             // Reset dimming step
          dimmingStartTime[i] = timeRead; // Start dimming
        }

      case LED_DIMMING: //  On, not talking  , dimming
  isFigureNowTalking( i, photoVal, timeRead);

        if (timeRead - lastKnownTalkingTime[i] < delayLEDon)   // todo  is this needed??? taken care of just above??
        {
          // Still in the delay period, do nothing
        }
        else
        {
          // Start dimming process
          if (dimmingStep[i] < dimmingSteps)
          {
            // Calculate the brightness based on the current dimming step
            int brightness = 255 * (dimmingSteps - dimmingStep[i]) / dimmingSteps;
            ledStrip.fill(ledStrip.Color(
                              FIGURE_COLOR[i][0] * brightness / 255,
                              FIGURE_COLOR[i][1] * brightness / 255,
                              FIGURE_COLOR[i][2] * brightness / 255,
                              FIGURE_COLOR[i][3] * brightness / 255),
                              i * LED_IN_GROUP, LED_IN_GROUP);
            ledStrip.show();

            // Check if it's time to move to the next dimming step
            if (timeRead - dimmingStartTime[i] >= (dimmingDuration / dimmingSteps))
            {
              dimmingStep[i]++;
              dimmingStartTime[i] = timeRead; // Reset the timer for the next step
            }
          }
          else
          {
            // Turn off the lights when dimming is complete
            ledStrip.fill(ledStrip.Color(0, 0, 0, 0), i * LED_IN_GROUP, LED_IN_GROUP);
            figState[i] = LED_OFF_NOT_TALKING; // Reset to off state
          }
        }
        break;

      default:
        break;
      }
      // end of figure if
    }
  */

} // end loop

// todo  change to bit banging / dont need to now

// check if figure started talking and set variables and LEDs
// void isFigureNowTalking(int inChannel, int inPhotoVal, unsigned long inTimeRead)
// {
//   if (inPhotoVal > TALKING_MIN[inChannel]) // If figure started talking, turn on the color and note the time
//  {
// lastKnownTalkingTime[inChannel] = inTimeRead;
// ledStrip.fill(ledStrip.Color(FIGURE_COLOR[inChannel][0], FIGURE_COLOR[inChannel][1],
//                              FIGURE_COLOR[inChannel][2], FIGURE_COLOR[inChannel][3]),
//                              inChannel * LED_IN_GROUP, LED_IN_GROUP);
// ledStrip.show(); //
//  figState[inChannel] = LED_ON_TALKING; // now talking
// }
