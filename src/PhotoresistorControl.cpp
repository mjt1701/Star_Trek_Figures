//  PhotoresistorControl.cpp

#include "PhotoresistorControl.h"

PhotoresistorControl::PhotoresistorControl()
    : S0(4), S1(5), S2(6), Z_PIN(A0) { Serial.println("PhotoRes objected created."); };

int PhotoresistorControl::readLightLevel(Figures &m_figObj)
{
// todo  change to bit banging / dont need to now but still can do it for fun

    digitalWrite(S0, m_figObj.getFigMux0());
    digitalWrite(S1, m_figObj.getFigMux1());
    digitalWrite(S2, m_figObj.getFigMux2());
    return analogRead(Z_PIN);
}
void PhotoresistorControl::setPinMode()
{
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
}
