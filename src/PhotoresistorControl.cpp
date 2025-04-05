


#include "PhotoresistorControl.h"


 PhotoresistorControl::PhotoresistorControl() 
     : S0(4), S1(5), S2(6), Z_PIN(A0) {Serial.println("PhotoRes objected created.");};


 //   PhotoresistorControl::PhotoresistorControl() {}

void PhotoresistorControl::setPinMode() {
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
}

int PhotoresistorControl::readLightLevel(int m_mux0, int m_mux1, int m_mux2 ) {
  digitalWrite(S0, m_mux0);
  digitalWrite(S1, m_mux1);
  digitalWrite(S2, m_mux2);
  return analogRead(Z_PIN);
}


