#include <Arduino.h>
#include <pt6315.hpp>

class Screen
{
private:
    PT6315* driver;
    uint8_t screenGirdNum;
    uint8_t screenSegNum;

public:
    Screen(uint8_t gridNum, uint8_t segNum);
    void SetOnoffLightness(bool onOff, uint8_t lightness);
    ~Screen();
};

Screen::Screen(uint8_t gridNum, uint8_t segNum)
    : screenGirdNum(gridNum), screenSegNum(segNum)
{
    driver = new PT6315(6, 16);
    driver->PT6315_Test(screenGirdNum, screenSegNum);
}

void Screen::SetOnoffLightness(bool onOff, uint8_t lightness){
    
}

Screen::~Screen(){
    driver->~PT6315();
}
