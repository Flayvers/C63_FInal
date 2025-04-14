#include "LoopEngine/Global.h"
#include "LoopEngine/GameObject/GOTile.h"

LE::GameObjectTile::GameObjectTile(const std::string& InImageFileName, const Rectangle& InSceneRectangle)
	:GOSimpleTexture(InImageFileName, "GameObjectTile")
{
	_CollisionBox = InSceneRectangle;
}

void LE::GameObjectTile::Draw2D()
{
	Rectangle source = { 0, 0, (float)_CollisionBox.width, (float)_CollisionBox.height };
	Rectangle dest = { GetWorldPosition().x, GetWorldPosition().y, _CollisionBox.width * _Scale, _CollisionBox.height * _Scale };
	Vector2 pivot = { _CollisionBox.width * 0.5f * _Scale, _CollisionBox.height * 0.5f * _Scale };

	if (_IsLoaded)
	{
		DrawTexturePro(_Texture, source, dest, pivot, _Rotation, WHITE);
	}
	else
	{
		DrawRectanglePro(_CollisionBox, pivot, _Rotation, _Tint);
	}

	if (GetIEngine().GetDebugMode())
	{
		DrawRectangleLinesEx(GetCollisionAtWorldPosition(), 5.f, _Tint);
	}
}
