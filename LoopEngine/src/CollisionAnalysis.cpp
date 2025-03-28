#include "CollisionAnalysis.h"
#include "raymath.h"
#include "logger.h"
namespace LE
{
    CollisionAnalysis::CollisionAnalysis(std::function<void(const CollisionAnalysis&)> InCallbackAnalyzedCollision)
        : _CallbackAnalyzedCollision(InCallbackAnalyzedCollision) {
    }

    CollisionAnalysis::~CollisionAnalysis() {}

    void CollisionAnalysis::Draw2D()
    {
        // Dessinez le rectangle de chevauchement
        DrawRectangleRec(_OverlapRectangle, RED);

        // Dessinez la position de la collision
        DrawCircleV(_Position, 5, GREEN);

        // Dessinez la normale
        Vector2 normalEnd = { _Position.x + (_IsNormalVertical ? 0 : 50), _Position.y + (_IsNormalVertical ? 50 : 0) };
        DrawLineV(_Position, normalEnd, BLUE);
    }

    void CollisionAnalysis::Analyze(const CollisionEvent& InCollisionEvent)
    {
        _CollisionEvent = InCollisionEvent;

        // Calcul du chevauchement des 2 rectangles
        _OverlapRectangle = GetCollisionRec(InCollisionEvent._MyObject->GetCollisionAtPosition(), InCollisionEvent._OtherObject->GetCollisionAtPosition());

        _Position = {
        _OverlapRectangle.x + _OverlapRectangle.width / 2.0f,
        _OverlapRectangle.y + _OverlapRectangle.height / 2.0f
        };

        // Calcul de la normale
        _IsNormalVertical = (_OverlapRectangle.width < _OverlapRectangle.height);

        // Calcul du vecteur de séparation
        _Separation = { _IsNormalVertical ? _OverlapRectangle.width : 0, _IsNormalVertical ? 0 : _OverlapRectangle.height };

        // Appel du callback
        if (_CallbackAnalyzedCollision)
        {
            _CallbackAnalyzedCollision(*this);
        }
    }

    void CollisionAnalysis::OnCollisionAnalysisEvent(std::function<void(const CollisionAnalysis&)> InCallbackAnalyzedCollision)
    {
        _CallbackAnalyzedCollision = InCallbackAnalyzedCollision;
    }

    bool CollisionAnalysis::IsNormalVertical() const
    {
        return _IsNormalVertical;
    }

    const Vector2& CollisionAnalysis::GetPosition() const
    {
        return _Position;
    }

    const Rectangle& CollisionAnalysis::GetOverlapRectangle() const
    {
        return _OverlapRectangle;
    }

    Vector2 CollisionAnalysis::MakeBounce(const Vector2& InVelocity) const
    {
        return { _IsNormalVertical ? InVelocity.x : -InVelocity.x, _IsNormalVertical ? -InVelocity.y : InVelocity.y };
    }

    const Vector2& CollisionAnalysis::SeparateMyObject(const Vector2& InPosition) const
    {
        Vector2 newPosition;
        // Calculate the direction from the object's position to the collision point
        Vector2 direction = Vector2Subtract(InPosition, _Position);

        // Determine if the collision is from the left/top or right/bottom

        // Apply the separation vector based on the direction

        if ((direction.x > 0) || (direction.y > 0))
            newPosition = Vector2Add(InPosition, _Separation);
        else
            newPosition = Vector2Subtract(InPosition, _Separation);

        LOG("Direction x : " + std::to_string(direction.x) + " Direction Y : " + std::to_string(direction.y), eDEBUG)

        return newPosition;
    }


}
