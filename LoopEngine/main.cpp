#include <iostream>
#include <memory>
//Les "" sont toujours relatifs au dossier racine du projet, contrairement aux dossiers <>
#include "raylib.h"
#include "src/Engine.h"
#include "src/Scene.h"
#include "src/ServiceLocator.h"
#include "src/Logger.h"
#include "src/Button.h"
#include "src/Scene.h"

using namespace LE;

void TestLogger()
{
    std::shared_ptr<LE::Logger> logger = std::make_shared<LE::Logger>();
    service_locator.registerService(logger);
    logger->SetLoggingLevel(TLevel::eINFO);
    logger->Log("Warning coucou, du pointeur de logger!", TLevel::eWARNING);
    logger->Log("Info coucou, du pointeur de logger!", TLevel::eINFO);

    service_locator.getService<ILoggerService>()->Log("Warning avec acces à partir du service locator", TLevel::eWARNING);
    service_locator.getService<ILoggerService>()->SetAbortLevel(eNONE);
    service_locator.getService<ILoggerService>()->Log("Error avec acces à partir du service locator", TLevel::eERROR);

    service_locator.getService<ILoggerService>()->Log(std::string(__FILENAME__) + ":" + to_string(__LINE__) + " Test pour fichier et ligne", TLevel::eWARNING);
    LOG("La macro fonctionne!", TLevel::eINFO);
}

void TestButton()
{
    std::shared_ptr<LE::Logger> logger = std::make_shared<LE::Logger>();
    logger->SetLoggingLevel(TLevel::eINFO);
    service_locator.registerService(logger);

    Button btnA(0, 0, 200, 50, "Hello world!", nullptr, "HelloBtnA");
    Button btnB(0, 300, 200, 50, "", []() {cout << "lawl" << endl; }, "HelloBtnB");
    Button btnC(0, 600, -100, 50, "Bye btn", nullptr, "");

    InitWindow(800, 900, "test btn");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(PINK);
        btnA.Draw2D();
        btnB.Draw2D();
        btnC.Draw2D();
        EndDrawing();
    }
}

void TestImage()
{
    std::shared_ptr<LE::Logger> logger = std::make_shared<LE::Logger>();
    logger->SetLoggingLevel(TLevel::eINFO);
    service_locator.registerService(logger);

    InitWindow(800, 900, "test img");
    SetTargetFPS(60);

    GameObjectSingleImage imgA(string(GetWorkingDirectory()) + "\\res\\Test-Image.png", "imgA");
    imgA.Load();
    imgA.SetScale(2.0f);
    imgA.SetRotation(45.0f);

    GameObjectSingleImage imgB(string(GetWorkingDirectory()) + "\\res\\Test-Image.png", "imgB");
    imgB.Load();
    imgB.SetScale(-2.0f);
    imgB.SetRotation(-40.0f);
    imgB.SetPosition(Vector2{ 350.f,300.f });

    GameObjectSingleImage imgC(string(GetWorkingDirectory()) + "\\res\\Test-Image.png", "imgC");
    imgC.SetPosition(Vector2{ 400.f,400.f });

    GameObjectSingleImage imgD(string(GetWorkingDirectory()) + "\\res\\Test-Image.png", "imgD");
    imgD.SetPosition(Vector2{ 600.f,700.f });
    imgD.Load();
    imgD.Unload();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLUE);
        imgA.Draw2D();
        imgB.Draw2D();
        imgC.Draw2D();
        imgD.Draw2D();
        EndDrawing();
    }
}

void TestScene()
{
    std::shared_ptr<LE::Logger> logger = std::make_shared<LE::Logger>();
    logger->SetLoggingLevel(TLevel::eWARNING);
    service_locator.registerService(logger);

    InitWindow(800, 900, "test img");
    SetTargetFPS(60);

    Scene scene("Test");
    auto btn = make_shared<Button>(0, 0, 300, 50, "Scene", []() {cout << "Coucou de la scene" << endl; });
    scene.AddGameObject2D(btn);

    auto img = make_shared<GameObjectSingleImage>(string(GetWorkingDirectory()) + "\\res\\Test-Image.png");
    img->SetPosition(Vector2{ 400.f,400.f });
    scene.AddGameObject2D(img);

    scene.Load();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RED);
        scene.PreUpdate();
        scene.Draw3D();
        scene.Draw2D();
        scene.LateUpdate();
        EndDrawing();
    }
}

void TestEngineEx()
{
    std::shared_ptr<LE::Logger> logger = std::make_shared<LE::Logger>();
    service_locator.registerService(logger);
    std::shared_ptr<LE::Engine> engine = std::make_shared<LE::Engine>(1000, 1000, "Test ultime", 60);
    service_locator.registerService(engine);

    logger->SetLoggingLevel(TLevel::eINFO);
    logger->ActivateScreenTrace(true);

    auto sceneMenu = std::make_shared<LE::Scene>("Menu");
    auto goToGameFunc = []() {SendCommand([](Engine& InEngine) {InEngine.SwitchScene("Game"); }); };
    auto closeFunc = []() {SendCommand([](Engine& InEngine) {InEngine.RequestClose(); }); };
    auto btnGoToGame = std::make_shared<LE::Button>(400, 400, 200, 50, "Start", goToGameFunc);
    auto btnQuit = std::make_shared<LE::Button>(700, 400, 200, 50, "Quit", closeFunc);
    sceneMenu->AddGameObject2D(btnGoToGame);
    sceneMenu->AddGameObject2D(btnQuit);

    auto sceneGame = std::make_shared<LE::Scene>("Game");
    auto quitFunc = []() {SendCommand([](Engine& InEngine) {InEngine.SwitchScene("Menu"); }); };
    auto img = std::make_shared<LE::GameObjectSingleImage>(string(GetWorkingDirectory()) + "\\res\\Test-Image.png");
    auto btnBackToMenu = std::make_shared<LE::Button>(500, 500, 200, 50, "Back to menu", quitFunc);
    sceneGame->AddGameObject2D(img);
    sceneGame->AddGameObject2D(btnBackToMenu);

    engine->RegisterScene(sceneMenu);
    engine->RegisterScene(sceneGame);
    engine->SetClearColor(PINK);
    engine->SetDebugMode(true);
    engine->StartGame("Menu");
}

void TestLoopEngine()
{
    std::shared_ptr<LE::Logger> logger = std::make_shared<LE::Logger>();
    service_locator.registerService(logger);
    std::shared_ptr<LE::Engine> engine = std::make_shared<LE::Engine>();
    service_locator.registerService(engine);

    if (engine != nullptr)
    {
        engine->SetClearColor(PINK);
        //Scène vide
        engine->RegisterScene(std::make_unique<LE::Scene>("Menu"));
        engine->StartGame("Menu");
    }
}

void TestCollision()
{
    std::shared_ptr<LE::Logger> logger = std::make_shared<LE::Logger>();
    service_locator.registerService(logger);
    std::shared_ptr<LE::Engine> engine = std::make_shared<LE::Engine>(1000, 1000, "Test collision", 60);
    service_locator.registerService(engine);

    auto sceneGame = std::make_shared<LE::Scene>("Game");
    auto quitFunc = []() {SendCommand([](Engine& InEngine) {InEngine.SwitchScene("Menu"); }); };
    auto img = std::make_shared<LE::GameObjectSingleImage>("invalid image name", "Yellow Square");
    img->SetPosition(Vector2{ 100.f,100.f });
    img->SetColorTint(YELLOW);
    img->SetCollisionMask(3);
    auto funcCollision = [](const CollisionEvent& InCollisionEvent) {
        if (InCollisionEvent._OtherObject != nullptr)
        {
            cout << "Collisionne avec " << InCollisionEvent._OtherObject->GetName() << endl;
        }
        };
    img->OnCollisionEvent(funcCollision);
    sceneGame->AddGameObject2D(img);

    auto imgB = std::make_shared<LE::GameObjectSingleImage>("invalid image name", "Red Square");
    imgB->SetPosition(Vector2{ 150.f,150.f });
    imgB->SetColorTint(RED);
    imgB->SetCollisionMask(2);
    auto funcCollisionOther = [](const CollisionEvent& InCollisionEvent) {
        if (InCollisionEvent._OtherObject != nullptr)
        {
            cout << "Moi aussi je collisionne avec " << InCollisionEvent._OtherObject->GetName() << endl;
        }
        };
    imgB->OnCollisionEvent(funcCollisionOther);
    sceneGame->AddGameObject2D(imgB);

    engine->RegisterScene(sceneGame);
    engine->SetClearColor(BLANK);
    engine->SetDebugMode(true);
    engine->StartGame("Game");
}

int main(void)
{

    //TestLogger();
    //TestButton();
    //TestImage();
    //TestScene();
    TestEngineEx();
    //TestLoopEngine();
    //TestCollision();
    return 0;
}