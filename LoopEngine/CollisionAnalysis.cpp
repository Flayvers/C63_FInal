#include "LoopEngine/CollisionAnalysis.h"
#include "raymath.h"

LE::CollisionAnalysis::CollisionAnalysis(std::function<void(const CollisionAnalysis&)> InCallbackAnalyzedCollision)
	:_CallbackAnalyzedCollision(InCallbackAnalyzedCollision)
{
}

LE::CollisionAnalysis::~CollisionAnalysis()
{
}

void LE::CollisionAnalysis::Draw2D()
{
	//const Vector2 normal = IsNormalVertical() ? Vector2{ 0.f,80.f } : Vector2{ 80.f,0.f };
	const Vector2 endNormal = Vector2Add(GetPosition(), _Separation);
	DrawRectangleRec(GetOverlapRectangle(), DARKBLUE);
	DrawCircle((int)GetPosition().x, (int)GetPosition().y, 10.f, GREEN);
	DrawLineEx(GetPosition(), endNormal, 10.f,DARKGREEN);
}

void LE::CollisionAnalysis::Analyze(const CollisionEvent& InCollisionEvent)
{
	_OverlapRectangle = GetCollisionRec(InCollisionEvent._MyObject->GetCollisionAtPosition(), InCollisionEvent._OtherObject->GetCollisionAtPosition());
	_IsNormalVertical = _OverlapRectangle.width > _OverlapRectangle.height;

	const Vector2 myPosition = InCollisionEvent._MyObject->GetPosition();

	_Separation = _IsNormalVertical ? Vector2{ 0.f,_OverlapRectangle.height } : Vector2{ _OverlapRectangle.width,0.f };
	if (_IsNormalVertical && myPosition.y > GetPosition().y)
	{
		_Separation.y = -_Separation.y;
	}

	if (!_IsNormalVertical && myPosition.x > GetPosition().x)
	{
		_Separation.x = -_Separation.x;
	}
	_CallbackAnalyzedCollision(*this);
}

void LE::CollisionAnalysis::OnCollisionAnalysisEvent(std::function<void(const CollisionAnalysis&)> InCallbackAnalyzedCollision)
{
	_CallbackAnalyzedCollision = InCallbackAnalyzedCollision;
}

bool LE::CollisionAnalysis::IsNormalVertical() const
{
	return _IsNormalVertical;
}

Vector2 LE::CollisionAnalysis::GetPosition() const
{
	return {_OverlapRectangle.x + _OverlapRectangle.width*0.5f, _OverlapRectangle.y + _OverlapRectangle.height * 0.5f };
}

Rectangle LE::CollisionAnalysis::GetOverlapRectangle() const
{
	return _OverlapRectangle;
}

Vector2 LE::CollisionAnalysis::MakeBounce(const Vector2& InVelocity) const
{
	if (IsNormalVertical())
	{
		return Vector2{ InVelocity.x, -InVelocity.y };
	}
	else
	{
		return Vector2{ -InVelocity.x, InVelocity.y };
	}
}

Vector2 LE::CollisionAnalysis::SeparateMyObject(const Vector2& InPosition) const
{

	return Vector2Subtract(InPosition, _Separation);
}
