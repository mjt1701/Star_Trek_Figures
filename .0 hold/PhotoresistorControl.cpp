#include "PhotoresistorControl.h"
#include <iostream>
#include <cstdlib>

PhotoresistorControl::PhotoresistorControl(int pin, int threshold)
    : photoresistorPin(pin), lightThreshold(threshold), lightLevel(0) {}

void PhotoresistorControl::readLightLevel() {
    lightLevel = rand() % 1024;  // Simulate an ADC value (0 to 1023)
    std::cout << "Photoresistor reading: " << lightLevel << std::endl;
}

int PhotoresistorControl::getLightLevel() const {
    return lightLevel;
}

bool PhotoresistorControl::isLightBelowThreshold() const {
    return lightLevel < lightThreshold;
}

void PhotoresistorControl::setThreshold(int threshold) {
    lightThreshold = threshold;
    std::cout << "Light threshold set to: " << lightThreshold << std::endl;
}
