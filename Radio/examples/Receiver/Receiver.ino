#include "Radio.h"

Radio myRadio(NRF24_1);

void setup() {
  Serial.begin(9600);
  if (!myRadio.begin<3>(7, 8))
    Serial.println("Config failed");
  else
    Serial.println("Config successful!");
}

void loop() {
  if (myRadio.available()) {
    String msg = myRadio.read();
    Serial.print("Message: ");
    Serial.println(msg);
  }
  delay(1);
}
