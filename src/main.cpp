#include <Arduino.h>
#include <screen.hpp>
#include <timer.hpp>

Screen* myScreen;
StopWatch* myWatch;

bool isSPIBusy() {
    // 读取 SPSR 寄存器
    uint8_t spsr = SPSR;
    // 检查 SPIF 位
    return !(spsr & (1 << SPIF));
}

void setup() {
  Serial.begin(115200);

  SPI.begin();
  SPI.beginTransaction(SPISettings(96200, LSBFIRST, SPI_MODE3));

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  myScreen = new SamsungScreen(6, 16);
  myWatch = new StopWatch(myScreen, 100);
  myWatch->showTime();
}

void loop() {

}
