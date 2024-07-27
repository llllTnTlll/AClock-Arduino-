#include "font.hpp"

const String errString = "0000000"; // 当找不到任何内容就会返回这个值，设置长度的时候最好能进行对齐

const std::map<char, String> FontDic = {
    // 数字值
    {'0', "1110111"},
    {'1', "0100100"},
    {'2', "1101011"},
    {'3', "1101101"},
    {'4', "0111100"},
    {'5', "1011101"},
    {'6', "1011111"},
    {'7', "1100100"},
    {'8', "1111111"},
    {'9', "1111101"},

    // 符号值
    {'-', "0001000"},

    // 空值
    {' ', "0000000"},

    // 字母值
};

String getOneCharCode(char word) {
    auto it = FontDic.find(word);
    if (it != FontDic.end()) {
        return it->second;
    } else {
        return errString;
    }
}