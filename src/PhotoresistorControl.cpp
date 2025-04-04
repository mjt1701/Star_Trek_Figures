#include "PhotoresistorControl.h"


PhotoresistorControl::PhotoresistorControl( 
     int S0 = 4,
     int S1 = 5,
     int S2 = 6, 
     int Z_PIN = 9 ) {}

void PhotoresistorControl::readLightLevel() {
    lightLevel = rand() % 1024;  // Simulate an ADC value (0 to 1023)
    std::cout << "Photoresistor reading: " << lightLevel << std::endl;
}

void PhotoresistorControl::setPinMode() {
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);

}
