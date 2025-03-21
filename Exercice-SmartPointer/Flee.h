#pragma once

#include "raylib.h"
#include <memory>
using namespace std;

class Flee
{
private:
    static constexpr float __Radius = 10.0f;

    Vector2 _Position;
    Vector2 _Direction;
    float _Velocity;
    const Vector2 _BorderMin;
    const Vector2 _BorderMax;

    //TODO: ami

public:
    Flee(const Vector2& InPosition, float InVelocity, const Vector2& InBordersMin, const Vector2& InBordersMax);
    ~Flee();

    void Move(float InDeltaTime);
    void Draw() const;
    const Vector2& GetPosition() const;
    //TODO pendant la démo:
    bool CollideWith(weak_ptr<const Flee> otherFlee) const;

};
