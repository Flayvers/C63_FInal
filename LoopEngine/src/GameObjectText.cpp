#include "GameObjectText.h"

LE::GameObjectText::GameObjectText(int InX, int InY, const string& InText, unsigned __int32 InSize)
    :_X(InX), _Y(InY), _Text(InText),_Size(InSize)
{
}

LE::GameObjectText::~GameObjectText()
{
}

void LE::GameObjectText::SetText(const string& InText)
{
    _Text = InText;
}
void LE::GameObjectText::SetColor(const Color& InColor)
{
    _Color = InColor;
}
void LE::GameObjectText::SetFontSize(unsigned __int32 InSize)
{
    _Size = InSize;
}

void LE::GameObjectText::Draw2D() {
    DrawText(_Text.c_str(), _X, _Y, _Size, _Color);
};