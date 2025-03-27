# Star_Trek_Figures
Star Trek Hallmark Storyteller figures from the TOS episode Mirror, Mirror with added lights that illuminate the speaking figure.
The added lights are LEDs that use the lights on the figure's base to signal that the figure is talking and therefore should be illuminated. 
It uses a Arduino Nano to read the figure's light emittance using photoresistors and NeoPixal strip to illumitate the speficic figure. 

  Lights set of WS2812 RGBW LEDs based on lighting of Hallmark Star Trek Figure
  This sketch reads (photoresistor) the base light of each Star Trek figure
  to see if it speaking. If so, it lights the LEDs for that figure.
  Note: "talking" in comments means figure base light (colored base light),
  anytime this is on is "talking". including after sequence is done and lights
  are on but no voice.


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

  Rev 1.20  branch - refactor switch case to enum; created state diagram. 


