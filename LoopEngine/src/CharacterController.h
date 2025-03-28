#pragma once

#include <string>
#include <functional>
#include <array>
#include "raylib.h"
#include "BaseObject.h"
#include "GameObject.h"
#include "CollisionAnalysis.h"

using namespace std;
namespace LE
{
    class CharacterController : public GameObjectSingleImage
    {
    protected:
        float _Velocity = 400.f;
        array<int, 4> _ControlUpLeftDownRight = { KEY_W,KEY_A,KEY_S,KEY_D };
        CollisionAnalysis _CollisionAnalysis;

    public:
        CharacterController(const string& InFilePath, const Vector2& InPosition = { 0.f,0.f }, float InVelocity = 500.f, array<int, 4> InControlUpLeftDownRight = { KEY_W,KEY_A,KEY_S,KEY_D }, const string& InObjectName = "CharacterController");
        virtual ~CharacterController();

        void SetVelocity(float Invelocity);
        float GetVelocity() const;

        virtual void PreUpdate() override;
        virtual void DrawDebug() override;

    protected:
        void HandleContinuousContact(const CollisionAnalysis& analysis);
    };
}
