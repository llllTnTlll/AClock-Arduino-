#include <Arduino.h>
#include <screen.hpp>

void setup() {
  Serial.begin(115200);

  SPI.begin();
  SPI.beginTransaction(SPISettings(96200, LSBFIRST, SPI_MODE3));

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  Screen* myScreen = new Screen(6, 16);
}

void loop() {

}
