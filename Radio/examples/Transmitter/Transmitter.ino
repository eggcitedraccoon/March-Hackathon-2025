#include "Radio.h"

Radio myRadio(NRF24_2);

void setup() {
  Serial.begin(9600);
  if (!myRadio.begin<3>(7, 8))
    Serial.println("Config failed");
  else
    Serial.println("Config successful!");
}
int count = 0;
void loop() {
  String msg = "Count: ";
  msg += count++;
  myRadio.write(msg);
  Serial.println(msg);
  delay(10);
}
