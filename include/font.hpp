#ifndef FONT_H
#define FONT_H

#include <ArxContainer.h>

// 全局变量
extern const String errString;
extern const std::map<char, String> FontDic;

String getOneCharCode(char word);

#endif