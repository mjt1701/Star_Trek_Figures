#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

const int LED_PIN = 2;
const int LED_IN_GROUP = 8;
const int NUMBER_OF_FIGS = 7;
const int LED_NUM_TOTAL = NUMBER_OF_FIGS * LED_IN_GROUP;

unsigned long delayLEDon = 1300; // delay LED on from when Fig stopped talking
const int dimmingSteps = 70;     // Number of steps for dimming
const int dimmingDuration = 550; // Total time for dimming in milliseconds

#endif // CONFIG_H
