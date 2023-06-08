#pragma once
#include <string>
#include "src/Utility/Math.h"
#include "Font.h"

class TextManager
{
public:
    void PrintText(std::string textToPrint, const Vec2& pos);
    void SetFont(Font& font);
private:
};
