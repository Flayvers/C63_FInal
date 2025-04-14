#include "raylib.h"
#include "raymath.h"
#include "LoopEngine/Global.h"
#include "LoopEngine/GameObject/GOProjectile.h"

void LE::GOProjectile::Bounce(const CollisionAnalysis& InCollisionAnalyze)
{
	SetPosition(InCollisionAnalyze.SeparateMyObject(GetPosition()));
	SetDirection(InCollisionAnalyze.MakeBounce(GetDirection()));
}

LE::GOProjectile::GOProjectile(const string& InFilePath, const Vector2& InPosition, float InVelocity, const Vector2& InDirection, const string& InObjectName)
	:GOSimpleTexture(InFilePath,InObjectName)
	,_Velocity(InVelocity)
{
	SetPosition(InPosition);
	SetDirection(InDirection);

	std::function<void(const CollisionEvent&)> methodToCallOnCollision = [this](const CollisionEvent& InEvent) {_CollisionAnalysis.Analyze(InEvent); };
	OnCollisionEvent(methodToCallOnCollision);

	std::function<void(const CollisionAnalysis&)> methodToCallOnAnalyze = [this](const CollisionAnalysis& InAnalysis) {Bounce(InAnalysis); };
	_CollisionAnalysis.OnCollisionAnalysisEvent(methodToCallOnAnalyze);
}

LE::GOProjectile::~GOProjectile()
{
}

void LE::GOProjectile::SetVelocity(float Invelocity)
{
	_Velocity = Invelocity;
}

float LE::GOProjectile::GetVelocity() const
{
	return _Velocity;
}

void LE::GOProjectile::SetDirection(Vector2 InDirection)
{
	_Direction = Vector2Normalize(InDirection);
}

Vector2 LE::GOProjectile::GetDirection() const
{
	return _Direction;
}

void LE::GOProjectile::PreUpdate()
{
	Vector2 oldPosition = GetPosition();
	Vector2 newPosition = Vector2Add(oldPosition,Vector2Scale(_Direction, _Velocity * GetFrameTime()));
	SetPosition(newPosition);
}

void LE::GOProjectile::DrawDebug()
{
	GameObject::DrawDebug();
	_CollisionAnalysis.Draw2D();
}
