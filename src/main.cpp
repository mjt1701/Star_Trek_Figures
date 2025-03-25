#include <Arduino.h>

// put function declarations here:
// int myFunction(int, int);

/*
  Star Trek Project
  Lights set of WS2812 RGBW LEDs based on lighting of Hallmark Star Trek Figure
  This sketch reads (photoresistor) the base light of each Star Trek figure
  to see if it speaking. If so, it lights the LEDs for that figure.
  Note: "talking" in comments means figure base light (colored base light),
  anytime this is on is "talking". including after sequence is done and lights
  are on but no voice.
  My Matt Troha

  Revision History
  Rev 1.0 and prior
  General testing of QW2812 lights
  hardware is set for two cells of 2 strips of 4 pixel leds

  Rev 1.1
  general upkeep

  Rev 1.2
  cleaned up varialbe init

  Rev 1.3
  change Serial Monitor output to table form

  Rev 1.4
  make lights respond to photoread

  Rev 1.5
  added each fig respondes separately

  Rev 1.6
  make figColor an array

  Rev 1.7
  change figState algroritm to use mapping instead of switch case

  Rev 1.8
  change numFig to 7
  add figColor for all 7
  fixed brightness calculation

  Rev 1.9
  change photo calibration from color-based to individual figure-based
  fixed brighness calcualtion and dimming

  Rev 1.9.1
  remove all serial prints

 Rev 1.10
 change to timing for LED on lag time

  Rev 1.11
  Restructure to use Case and fix up the light timing

  Rev 1.11
  Restructure beginning of loop
  Remove (comment) the serial.print testing

  Rev 1.12
  Change LED.fill calls from two calls (each side) to one call (all 8 at once)

  Rev 1.13
  Added red/blue/gold color palette for lighiting of fig. Add array.

  Rev 1.14 Picking up from long ago. some minor changes as we get back into it

  Rev 1.15 Split On Case into a) On, still talking and b) on, not talking.
           Light on after talking for a bit
           and deleted a lot of old serial.print and useless comments

  Rev 1.16  Added LED fade when done talking (during the time after talking but light still on)

  Rev 1.2   Moved to VS Code / PlatfomrIO source control, added adafruit neopixel lib to project

*/

// Include Adafruit NeoPixel Library
#include <Adafruit_NeoPixel.h>

// Define Arduino connection pin for LED data
const int ledPin = 2;

// Define nubmer of LEDs in a group (one side)
const int ledInGroup = 8;

// Define the number of Figures
// Use x for test, 7 for production
const int numFigs = 7;

// Define the number of LEDs  7 figs -> 7*2*4=56
const int ledNum = numFigs * ledInGroup;

// Talking Range (Minimum)
const int talkingMin[7] = {
    100,  // Fig 0 Talking Photo Min
    170,  // Fig 1 Talking Photo Min
    170,  // Fig 2 Talking Photo Min
    135,  // Fig 3 Talking Photo Min
    110,  // Fig 4 Talking Photo Min
    100,  // Fig 5 Talking Photo Min
    300}; // Fig 6 Talking Photo Min

// Define Figure State for each figure and initialize to 0 for each
//  0       Off  or init
//  1       On, still talking
//  2       On, not talking, lights still on
int figState[] = {0, 0, 0, 0, 0, 0, 0};

// color palette for each fig cell
const int figColor[7][4] = {
    {0, 0, 122, 122}, // Figure 0 blue
    {76, 46, 0, 122}, // Figure 1 gold
    {122, 0, 0, 122}, // Figure 2 red
    {122, 0, 0, 122}, // Figure 3 red
    {122, 0, 0, 122}, // Figure 4 red
    {0, 0, 122, 122}, // Figure 5 blue
    {76, 46, 0, 122}  // Figure 6 gold
};

//  brighness factor for each fig cell // ! the number in the table must be divided also
int figBrightFactor[] = {100, 100, 100, 100, 100, 100, 100}; // ? not needed

// factor to reduce brightness each loop
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
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(ledNum, ledPin, NEO_GRBW + NEO_KHZ800);

// Mux control pins for photoresistors
const int s0 = 4;
const int s1 = 5;
const int s2 = 6;

// Mux in "Z" pin
const int Z_pin = A0; // new added const

const unsigned long timeStart = micros(); // ? not needed
// const unsigned long delayLEDon = 4000; // delay LED on from when Fig stopped talking
unsigned long delayLEDon = 950;
unsigned long timeFigStartedTalking[7];

const int dimmingSteps = 20;      // Number of steps for dimming
const int dimmingDuration = 1000; // Total time for dimming in milliseconds

unsigned long dimmingStartTime[7];
int dimmingStep[7];

// put function declarations here:

int readMux(int channel);

void clearLEDs();

void setup()
{
  // Setup Serial Monitor
  //  Serial.begin(9600);
  //   Serial.println("Starting Program");

  // Initialize the LEDs
  ledStrip.begin();
  delay(50); // ?  Needed?  not in chatgpt code
  // Clear them all
  clearLEDs();
  // Show the result of clearing the LEDs
  ledStrip.show();

  // Initialize the photoresistor address pins
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);

  // Initialize the Photoresistor address to 000(first one)
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
}

// ********************************************* LOOP starts

void loop()
{
  // Loop through each figure
  for (int i = 0; i < numFigs; i++)
  {
    // Read the photoresistor for this figure
    int photoVal = readMux(i);
    unsigned long timeRead = millis();

    switch (figState[i])
    {
    case 0: // Off not talking

      if (photoVal > talkingMin[i]) // If figure started talking, turn on the color and note the time
      {
        timeFigStartedTalking[i] = timeRead;
        figState[i] = 1; // now talking

        ledStrip.fill(ledStrip.Color(figColor[i][0], figColor[i][1], figColor[i][2], figColor[i][3]), i * ledInGroup, ledInGroup);
        ledStrip.show(); //
      }
      break;

    case 1: // case 1 On,  talking

      if (photoVal > talkingMin[i]) //  is figure is still talking
      {
        timeFigStartedTalking[i] = timeRead; //  reset begin timer countdown for turning off light
        // todo does state need updated?  dont think so, still talking is still talking
        // todo reset ??? for delay ligths
      }

      else //  figure has stopped talking (LED still on)
        figState[i] = 2;

      dimmingStep[i] = 0;             // Reset dimming step
      dimmingStartTime[i] = timeRead; // Start dimming

      {
        break;

      case 2: //  case 2 On, not talking  , dimming

        if (timeRead - timeFigStartedTalking[i] < delayLEDon)
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
                              figColor[i][0] * brightness / 255,
                              figColor[i][1] * brightness / 255,
                              figColor[i][2] * brightness / 255,
                              figColor[i][3] * brightness / 255),
                          i * ledInGroup, ledInGroup);
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
            ledStrip.fill(ledStrip.Color(0, 0, 0, 0), i * ledInGroup, ledInGroup);
            figState[i] = 0; // Reset to off state
          }
        }
        break;

      default:
        break;
      }
      // end of figure if
    }

  } // end loop
}

// read the photoresistor for a
int readMux(int channel)
{
  int controlPin[] = {s0, s1, s2};

  //?  can this be made global so that it does not have to be created every time thru loop
  //?  is it really created every time thru??
  // todo make it static
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
    // todo  change to bit banging
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  // todo  change to bit banging
  // int readVal = 0;
  int readVal = analogRead(Z_pin);

  return readVal;
}

// Function to set all LEDs off
void clearLEDs()
{
  // Cycle through all LEDs for figure in loop
  for (int i = 0; i < ledNum; i++)
  {
    // Set color to zero which is off
    ledStrip.setPixelColor(i, 0);
  }
}