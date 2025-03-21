#pragma once
//hpp pour les classes très simples, sinon le temps de compilation peu êtr très élevé.

#include "raylib.h"
#include <string>

class SimpleSquare
{
public:
	//////////////////
	//Attributs
	//////////////////
	Vector2 _Position = Vector2{ 0.f,0.f };
	float _Size = 10.0f;
	Color _Color = YELLOW;
	std::string _Message = "";

	//////////////////
	//Attributs de classe
	//////////////////
	static constexpr int __TextOffsetY = 20;
	static constexpr int __TextFontSize = 32;

	//////////////////
	//Méthodes
	//////////////////
	SimpleSquare(const Vector2& InPosition, const std::string& InMessage, Color InColor = YELLOW, float InSize = 10.0f)
		:_Position(InPosition)
		, _Size(InSize)
		, _Color(InColor)
		, _Message(InMessage)
	{}

	~SimpleSquare()
	{}

	void Draw(const std::string& InMessageExtended = "")
	{
		const int x = (int)_Position.x;
		const int y = (int)_Position.y;
		const std::string totalMsg = _Message + " " + InMessageExtended;
		DrawText(totalMsg.c_str(), x, y + __TextOffsetY, __TextFontSize, _Color);
		DrawRectangle(x, y, _Size, _Size, _Color);
	}
};
