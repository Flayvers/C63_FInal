#include "LoopEngine/GameObject/GOText.h"

LE::GOText::GOText(int InX, int InY, const string& InText, unsigned __int32 InSize)
    :GOComposite(InText),_Text(InText),_Size(InSize)
{
    SetPosition({ (float)InX,  (float)InY });
}

LE::GOText::~GOText()
{
}

void LE::GOText::SetText(const string& InText)
{
    _Text = InText;
}
void LE::GOText::SetColor(const Color& InColor)
{
    _Color = InColor;
}
void LE::GOText::SetFontSize(unsigned __int32 InSize)
{
    _Size = InSize;
}

void LE::GOText::Draw2D() {
    DrawText(_Text.c_str(), (int)GetWorldPosition().x, (int)GetWorldPosition().y, _Size, _Color);
};