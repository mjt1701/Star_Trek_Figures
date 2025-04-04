#include <iostream>

class LightControl {
private:
    LEDControl ledControl;                // LEDControl object
    PhotoresistorControl photoControl;    // PhotoresistorControl object

public:
    // Constructor to initialize the LED and photoresistor control objects
    LightControl(int ledPin, int photoPin, int threshold = 512)
        : ledControl(ledPin), photoControl(photoPin, threshold) {}

    // Method to control the LED based on the photoresistor reading
    void controlLED() {
        photoControl.readLightLevel();  // Read the light level from the photoresistor
        
        // Turn LED on if the light level is below the threshold, otherwise turn it off
        if (photoControl.isLightBelowThreshold()) {
            ledControl.turnOn();
        } else {
            ledControl.turnOff();
        }
    }

    // Method to adjust the light threshold
    void adjustThreshold(int newThreshold) {
        photoControl.setThreshold(newThreshold);
    }
};
