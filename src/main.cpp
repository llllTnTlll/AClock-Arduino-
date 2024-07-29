#include <Arduino.h>
#include <screen.hpp>
#include <timer.hpp>
#include <key.hpp>

Screen *myScreen;
StopWatch *myWatch;

void UpdateTime()
{
  //TODO:这里的处理内容要根据当前模式不同改变
  myWatch->AddTime(0,0,0,10);
}

void setup()
{
  // Serial.begin(250000);

  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, LSBFIRST, SPI_MODE3));

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  // 启用按键中断
  attachInterrupt(0, KeyBoard::BtnAPressed, FALLING);  

  myScreen = new SamsungScreen(6, 16);
  myWatch = new StopWatch(myScreen); 
  Timer1.initialize(10000);
  Timer1.attachInterrupt(UpdateTime);
}

void loop()
{
  
  myWatch->ShowTime();
}
