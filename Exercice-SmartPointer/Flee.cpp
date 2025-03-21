#include "Flee.h"
#include <raymath.h>

Flee::Flee(const Vector2& InPosition, float InVelocity, const Vector2& InBordersMin, const Vector2& InBordersMax)
	:_Position(InPosition)
	, _Velocity(InVelocity)
	, _BorderMin(InBordersMin)
	, _BorderMax(InBordersMax)
{
	float randomX = static_cast<float>(GetRandomValue(0, 100));
	float randomY = static_cast<float>(GetRandomValue(0, 100));
	_Direction = Vector2{ randomX, randomY };
	_Direction = Vector2Normalize(_Direction);
}

Flee::~Flee()
{
	//Rien
}

void Flee::Move(float InDeltaTime)
{
	const Vector2 oldPosition = _Position;
	_Position += Vector2Scale(_Direction, _Velocity * InDeltaTime);
	if (_Position.x > _BorderMax.x || _Position.x < _BorderMin.x)
	{
		_Position = oldPosition;
		_Direction.x = -_Direction.x;
	}

	if (_Position.y > _BorderMax.y || _Position.y < _BorderMin.y)
	{
		_Position = oldPosition;
		_Direction.y = -_Direction.y;
	}
}

bool Flee::CollideWith(weak_ptr<const Flee> otherFlee) const
{
	if (auto usablePtr = otherFlee.lock())
	{
		return CheckCollisionCircles(GetPosition(), __Radius, usablePtr->GetPosition(), __Radius);
	}
	return false;
}

void Flee::Draw() const
{
	DrawCircle(static_cast<int>(_Position.x), static_cast<int>(_Position.y), static_cast<int>(__Radius), GREEN);
}

const Vector2& Flee::GetPosition() const
{
	return _Position;
}