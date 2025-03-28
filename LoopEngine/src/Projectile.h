#pragma once

#include <string>
#include <functional>
#include "raylib.h"
#include "BaseObject.h"
#include "GameObject.h"
#include "CollisionAnalysis.h"

using namespace std;
namespace LE
{
    class Projectile : public GameObjectSingleImage
    {
    protected:
        float _Velocity = 0.f;
        Vector2 _Direction{ 1.f,0.f };
        CollisionAnalysis _CollisionAnalysis;
        int _bounceCount = 0;

    public:
        Projectile(const string& InFilePath, const Vector2& InPosition = { 0.f,0.f }, float InVelocity = 50.f, const Vector2& InDirection = { 1.f,0.f }, const string& InObjectName = "Projectile");
        virtual ~Projectile();

        void SetVelocity(float InVelocity);
        float GetVelocity() const;

        void SetDirection(Vector2 InDirection);
        Vector2 GetDirection() const;

        virtual void PreUpdate() override;
        virtual void DrawDebug() override;

    protected:
        void Bounce(const CollisionAnalysis& analysis);
    };
}
