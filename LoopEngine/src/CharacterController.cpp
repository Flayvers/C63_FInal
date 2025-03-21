#include "CharacterController.h"
#include "raymath.h"

LE::CharacterController::CharacterController(const string& InFilePath, const Vector2& InPosition, float InVelocity, std::array<int, 4> InControlUpLeftDownRight, const string& InObjectName)
	:GameObjectSingleImage(InFilePath, InObjectName)
	,_Velocity(InVelocity)
{
	SetPosition(InPosition);
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
	Vector2 controlDirection{0.f,0.f};
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
	}
}