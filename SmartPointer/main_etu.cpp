#include <iostream>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "SimpleSquare.hpp"

//À inclure pour l'utilisation des pointeurs automatiques
#include <memory>

int main(void)
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 800;
    constexpr float buffer = 80.f;
    constexpr float delta = 100.f;

    InitWindow(screenWidth, screenHeight, "Demo pointeurs automatiques");

    Vector2 currentDrawPosition = Vector2{ buffer,buffer };
    Vector2 drawPositionDelta = Vector2{ delta,delta };

    //Objet automatique
    SimpleSquare hautGauche(currentDrawPosition, "Objet automatique", GREEN);

    //Pointeur normal - ne pas oublier de supprimer!
    currentDrawPosition = Vector2Add(currentDrawPosition, drawPositionDelta);
    SimpleSquare* ptrSimpleSquare = new SimpleSquare(currentDrawPosition, "Pointeur classique", RED);

    //Pointeur partagé
    currentDrawPosition = Vector2Add(currentDrawPosition, drawPositionDelta);
    std::shared_ptr<SimpleSquare> ptrSharedSimpleSquare = std::make_shared<SimpleSquare>(currentDrawPosition, "Pointeur partage", YELLOW);
    std::shared_ptr<SimpleSquare> ptrSharedSimpleSquarecopy = ptrSharedSimpleSquare; //use_count ++

    {
        std::shared_ptr<SimpleSquare> ptrSharedSimpleSquarecopycopy = ptrSharedSimpleSquare; //use_count ++
    }//ptrSharedSimpleSquarecopycopy ne peux plus etre utilise apres la portée, donc use_count--

    //Pointeur faible
    currentDrawPosition = Vector2Add(currentDrawPosition, drawPositionDelta);
    std::weak_ptr<SimpleSquare> ptrWeakSimpleSquare = ptrSharedSimpleSquare; //make_weak n'existe pas
    //un weak ptr n'augmente pas use_count

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(VIOLET);
        hautGauche.Draw();
        if (ptrSimpleSquare != nullptr) 
        {
            ptrSimpleSquare->Draw();
        }
        if (ptrSharedSimpleSquare != nullptr) {
            ptrSharedSimpleSquare->Draw(std::to_string(ptrSharedSimpleSquare.use_count()));
        }
        if (auto tempShared = ptrWeakSimpleSquare.lock()) //IMPORTANT : verrouille le ptr pour empecher la suppression par d'autre instance lors de l'utilisation
        {
            tempShared->Draw(std::to_string(ptrSharedSimpleSquare.use_count()));
        }
        EndDrawing();
    }
    

    CloseWindow();
    if (ptrSimpleSquare != nullptr) {
        delete(ptrSimpleSquare);
    }

    return 0;
}//use_count-- use_count-- donc use_count==0 donc delete effectué