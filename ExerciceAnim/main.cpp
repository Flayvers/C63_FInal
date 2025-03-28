#include <iostream>
#include <memory>
#include "raylib.h"
#include "src/Global.h"
#include "src/Engine.h"
#include "src/Scene.h"
#include "src/Button.h"
#include "src/TimerCallback.h"
#include "src/GameObjectAnimated.h"
#include "src/GameObjectText.h"
#include "src/GameObjectTextCounter.h"

using namespace std;

int main()
{
    shared_ptr<LE::Engine> engine = InitLoopEngine(1000, 1000, "Exercice animation");
    shared_ptr<LE::Scene> scene = make_shared<LE::Scene>("Test");

    shared_ptr<LE::GameObjectText> txtCounterLabel = make_shared<LE::GameObjectText>(400, 30, "SANS TEXT ");
    ///////////////////////////
    //1) Sur la ligne suivante, changez le contenu du texte de txtCounterLabel pour "Counter: "
    txtCounterLabel->SetText("Counter : ");
        ///////////////////////////

        //2) Rendez-vous dans le constructeur de GameObjectTextCounter - Utilisez un raccourcis obligatoire!
        shared_ptr<LE::GameObjectTextCounter> txtCounterValue = make_shared<LE::GameObjectTextCounter>(600, 30);
    ///////////////////////////

    shared_ptr<LE::Button> btnStart = make_shared<LE::Button>(250, 100, 100, 50, "Start",
        [&txtCounterValue]() {
            ///////////////////////////
            //6) Faites ce que bouton démarre (active) le compteur.
            if (txtCounterValue)
            {
                txtCounterValue->SetActive(true);
            }
            ///////////////////////////
        }
    );

    shared_ptr<LE::Button> btnStop = make_shared<LE::Button>(450, 100, 100, 50, "Pause",
        [&txtCounterValue]() {
            ///////////////////////////
            //7) Faites ce que bouton arrête (désactive) le compteur.
            if (txtCounterValue)
            {
                txtCounterValue->SetActive(false);
            }
            ///////////////////////////
        }
    );


    shared_ptr<LE::Button> btnDuration = make_shared<LE::Button>(650, 100, 100, 50, "Duration",
        [&txtCounterValue]() {
            ///////////////////////////
            //8) Faites ce que bouton donne une durée aléatoire au compteur entre 0.05f et 1.f secondes
            if (txtCounterValue)
            {
                txtCounterValue->SetDuration( (static_cast<float>(GetRandomValue(5, 100) ) / 100.f));
            }
            ///////////////////////////
        }
    );

    const string numberGridImgPath = GetWorkingDirectory() + string("\\res\\AnimGrille4x4.png");
    ///////////////////////////
    //9) La classe GameObjectAnimated dérive de GameObjectSingleImage. Étudiez 1 minute GameObjectAnimated.h puis rendez-vous dans GameObjectAnimated::Draw2D()
    shared_ptr<LE::GameObjectAnimated> animNumbers = make_shared<LE::GameObjectAnimated>(numberGridImgPath, Vector2{ 300.f,500.f }, 4, 4);
    animNumbers->SetFrame(4); //L'index est 2, donc image affichée est 3
    ///////////////////////////

    const string explosionImgPath = GetWorkingDirectory() + string("\\res\\AnimExplosion.png");
    ///////////////////////////
    //13) Corrigez la ligne suivante pour que l'animation joue correctement.
    shared_ptr<LE::GameObjectAnimated> animExplosion = make_shared<LE::GameObjectAnimated>(explosionImgPath, Vector2{ 700.f,500.f }, 4, 4);
    animExplosion->SetLooping(false);
    ///////////////////////////

    //Raccourcis est ok car 0 est l'equivalent de false
    if (engine && scene)
    {
        scene->AddGameObject2D(btnStart);
        scene->AddGameObject2D(btnStop);
        scene->AddGameObject2D(btnDuration);
        scene->AddGameObject2D(txtCounterLabel);
        scene->AddGameObject2D(txtCounterValue);
        scene->AddGameObject2D(animNumbers);
        scene->AddGameObject2D(animExplosion);
        engine->SetClearColor(GRAY);
        //Scène vide
        engine->RegisterScene(scene);
        engine->StartGame("Test");
    }
}