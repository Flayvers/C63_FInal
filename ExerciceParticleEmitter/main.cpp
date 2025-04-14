#include <iostream>
#include <memory>

#include "raylib.h"

#include "LoopEngine/Global.h"
#include "LoopEngine/GameObject/GOButton.h"
#include "LoopEngine/GameObject/GOText.h"
#include "LoopEngine/GameObject/GOComposite.h"
#include "LoopEngine/GameObject/GOParticleEmitter.h"
#include "LoopEngine/GameObject/GOCharacterController.h"

using namespace std;
shared_ptr<LE::GOComposite> NewEmitterTestEnviro(const string& EnviroName, const string& imageFilePath, const Vector2& InPosition, const LE::GOParticleEmitter::ParticleEmitterParam& InEmitterConfig, const Vector2& InEmitterEmissionArea);


int main()
{
    shared_ptr<LE::Engine> engine = InitLoopEngine(1000, 1000, "Exercice particle emitter");

    shared_ptr<LE::GOComposite> root = make_shared<LE::GOComposite>("Racine");

    const string particleRainFilePath = GetWorkingDirectory() + string("\\res\\rain_drop_0.png");
    root->AddGameObject2D(NewEmitterTestEnviro("Rain fall", particleRainFilePath, { 450.f,200.f }, LE::GOParticleEmitter::ParticleEmitterParamRain(), { 1000.f,1.f }));

    const string particleDirtFilePath = GetWorkingDirectory() + string("\\res\\dirt.png");
    ///////////////////////////
    //1) Prenez le temps d'étudier ce main et familiarisez-vous avec la nouvelle manière de se faire une scène.
    //Ajoutez un nouvel environnement de test au centre pour l'effet d'explosion de terre (dirt)
    root->AddGameObject2D(NewEmitterTestEnviro("Dirt explosion", particleDirtFilePath, { 450.f, 500.f }, LE::GOParticleEmitter::ParticleEmitterParamDirt(), { 100.f, 100.f }));
    //Allez ensuite dans NewEmitterTestEnviro(...)
    ///////////////////////////

    const string particleSmokeFilePath = GetWorkingDirectory() + string("\\res\\smoke1.png");
    root->AddGameObject2D(NewEmitterTestEnviro("Smoke burst", particleSmokeFilePath, { 450.f,800.f }, LE::GOParticleEmitter::ParticleEmitterParamSmoke(), { 100.f,100.f }));

    if (engine && root)
    {
        engine->RegisterScene(root);
        engine->SetClearColor(ORANGE);
        engine->StartGame("Racine");
    }
}

shared_ptr<LE::GOComposite> NewEmitterTestEnviro(const string& EnviroName, const string& imageFilePath,const Vector2& InPosition,const LE::GOParticleEmitter::ParticleEmitterParam& InEmitterConfig,const Vector2& InEmitterEmissionArea)
{
    auto rootEnviroEmitter = make_shared<LE::GOComposite>("Test root - "+ EnviroName);
    rootEnviroEmitter->SetPosition(InPosition);

    auto charController = rootEnviroEmitter->AddNew<LE::GOCharacterController>(imageFilePath);
    auto burstEmitter = charController->AddNew<LE::GOParticleEmitter>(imageFilePath, "Test emitter - " + EnviroName);
    burstEmitter->_EmissionParameter = InEmitterConfig;
    burstEmitter->SetCollisionBox(InEmitterEmissionArea);

    ///////////////////////////
    //2) Une manière de se faire des objets de jeu est de combiner des GameObject dans une fonction.
    //L'autre est de dériver d'un GOComposite et de l'assembler dans son constructeur. Les deux sont viables!
    //Ajoutez à rootEnviroEmitter un texte contenant le nom de l'environnement (le paramètre EnviroName).
    //Le texte devrait se trouver en haut (suggéré 100).
    auto text = rootEnviroEmitter->AddNew<LE::GOText>(GetScreenWidth()/2, 100, EnviroName);
    text->SetColor(WHITE);
    text->SetFontSize(20);
    //Allez ensuite dans LE::GOParticleEmitter::PreUpdate()
    ///////////////////////////

    auto btnPlay = rootEnviroEmitter->AddNew<LE::GOButton>(-150, 50, 100, 30, "Play()",
        [burstEmitter]() {
            burstEmitter->Play();
        }
    );
    btnPlay->SetColors(BLUE, GREEN, RED);

    auto btnStop = rootEnviroEmitter->AddNew<LE::GOButton>(-50, 50, 100, 30, "Stop()",
        [burstEmitter]() {
            burstEmitter->Stop();
        }
    );
    btnStop->SetColors(BLUE, GREEN, RED);

    auto btnEmitOne = rootEnviroEmitter->AddNew<LE::GOButton>(50, 50, 100, 30, "EmitOne()",
        [burstEmitter]() {
            burstEmitter->EmitOne();
        }
    );
    btnEmitOne->SetColors(BLUE, GREEN, RED);

    auto btnKillAll = rootEnviroEmitter->AddNew<LE::GOButton>(150, 50, 100, 30, "KillAll()",
        [burstEmitter]() {
            burstEmitter->KillAll();
        }
    );
    btnKillAll->SetColors(BLUE, GREEN, RED);



    return rootEnviroEmitter;
}