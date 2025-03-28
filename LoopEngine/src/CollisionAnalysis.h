#pragma once

#include <string>
#include <functional>
#include "raylib.h"
#include "BaseObject.h"
#include "GameObject.h"

using namespace std;
namespace LE
{
	//Classe utilitaire pour analyser la collision
	//Vous l'utilisez dans Projectil et CharacterController
	class CollisionAnalysis : public IBaseObject
	{
	protected:
		bool _IsNormalVertical = true; //Rebondissement horizontal ou vertical
		Vector2 _Position{ 0.f,0.f };
		Vector2 _Separation{ 0.f,0.f };
		Rectangle _OverlapRectangle{ 0.f,0.f,0.f,0.f };
		CollisionEvent _CollisionEvent;
		std::function<void(const CollisionAnalysis&)> _CallbackAnalyzedCollision;

	public:
		//WARNING: PostAnalysisCallback is null
		CollisionAnalysis(std::function<void(const CollisionAnalysis&)> InCallbackAnalyzedCollision = nullptr);
		virtual ~CollisionAnalysis();

		//Dessine les informations de la derni�re collision qui eu lieu.
		//Pour le moment, dessine en ordre le rectangle de chevauchement, la position de la collision et la normale
		void Draw2D();

		//Passer cette m�thode � OnCollisionEvent pour analyser la collision
		//Pour r�agir � la collision analys�e, il faut s'enregister via SetAnalyzedCallback
		//En ordre, effectue les op�rations suivantes
		// 
		//Calcul du chevauchement des 2 rectangles avec 
		//Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);
		//
		// Calcul de la normale (vecteur de direction du rebondissement)
		// 
		// Calcul du vecteur de s�paration par rapport � l'object _MyObject
		// 
		//Appel _CallbackAnalyzedCollision
		void Analyze(const CollisionEvent& InCollisionEvent);

		//WARNING: PostAnalysisCallback is null
		//R�agir via ce callback. C'est ici que vous codez le sp�cifique pour Projectile ou CharacterController
		void OnCollisionAnalysisEvent(std::function<void(const CollisionAnalysis&)> InCallbackAnalyzedCollision);

		bool IsNormalVertical() const;
		//Centre du rectangle de chevauchement
		const Vector2& GetPosition() const;

		const Rectangle& GetOverlapRectangle() const;

		//Retourne la velocit� mais avec l'inverse du X ou du Y selon la normale
		Vector2 MakeBounce(const Vector2& InVelocity) const;

		//D�place la position en entr�e avec le vecteur de s�paration pour s�parer l'objet
		const Vector2& SeparateMyObject(const Vector2& InPosition) const;
	};
}