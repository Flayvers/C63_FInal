#include "raylib.h"
#include "raymath.h"
#include "Flee.h"
#include <iostream>
#include <memory>
#include <vector>
#include <set>

using namespace std;

struct CollisionEvent
{
    weak_ptr<Flee> _LowerIndexFlee;
    weak_ptr<Flee> _HigherIndexFlee;
    Vector2 _Position;
    float _TimeOfImpact;

    CollisionEvent(weak_ptr<Flee> InLowerIndexFlee, weak_ptr<Flee> InHigherIndexFlee, float InTimeOfImpact)
        : _LowerIndexFlee(InLowerIndexFlee)
        , _HigherIndexFlee(InHigherIndexFlee)
        , _TimeOfImpact(InTimeOfImpact)
    {
        // Constructeur ici
        if (auto lowerFlee = _LowerIndexFlee.lock())
        {
            _Position = lowerFlee->GetPosition();
        }
    }
};

int main(void)
{
    constexpr int screenWidth = 1000;
    constexpr int screenHeight = 1000;
    constexpr int borderMargin = 50;
    constexpr int nbFlee = 25;

    constexpr Vector2 borderMin = Vector2{ borderMargin ,borderMargin };
    constexpr Vector2 borderMax = Vector2{ screenWidth - borderMargin , screenHeight - borderMargin };
    InitWindow(screenWidth, screenHeight, "Flee bonanza!");

    // 1) Créer une structure de donnée pour contenir des smart pointeur de puce sans la remplir
    vector<shared_ptr<Flee>> flees;

    // 2) Dans une boucle, créez des puces et placez-les au hasard à l'intérieur de border min et border max
    for (int i = 0; i < nbFlee; ++i)
    {
        Vector2 randomPosition = Vector2{
            static_cast<float>(GetRandomValue(borderMin.x, borderMax.x)),
            static_cast<float>(GetRandomValue(borderMin.y, borderMax.y))
        };
        flees.emplace_back(make_shared<Flee>(randomPosition, 500.0f, borderMin, borderMax));
    }

    // 4) Créer une structure de données pour contenir des smart pointer d'évènement de collision.
    vector<shared_ptr<CollisionEvent>> collisionEvents;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();
        const float totalTime = GetTime();
        BeginDrawing();
        ClearBackground(BLUE);
        DrawLine(borderMin.x, borderMin.y, borderMin.x, borderMax.y, PURPLE);
        DrawLine(borderMin.x, borderMin.y, borderMax.x, borderMin.y, PURPLE);
        DrawLine(borderMax.x, borderMin.y, borderMax.x, borderMax.y, PURPLE);
        DrawLine(borderMin.x, borderMax.y, borderMax.x, borderMax.y, PURPLE);

        // 5) Dessiner le nombre d'images par secondes en haut à gauche
        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, WHITE);

        // 6) Écrire le nombre total de puces en noir
        DrawText(TextFormat("Flees: %d", flees.size()), screenWidth / 2 - 50, 10, 20, BLACK);

        // 7) Écrire le nombre total de collisions
        DrawText(TextFormat("Collisions: %d", collisionEvents.size()), screenWidth - 200, 10, 20, WHITE);

        // 8) Pour chaque puce, faites-la avancer et dessinez-la
        for (auto& flee : flees)
        {
            flee->Move(deltaTime);
            flee->Draw();
        }

        // 9) Tester la collision entre toutes les paires de puces possibles
        for (size_t i = 0; i < flees.size(); ++i)
        {
            for (size_t j = i + 1; j < flees.size(); ++j)
            {
                if (flees[i]->CollideWith(flees[j]))
                {
                    collisionEvents.emplace_back(make_shared<CollisionEvent>(flees[i], flees[j], totalTime));
                }
            }
        }

        // 11) Pour chaque évènement de collision
        for (const auto& collisionEvent : collisionEvents)
        {
            if (auto lowerFlee = collisionEvent->_LowerIndexFlee.lock())
            {
                if (auto higherFlee = collisionEvent->_HigherIndexFlee.lock())
                {
                    // 11.1) Dessiner un carré blanc transparent à chaque position de collision
                    DrawRectangleV(collisionEvent->_Position, Vector2{ 5, 5 }, Color{ 255, 255, 255, 25 });

                    // 11.2) Dessiner une ligne noire transparente entre chaque puce qui a subi une collision
                    DrawLineV(lowerFlee->GetPosition(), higherFlee->GetPosition(), Color{ 25, 25, 25, 10 });
                }
            }
        }

        // 12) Supprimer une puce chaque fois qu'on appuie sur espace
        if (IsKeyPressed(KEY_SPACE))
        {
            if (!flees.empty())
            {
                flees.pop_back();
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
