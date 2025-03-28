#include "CharacterController.h"
#include "raymath.h"

void LE::CharacterController::Bounce(const const CollisionAnalysis& InCollisionAnalyze)
{
	SetPosition(InCollisionAnalyze.SeparateMyObject(GetPosition()));
}

LE::CharacterController::CharacterController(const string& InFilePath, const Vector2& InPosition, float InVelocity, std::array<int, 4> InControlUpLeftDownRight, const string& InObjectName)
	:GameObjectSingleImage(InFilePath, InObjectName)
	, _Velocity(InVelocity)

{
	SetPosition(InPosition);
	std::function<void(const CollisionEvent&)> methodToCallOnCollision = [this](const CollisionEvent& InEvent) {_CollisionAnalysis.Analyze(InEvent); };
	OnCollisionEvent(methodToCallOnCollision);

	std::function<void(const CollisionAnalysis&)> methodToCallOnAnalyze = [this](const CollisionAnalysis& InAnalysis) {Bounce(InAnalysis); };
	_CollisionAnalysis.OnCollisionAnalysisEvent(methodToCallOnAnalyze);
}

LE::CharacterController::~CharacterController()
{}

void LE::CharacterController::SetVelocity(float Invelocity)
{
	_Velocity = Invelocity;
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

		//Les images des personnages devront faire face à droite par défaut
		constexpr Vector2 _ImageFacingDirection = { 1.f,0.f };
		//Angle entre la direction du contrôle et la direction de l'image.
		const float angleRadian = Vector2Angle(_ImageFacingDirection, controlDirection);
		//Converti en degré et défini la rotation
		SetRotation(RAD2DEG * angleRadian);
	}
}

void LE::CharacterController::DrawDebug()
{
	_CollisionAnalysis.Draw2D();
	DrawRectangleLinesEx(GetCollisionAtPosition(), 5.f, WHITE);
}
