#include <screen.hpp>

Screen::Screen(uint8_t gridNum, uint8_t segNum)
    : screenGirdNum(gridNum), screenSegNum(segNum)
{
    driver = new PT6315(screenGirdNum, screenSegNum);
}

void Screen::SetOnoffLightness(bool onOff, uint8_t lightness)
{
    driver->PT6315_SetScreen(onOff, lightness);
}

void Screen::ClearScreen()
{
    driver->PT6315_ClearAll();
}

void Screen::TestScreen(){
    driver->PT6315_Test(screenGirdNum, screenSegNum);
}

void Screen::Print(String content)
{
    uint8_t digitPos = 0;
    content = content.substring(0, 7);
    for (uint8_t i = 0; i < content.length(); ++i) {
        char word = static_cast<char>(content[i]);

        Coordinate coord = ScreenDigitBeginIndex[digitPos];
        driver->PT6315_WriteBufferBits(coord.gridIndex, coord.segIndex, ToBoolVec(getOneCharCode(word)));

        digitPos += 1;
    }

    driver->PT6315_ShowFrame();
}

void Screen::ScrollPirnt(String content, uint16_t interval){
    Print(content);
    delay(interval);
    while (content.length() > 7) {
        content = content.substring(1);
        Print(content);
        delay(interval);
    }
    delay(interval);
}

Screen::~Screen()
{
    driver->~PT6315();
}