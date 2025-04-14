#pragma once

#include <string>
#include <functional>
#include "LoopEngine/BaseObject.h"
#include "LoopEngine/GameObject/GO.h"

using namespace std;
namespace LE
{
	class CollisionAnalysis : public IBaseObject
	{
		protected:
			bool _IsNormalVertical = true;
			Vector2 _Position{ 0.f,0.f };
			Vector2 _Separation{ 0.f,0.f };
			Rectangle _OverlapRectangle{ 0.f,0.f,0.f,0.f };
			CollisionEvent _CollisionEvent = CollisionEvent();
			std::function<void(const CollisionAnalysis&)> _CallbackAnalyzedCollision = nullptr;

		public:
			CollisionAnalysis(std::function<void(const CollisionAnalysis&)> InCallbackAnalyzedCollision = nullptr);
			virtual ~CollisionAnalysis();

			void Draw2D();
			void Analyze(const CollisionEvent& InCollisionEvent);

			void OnCollisionAnalysisEvent(std::function<void(const CollisionAnalysis&)> InCallbackAnalyzedCollision);

			bool IsNormalVertical() const;
			Vector2 GetPosition() const;

			Rectangle GetOverlapRectangle() const;

			Vector2 MakeBounce(const Vector2& InVelocity) const;

			Vector2 SeparateMyObject(const Vector2& InPosition) const;
	};
}