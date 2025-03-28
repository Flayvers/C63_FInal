#include "CharacterController.h"
#include "raymath.h"

LE::CharacterController::CharacterController(const string& InFilePath, const Vector2& InPosition, float InVelocity, array<int, 4> InControlUpLeftDownRight, const string& InObjectName)
    : GameObjectSingleImage(InFilePath, InObjectName)
    , _Velocity(InVelocity)
    , _ControlUpLeftDownRight(InControlUpLeftDownRight)
{
    SetPosition(InPosition);

    // Enregistrement de la méthode Analyze
    std::function<void(const CollisionEvent&)> methodToCall = [this](const CollisionEvent& InEvent) {
        _CollisionAnalysis.Analyze(InEvent);
        };
    OnCollisionEvent(methodToCall);

    // Enregistrement de la méthode HandleContinuousContact
    std::function<void(const CollisionAnalysis&)> methodToCallOnAnalyze = [this](const CollisionAnalysis& InAnalysis) {
        HandleContinuousContact(InAnalysis);
        };
    _CollisionAnalysis.OnCollisionAnalysisEvent(methodToCallOnAnalyze);
}

LE::CharacterController::~CharacterController() {}

void LE::CharacterController::SetVelocity(float InVelocity)
{
    _Velocity = InVelocity;
}

float LE::CharacterController::GetVelocity() const
{
    return _Velocity;
}

void LE::CharacterController::PreUpdate()
{
    Vector2 controlDirection{ 0.f,0.f };
    if (IsKeyDown(_ControlUpLeftDownRight[0]))
    {
        controlDirection.y -= 1.0f;
    }

    if (IsKeyDown(_ControlUpLeftDownRight[1]))
    {
        controlDirection.x -= 1.0f;
    }

    if (IsKeyDown(_ControlUpLeftDownRight[2]))
    {
        controlDirection.y += 1.0f;
    }

    if (IsKeyDown(_ControlUpLeftDownRight[3]))
    {
        controlDirection.x += 1.0f;
    }

    if (Vector2LengthSqr(controlDirection))
    {
        controlDirection = Vector2Normalize(controlDirection);
        const Vector2 oldPosition = GetPosition();
        const Vector2 newPosition = Vector2Add(oldPosition, Vector2Scale(controlDirection, _Velocity * GetFrameTime()));
        SetPosition(newPosition);

        constexpr Vector2 _ImageFacingDirection = { 1.f,0.f };
        const float angleRadian = Vector2Angle(_ImageFacingDirection, controlDirection);
        SetRotation(RAD2DEG * angleRadian);
    }
}

void LE::CharacterController::DrawDebug()
{
    _CollisionAnalysis.Draw2D();
}

void LE::CharacterController::HandleContinuousContact(const CollisionAnalysis& analysis)
{
    // Ajustez la position du CharacterController en fonction de l'analyse de la collision
    SetPosition(analysis.SeparateMyObject(GetPosition()));

    // Vous pouvez également ajuster d'autres propriétés comme la vitesse ou la direction
    // en fonction de la logique de votre jeu.
}
