#include "raylib.h"
#include "raymath.h"
#include "Projectile.h"
#include "CollisionAnalysis.h"

LE::Projectile::Projectile(const string& InFilePath, const Vector2& InPosition, float InVelocity, const Vector2& InDirection, const string& InObjectName)
    : GameObjectSingleImage(InFilePath, InObjectName)
    , _Velocity(InVelocity)
    , _bounceCount(0)
{
    SetPosition(InPosition);
    SetDirection(InDirection);

    // Enregistrement de la m�thode Analyze
    std::function<void(const CollisionEvent&)> methodToCall = [this](const CollisionEvent& InEvent) {
        _CollisionAnalysis.Analyze(InEvent);
        };
    OnCollisionEvent(methodToCall);

    // Enregistrement de la m�thode Bounce
    std::function<void(const CollisionAnalysis&)> methodToCallOnAnalyze = [this](const CollisionAnalysis& InAnalysis) {
        Bounce(InAnalysis);
        };
    _CollisionAnalysis.OnCollisionAnalysisEvent(methodToCallOnAnalyze);
}

LE::Projectile::~Projectile() {}

void LE::Projectile::SetVelocity(float InVelocity)
{
    _Velocity = InVelocity;
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
}

void LE::Projectile::Bounce(const CollisionAnalysis& analysis)
{
    if (_bounceCount < 3)
    {
        _Direction = analysis.MakeBounce(_Direction);
        SetPosition(analysis.SeparateMyObject(GetPosition()));
        _bounceCount++;
    }
    else
    {
        // Destruction du projectile apr�s 3 rebonds
        //Destroy();
    }
}
