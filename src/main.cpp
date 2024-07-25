#include <Arduino.h>
#include <pt6315.hpp>

void setup() {
  Serial.begin(115200);

  SPI.begin();
  SPI.beginTransaction(SPISettings(96200, LSBFIRST, SPI_MODE3));

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  PT6315* vfd = new PT6315();
  for(int i=1; i<=12; ++i){
    vfd->PT6315_WriteBuffer(i,8,1);
    vfd->PT6315_WriteBuffer(i,7,1);
    vfd->PT6315_WriteBuffer(i,6,1);
    vfd->PT6315_WriteBuffer(i,5,1);

    vfd->PT6315_WriteBuffer(i,16,1);
    vfd->PT6315_WriteBuffer(i,15,1);
    vfd->PT6315_WriteBuffer(i,14,1);
    vfd->PT6315_WriteBuffer(i,13,1);
  }
  vfd->PT6315_ShowFrame();
}

void loop() {

}
