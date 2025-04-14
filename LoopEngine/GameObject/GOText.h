#pragma once

#include <string>
#include "raylib.h"
#include "LoopEngine/GameObject/GOComposite.h"

using namespace std;
namespace LE
{
	class GOText : public GOComposite
	{
	protected:
		string _Text = "NO TEXT";
		Color _Color = DARKPURPLE;
		unsigned __int32 _Size = 32;

	public:

		GOText(int InPositionX, int InPositionY, const std::string& InText, unsigned __int32 InSize = 32);
		virtual ~GOText();

		void SetColor(const Color& InColor);
		void SetFontSize(unsigned __int32 InSize);
		void SetText(const std::string& InText);

		virtual void Draw2D() override;
	};
}
