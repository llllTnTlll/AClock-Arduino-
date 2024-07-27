#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <Arduino.h>
#include <pt6315.hpp>
#include <font.h>

struct Coordinate {
    uint8_t gridIndex;
    uint8_t segIndex;
};

class Screen
{
private:
    PT6315 *driver;

    uint8_t screenGirdNum;
    uint8_t screenSegNum;

    std::vector<String> ScreenContent;

    // 迁移至其他屏幕时此处需要重载
    std::map<uint8_t, Coordinate> ScreenDigitBeginIndex{
        {0, Coordinate{3, 9}},
        {1, Coordinate{4, 1}},
        {2, Coordinate{4, 9}},
        {3, Coordinate{5, 1}},
        {4, Coordinate{5, 9}},
        {5, Coordinate{6, 1}},
        {6, Coordinate{6, 9}},
    };

    inline std::vector<bool> ToBoolVec(String str){
        std::vector<bool> bits;
        for (char ch : str){
            if (ch == '0')
            {
                bits.push_back(0);
            }
            if (ch == '1')
            {
                bits.push_back(1);
            }
        }
        return bits;
    };

public:
    Screen(uint8_t gridNum, uint8_t segNum);
    ~Screen();

    void SetOnoffLightness(bool onOff, uint8_t lightness);
    void ClearScreen();
    void TestScreen();
    void Print(String content);
};

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
    // 将在后期支持滚动播放
    for (uint8_t i = 0; i < content.length(); ++i) {
        char word = static_cast<char>(content[i]);

        Coordinate coord = ScreenDigitBeginIndex[digitPos];
        driver->PT6315_WriteBufferBits(coord.gridIndex, coord.segIndex, ToBoolVec(getOneCharCode(word)));

        digitPos += 1;
    }

    driver->PT6315_ShowFrame();
}

Screen::~Screen()
{
    driver->~PT6315();
}

#endif