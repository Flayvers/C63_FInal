#include "GameObject.h"
#include "Global.h"

using namespace LE;


GameObjectTile::GameObjectTile(const std::string& InImageFileName, const Rectangle& InSceneRectangle)
    : GameObjectSingleImage(InImageFileName, "Tile"), _SceneRectangle(InSceneRectangle)
{
    
}

GameObjectTile::~GameObjectTile()
{
    Unload();
}


void GameObjectTile::Draw2D()
{
    if (GetTexture().id > 0)
    {
        Vector2 origin = { GetTexture().width / 2.0f, GetTexture().height / 2.0f };
        Vector2 size = { GetCollisionBox().x * GetScale(), GetCollisionBox().y * GetScale() };
        Rectangle sourceRec = { 0, 0, static_cast<float>(GetTexture().width), static_cast<float>(GetTexture().height) };
        Rectangle destRec = { GetPosition().x, GetPosition().y, size.x, size.y };

        DrawTexturePro(GetTexture(), sourceRec, destRec, origin, GetRotation(), GetColorTint());

        if (GetIEngine().GetDebugMode())
        {
            DrawRectangleLinesEx(GetCollisionAtPosition(), 2, PINK);
        }
    }
    else
    {
        DrawRectangle(GetPosition().x, GetPosition().y, GetCollisionBox().x, GetCollisionBox().y, GetColorTint());
    }
}
