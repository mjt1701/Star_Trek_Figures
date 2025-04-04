// Star Trek Figures Project
//
//  My Matt Troha

#include <Arduino.h>
#include "LEDControl.h"
#include "PhotoresistorControl.h"

const int LED_PIN = 2;
const int LED_IN_GROUP = 8;
const int NUMBER_OF_FIGS = 7;
const int LED_NUM_TOTAL = NUMBER_OF_FIGS * LED_IN_GROUP;

// Talking Range (Minimum)
const int TALKING_MIN[7] = {
    100,  // Fig 0 Talking Photo Min
    170,  // Fig 1 Talking Photo Min
    170,  // Fig 2 Talking Photo Min
    135,  // Fig 3 Talking Photo Min
    110,  // Fig 4 Talking Photo Min
    100,  // Fig 5 Talking Photo Min
    200}; // Fig 6 Talking Photo Min

enum figStates
{
  LED_OFF_NOT_TALKING,     //  Setup any initial conditions first time thru
  LED_ON_TALKING,      //  Figure started talking
  LED_KEEP_ON,        //  Figure stay lit for a bit after stop talking
  LED_DIMMING         //  Figure stopped talking, led dimming
                        //  all Figures not taking long enough that prettly lights start ; maybe will need additianal states for tbat
};

//  int figState[] = {0, 0, 0, 0, 0, 0, 0};
enum figStates figState[7];

// color palette for each fig cell
const int FIGURE_COLOR[7][4] = {
    {0, 0, 122, 122}, // Figure 0 blue
    {76, 46, 0, 122}, // Figure 1 gold
    {122, 0, 0, 122}, // Figure 2 red
    {122, 0, 0, 122}, // Figure 3 red
    {122, 0, 0, 122}, // Figure 4 red
    {0, 0, 122, 122}, // Figure 5 blue
    {76, 46, 0, 122}  // Figure 6 gold
};

// factor to reduce brightness each loop when dimming
const int reduceFactor = 20; // in percentage  // ? not needed

// Create instance of NeoPixel class
// Parameter 1 = number of pixels in leds
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
//  Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(LED_NUM_TOTAL, LED_PIN, NEO_GRBW + NEO_KHZ800);

// Mux control pins for photoresistors
// const int S0 =4;
// const int S1 = 5;
// const int S2 = 6;

// Mux in "Z" pin
// const int Z_PIN = A0;

// const unsigned long timeStart = micros(); // ? not needed
// const unsigned long delayLEDon = 4000; // delay LED on from when Fig stopped talking
unsigned long delayLEDon = 1300;  //time that led stays on after figure stops talking
unsigned long lastKnownTalkingTime[7];

const int dimmingSteps = 70;      // Number of steps for dimming
const int dimmingDuration = 550; // Total time for dimming in milliseconds

unsigned long dimmingStartTime[7];
int dimmingStep[7];

// put function declarations here:
int readMux(int channel);
void isFigureNowTalking(int inChannel, int inPhotoVal, unsigned long inTimeRead);

void setup()
{
  // Setup Serial Monitor
    Serial.begin(9600);
     Serial.println("Starting Program");


  // Initialize the LEDs
LEDControl   LEDobj(LED_PIN, LED_NUM_TOTAL);



LEDobj.begin();
  delay(50); // ?  Needed?  not in chatgpt code
  // Clear them all
  LEDobj.clearLEDs();
  // Show the result of clearing the LEDs
  LEDobj.show();
  // todo add a simple LED flash to indicated the figures got the word to start

  
  Serial.println("long delay...");
  delay(90000);

   // Initialize the
    PhotoresistorControl PhotoResObj();

  // Initialize the photoresistor address pins
  // pinMode(S0, OUTPUT);
  // pinMode(S1, OUTPUT);
  // pinMode(S2, OUTPUT);

  // Initialize the Photoresistor address to 000(first one)
  // digitalWrite(S0, LOW);
  // digitalWrite(S1, LOW);
  // digitalWrite(S2, LOW);
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

// read the photoresistor for a
int readMux(int channel)
{
 // int controlPin[] = {S0, S1, S2};

  //?  can this be made global so that it does not have to be created every time thru loop
  //?  is it really created every time thru??   
  // todo make it static const  ;;  MAKE it part of the figure object
  const int muxChannel[8][3] = {
      {0, 0, 0}, // channel 0
      {1, 0, 0}, // channel 1
      {0, 1, 0}, // channel 2
      {1, 1, 0}, // channel 3
      {0, 0, 1}, // channel 4
      {1, 0, 1}, // channel 5
      {0, 1, 1}, // channel 6
      {1, 1, 1}, // channel 7
  };

  // loop through the 3 signal pins
  for (int i = 0; i < 3; i++)
  {
    // todo  change to bit banging  / dont need to now
 //   digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  // todo  change to bit banging / dont need to now
  //int readVal = analogRead(Z_PIN);

 // return readVal;
}


// check if figure started talking and set variables and LEDs
void  isFigureNowTalking(int inChannel, int inPhotoVal, unsigned long inTimeRead)
{
  if (inPhotoVal > TALKING_MIN[inChannel]) // If figure started talking, turn on the color and note the time
  {
    // lastKnownTalkingTime[inChannel] = inTimeRead;
    // ledStrip.fill(ledStrip.Color(FIGURE_COLOR[inChannel][0], FIGURE_COLOR[inChannel][1], 
    //                              FIGURE_COLOR[inChannel][2], FIGURE_COLOR[inChannel][3]), 
    //                              inChannel * LED_IN_GROUP, LED_IN_GROUP);
    // ledStrip.show(); //
    //  figState[inChannel] = LED_ON_TALKING; // now talking
  }
  
}
