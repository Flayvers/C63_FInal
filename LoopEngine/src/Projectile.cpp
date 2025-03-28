#include "raylib.h"
#include "raymath.h"
#include "Projectile.h"
#include "Global.h"

void LE::Projectile::Bounce(const const CollisionAnalysis& InCollisionAnalyze)
{
	SetPosition(InCollisionAnalyze.SeparateMyObject(GetPosition()));
	SetDirection(InCollisionAnalyze.MakeBounce(GetDirection()));
}

LE::Projectile::Projectile(const string& InFilePath, const Vector2& InPosition, float InVelocity, const Vector2& InDirection, const string& InObjectName)
	:GameObjectSingleImage(InFilePath, InObjectName)
	, _Velocity(InVelocity)
{
	SetPosition(InPosition);
	SetDirection(InDirection);

	std::function<void(const CollisionEvent&)> methodToCallOnCollision = [this](const CollisionEvent& InEvent) {_CollisionAnalysis.Analyze(InEvent); };
	OnCollisionEvent(methodToCallOnCollision);

	std::function<void(const CollisionAnalysis&)> methodToCallOnAnalyze = [this](const CollisionAnalysis& InAnalysis) {Bounce(InAnalysis); };
	_CollisionAnalysis.OnCollisionAnalysisEvent(methodToCallOnAnalyze);
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
	Vector2 newPosition = Vector2Add(oldPosition, Vector2Scale(_Direction, _Velocity * GetFrameTime()));
	SetPosition(newPosition);
}

void LE::Projectile::DrawDebug()
{
	_CollisionAnalysis.Draw2D();
	DrawRectangleLinesEx(GetCollisionAtPosition(), 5.f, WHITE);
}
