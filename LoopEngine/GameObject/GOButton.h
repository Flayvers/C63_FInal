#pragma once

#include <string>
#include <functional>
#include "raylib.h"
#include "LoopEngine/BaseObject.h"
#include "LoopEngine/GameObject/GOComposite.h"

using namespace std;
namespace LE
{
	class GOButton : public GOComposite
	{
	protected:
		std::string _Text = "";
		std::function<void()> _ActionToDo = nullptr;

		Color _ColorNeutral = LIGHTGRAY;
		Color _ColorHover = YELLOW;
		Color _ColorPressed = GREEN;

	public:

		GOButton(int InPositionX, int InPositionY, int InLargeur, int InHauteur, const std::string& InText, std::function<void()> InActionToDo, const std::string& InName = "GOButton");
		virtual ~GOButton();

		void SetColors(const Color& InColorNeutral, const Color& InColorHover, const Color& InColorPressed);

		virtual void Draw2D() override;
	};
}
