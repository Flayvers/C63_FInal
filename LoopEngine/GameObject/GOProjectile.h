#pragma once

#include <string>
#include <functional>

#include "raylib.h"

#include "LoopEngine/CollisionAnalysis.h"
#include "LoopEngine/GameObject/GOSimpleTexture.h"

using namespace std;
namespace LE
{
	class GOProjectile : public GOSimpleTexture
	{
		protected:
			float _Velocity = 0.f;
			Vector2 _Direction{ 0.5f,.4f };
			CollisionAnalysis _CollisionAnalysis;

			void Bounce(const CollisionAnalysis& InCollisionAnalyze);

		public:
			GOProjectile(const string& InFilePath, const Vector2& InPosition = { 0.f,0.f }, float InVelocity = 50.f, const Vector2& InDirection = {1.f,0.f}, const string& InObjectName = "GOProjectile");
			virtual ~GOProjectile();

			void SetVelocity(float Invelocity);
			float GetVelocity() const;

			void SetDirection(Vector2 InDirection);
			Vector2 GetDirection() const;

			virtual void PreUpdate() override;
			virtual void DrawDebug() override;

	};
}
