#include "LightControl.h"

int main() {
    LightControl lightControl(2, 1, 512);  // LED pin 2, Photoresistor pin 1, threshold 512

    // Simulate controlling the LED based on light levels
    lightControl.controlLED();  // Will either turn on or off based on light level

    // Adjust threshold if needed
    lightControl.adjustThreshold(600);
    lightControl.controlLED();  // React to the new threshold

    return 0;
}
