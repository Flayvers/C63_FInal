#pragma once

#include <string>
#include <functional>
#include <array>
#include "raylib.h"
#include "LoopEngine/BaseObject.h"
#include "LoopEngine/CollisionAnalysis.h"
#include "LoopEngine/GameObject/GOSimpleTexture.h"

using namespace std;
namespace LE
{
	class GOCharacterController : public GOSimpleTexture
	{
	protected:
		float _Velocity = 400.f;
		array<int, 4> _ControlUpLeftDownRight = { KEY_W,KEY_A,KEY_S,KEY_D };
		CollisionAnalysis _CollisionAnalysis;

		void Bounce(const CollisionAnalysis& InCollisionAnalyze);

	public:
		GOCharacterController(const string& InFilePath, const Vector2& InPosition = {0.f,0.f}, float InVelocity = 500.f, array<int, 4> InControlUpLeftDownRight = { KEY_W,KEY_A,KEY_S,KEY_D }, const string& InObjectName = "GOCharacterController");
		virtual ~GOCharacterController();

		void SetVelocity(float Invelocity);
		float GetVelocity() const;

		virtual void PreUpdate() override;
		virtual void DrawDebug() override;


		//Simule un mouvement dans la direction donnee
		//TODO: void SimulateControl(const Vector2& InDirection)
	};
}
