#include "Button.h"
#include "Logger.h"

LE::Button::Button(int InPositionX, int InPositionY, int InLargeur, int InHauteur, const std::string& InText, std::function<void()> InActionToDo, const std::string& InName)
	:_Rectancle{ (float)InPositionX, (float)InPositionY, (float)InLargeur, (float)InHauteur }
	, _Text(InText)
	, _ActionToDo(InActionToDo)
{
	if (_Rectancle.width <= 0.f || _Rectancle.height <= 0.f)
	{
		LOG("Le bouton nomme " + _Name + " a une grosseur invalide. Valeur modifie pour (200,50)", TLevel::eWARNING);
		_Rectancle.width = 200.f;
		_Rectancle.height = 50.f;
	}
}

LE::Button::~Button()
{
}

void LE::Button::SetColors(const Color& InColorNeutral, const Color& InColorHover, const Color& InColorPressed)
{
	_ColorNeutral = InColorNeutral;
	_ColorHover = InColorHover;
	_ColorPressed = InColorPressed;
}

void LE::Button::Draw2D()
{
	const bool isMouseInside = CheckCollisionPointRec(GetMousePosition(), _Rectancle);
	const bool isMousePressed = IsMouseButtonPressed(0);
	Color activeColor = isMouseInside ? _ColorHover : _ColorNeutral;
	if (isMouseInside && isMousePressed)
	{
		if (_ActionToDo != nullptr)
		{
			_ActionToDo();
		}
	}

	if (isMouseInside && IsMouseButtonDown(0))
	{
		activeColor = _ColorPressed;
	}

	DrawRectangle((int)_Rectancle.x, (int)_Rectancle.y, (int)_Rectancle.width, (int)_Rectancle.height, activeColor);
	DrawText(_Text.c_str(), (int)_Rectancle.x, (int)_Rectancle.y, 24, BLACK);
}
