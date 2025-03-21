#include "raylib.h"
#include "raymath.h"
#include "Projectile.h"

LE::Projectile::Projectile(const string& InFilePath, const Vector2& InPosition, float InVelocity, const Vector2& InDirection, const string& InObjectName)
	:GameObjectSingleImage(InFilePath,InObjectName)
	,_Velocity(InVelocity)
{
	SetPosition(InPosition);
	SetDirection(InDirection);
}

LE::Projectile::~Projectile()
{

}

void LE::Projectile::SetVelocity(float Invelocity)
{
	_Velocity = Invelocity;
}

float LE::Projectile::GetVelocity() const
{
	return _Velocity;
}

void LE::Projectile::SetDirection(Vector2 InDirection)
{
	_Direction = Vector2Normalize(InDirection);
}

Vector2 LE::Projectile::GetDirection() const
{
	return _Direction;
}

void LE::Projectile::PreUpdate()
{
	Vector2 oldPosition = GetPosition();
	Vector2 newPosition = Vector2Add(oldPosition,Vector2Scale(_Direction, _Velocity * GetFrameTime()));
	SetPosition(newPosition);
}
