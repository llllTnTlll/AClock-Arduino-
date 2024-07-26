#include <Arduino.h>
#include <pt6315.hpp>

void setup() {
  Serial.begin(115200);

  SPI.begin();
  SPI.beginTransaction(SPISettings(96200, LSBFIRST, SPI_MODE3));

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  PT6315* vfd = new PT6315(SCAN_MODE_6D22S, 7);
  vfd->PT6315_Test(6, 16);
}

void loop() {

}
