#pragma once

#include <string>
#include <functional>
#include "raylib.h"
#include "BaseObject.h"
#include "GameObject.h"
#include "CharacterController.h"
#include "Projectile.h"

//Classe semblable à l'exercice
using namespace std;
namespace LE
{
	class Button : public GameObject2D
	{
	protected:
		Rectangle _Rectancle;
		std::string _Text = "";
		std::function<void()> _ActionToDo = nullptr;

		Color _ColorNeutral = LIGHTGRAY;
		Color _ColorHover = YELLOW;
		Color _ColorPressed = GREEN;

	public:

		//Log WARNING: Bouton nommé X a une largeur ou une hauteur négative (changé pour (200,50)).
		Button(int InPositionX, int InPositionY, int InLargeur, int InHauteur, const std::string& InText, std::function<void()> InActionToDo, const std::string& InName = "Button");
		virtual ~Button();

		void SetColors(const Color& InColorNeutral, const Color& InColorHover, const Color& InColorPressed);

		//Log INFO: Bouton nommé X appuyé.
		//Log INFO: Bouton nommé X a execute son action.
		//Log INFO: Bouton nommé X n'a pas execute son action car elle est vide.
		virtual void Draw2D() override;
	};
}
