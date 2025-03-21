#include "Button.h"
#include "Logger.h"

namespace LE
{
    Button::Button(int InPositionX, int InPositionY, int InLargeur, int InHauteur, const std::string& InText, std::function<void()> InActionToDo, const std::string& InName)
        : GameObject2D(Vector2{ static_cast<float>(InPositionX), static_cast<float>(InPositionY) }, Vector2{ static_cast<float>(InLargeur), static_cast<float>(InHauteur) }, 0, InName),
        _PositionX(InPositionX), _PositionY(InPositionY), _Largeur(InLargeur), _Hauteur(InHauteur),
        _Text(InText), _ActionToDo(InActionToDo), _Name(InName),
        _ColorNeutral(LIGHTGRAY), _HoverNeutral(GRAY), _PressedNeutral(DARKGRAY)
    {
        if (_Largeur < 0 || _Hauteur < 0)
        {
            LOG("Bouton nommé " + _Name + " a une largeur ou une hauteur négative (changé pour (200,50)).", eWARNING);
            _Largeur = 200;
            _Hauteur = 50;
        }
    }

    Button::~Button() {}

    void Button::SetColors(const Color& InColorNeutral, const Color& InHoverNeutral, const Color& InPressedNeutral)
    {
        _ColorNeutral = InColorNeutral;
        _HoverNeutral = InHoverNeutral;
        _PressedNeutral = InPressedNeutral;
    }

    void Button::Draw2D()
    {
        Vector2 mousePosition = GetMousePosition();
        bool isMouseOver = (mousePosition.x >= _PositionX && mousePosition.x <= _PositionX + _Largeur &&
            mousePosition.y >= _PositionY && mousePosition.y <= _PositionY + _Hauteur);

        Color currentColor = _ColorNeutral;
        if (isMouseOver)
        {
            currentColor = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? _PressedNeutral : _HoverNeutral;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                LOG("Bouton nommé " + _Name + " appuyé.", eINFO);
                if (_ActionToDo)
                {
                    _ActionToDo();
                    LOG("Bouton nommé " + _Name + " a exécuté son action.", eINFO);
                }
                else
                {
                    LOG("Bouton nommé " + _Name + " n'a pas exécuté son action car elle est vide.", eINFO);
                }
            }
        }

        DrawRectangle(_PositionX, _PositionY, _Largeur, _Hauteur, currentColor);
        DrawText(_Text.c_str(), _PositionX + 10, _PositionY + 10, 20, BLACK);
    }
}
