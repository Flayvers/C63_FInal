#pragma once

#include <string>
#include "raylib.h"
#include "GameObject.h"

using namespace std;
namespace LE
{
	class GameObjectText : public GameObject2D
	{
	protected:
		int _X = 0, _Y = 0;
		string _Text = "NO TEXT";
		Color _Color = DARKPURPLE;
		unsigned __int32 _Size = 32;

	public:

		GameObjectText(int InPositionX, int InPositionY, const std::string& InText, unsigned __int32 InSize = 32);
		virtual ~GameObjectText();

		void SetColor(const Color& InColor);
		void SetFontSize(unsigned __int32 InSize);
		void SetText(const std::string& InText);

		virtual void Draw2D() override;
	};
}
