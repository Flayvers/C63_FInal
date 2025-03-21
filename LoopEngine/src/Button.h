#pragma once

#include <string>
#include <functional>
#include "raylib.h"
#include "BaseObject.h"
#include "GameObject.h"

//Classe semblable � l'exercice
using namespace std;
namespace LE
{
	class Button : public GameObject2D
	{
	public:

		//Log WARNING: Bouton nomm� X a une largeur ou une hauteur n�gative (chang� pour (200,50)).
		Button(int InPositionX, int InPositionY, int InLargeur, int InHauteur, const std::string& InText, std::function<void()> InActionToDo, const std::string& InName = "Button");
		virtual ~Button();

		void SetColors(const Color& InColorNeutral, const Color& InHoverNeutral, const Color& InPressedNeutral);

		//Log INFO: Bouton nomm� X appuy�.
		//Log INFO: Bouton nomm� X a execute son action.
		//Log INFO: Bouton nomm� X n'a pas execute son action car elle est vide.
		virtual void Draw2D() override;
	private:
		int _PositionX = 0;
		int _PositionY = 0;
		int _Largeur = 0;
		int _Hauteur = 0;
		std::string _Text = "";
		std::function<void()> _ActionToDo;
		std::string _Name = "";
		Color _ColorNeutral;
		Color _HoverNeutral;
		Color _PressedNeutral;
	};
}
