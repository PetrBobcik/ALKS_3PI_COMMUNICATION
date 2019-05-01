#include <Arduino.h>
#include "ALKS_3pi.h" 
#include "esp32-hal-i2c.h"
void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
}

void loop() {
  setMotorPower(0,0);
  delay(1000);
  setMotorPower(50,50);
  delay(1000);
}
