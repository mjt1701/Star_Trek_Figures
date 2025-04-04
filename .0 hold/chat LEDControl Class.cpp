#include <iostream>
#include <string>

class LEDControl {
private:
    int ledPin;         // Pin connected to the LED
    std::string color;  // Color of the LED (could be extended to RGB or something else)
    bool isOn;          // State of the LED

public:
    // Constructor to initialize the LED pin and color
    LEDControl(int pin, const std::string& initialColor = "off")
        : ledPin(pin), color(initialColor), isOn(false) {}

    // Method to set the color of the LED
    void setColor(const std::string& newColor) {
        color = newColor;
        std::cout << "LED color set to: " << color << std::endl;
    }

    // Method to turn on the LED
    void LEDTurnOn() {
        isOn = true;
        std::cout << "LED turned on (Color: " << color << ")" << std::endl;
    }

    // Method to turn off the LED
    void LEDTurnOff() {
        isOn = false;
        std::cout << "LED turned off" << std::endl;
    }

    // Method to check if the LED is on
    bool getState() const {
        return isOn;
    }
};
