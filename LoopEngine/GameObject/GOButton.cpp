#include "LoopEngine/Logger.h"
#include "LoopEngine/GameObject/GoButton.h"

LE::GOButton::GOButton(int InPositionX, int InPositionY, int InLargeur, int InHauteur, const std::string& InText, std::function<void()> InActionToDo, const std::string& InName)
	:GOComposite(InName)
	,_Text(InText)
	,_ActionToDo(InActionToDo)
{
	SetPosition({ (float)InPositionX, (float)InPositionY });
	SetCollisionBox({ (float)InLargeur, (float)InHauteur });
	if (_CollisionBox.width <= 0.f || _CollisionBox.height <= 0.f)
	{
		LOG("Le bouton nomme " + _Name + " a une grosseur invalide. Valeur modifie pour (200,50)", TLevel::eWARNING);
		_CollisionBox.width = 200.f;
		_CollisionBox.height = 50.f;
	}
}

LE::GOButton::~GOButton()
{}

void LE::GOButton::SetColors(const Color& InColorNeutral, const Color& InColorHover, const Color& InColorPressed)
{
	_ColorNeutral = InColorNeutral;
	_ColorHover = InColorHover;
	_ColorPressed = InColorPressed;
}

void LE::GOButton::Draw2D()
{
	const bool isMouseInside = CheckCollisionPointRec(GetMousePosition(), GetCollisionAtWorldPosition());
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
	
	DrawRectangleRec(GetCollisionAtWorldPosition(), activeColor);
	DrawText(_Text.c_str(), (int)GetWorldPosition().x, (int)GetWorldPosition().y, 24, BLACK);
}
