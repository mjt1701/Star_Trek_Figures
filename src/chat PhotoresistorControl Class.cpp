#include <iostream>

class PhotoresistorControl {
private:
    int photoresistorPin; // Pin connected to the photoresistor
    int lightThreshold;   // Threshold to decide when to turn the LED on/off
    int lightLevel;       // The current reading from the photoresistor

public:
    // Constructor to initialize the photoresistor pin and threshold
    PhotoresistorControl(int pin, int threshold = 512)
        : photoresistorPin(pin), lightThreshold(threshold), lightLevel(0) {}

    // Method to simulate reading from the photoresistor (in a real system, you'd use an ADC)
    void readLightLevel() {
        // For simulation, let's assume a random light level
        lightLevel = rand() % 1024; // Random value between 0 and 1023
        std::cout << "Photoresistor reading: " << lightLevel << std::endl;
    }

    // Method to get the current light level
    int getLightLevel() const {
        return lightLevel;
    }

    // Method to check if the light level is below the threshold
    bool isLightBelowThreshold() const {
        return lightLevel < lightThreshold;
    }

    // Method to set the threshold dynamically
    void setThreshold(int threshold) {
        lightThreshold = threshold;
        std::cout << "Light threshold set to: " << lightThreshold << std::endl;
    }
};
