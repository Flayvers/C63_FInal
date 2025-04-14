#include "LoopEngine/Global.h"
#include "raylib.h"


std::shared_ptr<LE::Engine> InitLoopEngine(int InResolutionX, int InResolutionY, const string& InTitle, int InTargetFPS)
{
    std::shared_ptr<LE::Logger> logger = std::make_shared<LE::Logger>();
    service_locator.registerService(logger);
    std::shared_ptr<LE::RessourceManager> ressourceManager = std::make_shared<LE::RessourceManager>();
    service_locator.registerService(ressourceManager);
    std::shared_ptr<LE::Engine> engine = std::make_shared<LE::Engine>(InResolutionX, InResolutionY, InTitle, InTargetFPS);
    service_locator.registerService(engine);
    return engine;
}

LE::IEngineService& GetIEngine()
{
    return GetService<LE::IEngineService>();
}

LE::ILoggerService& GetILogger()
{
    return GetService<LE::ILoggerService>();
}

LE::IRessourceManager& GetIRessourceManager()
{
    return GetService<LE::IRessourceManager>();
}

Texture& LE::LoadTexture(std::string InPathTexture)
{
    return GetIRessourceManager().Load(InPathTexture);
}

void SendLateCommand(const std::function<void(LE::Engine&)>& InNewCommand)
{
    GetIEngine().SendLateUpdateCommand(InNewCommand);
}

float RadianToDegree(float InAngleRadian)
{
    return RAD2DEG * InAngleRadian;
}

float DegreeToRadian(float InAngleDegree)
{
    return DEG2RAD * InAngleDegree;
}

float GetRandomFloat(float InMin, float InMax)
{
    return (InMax - InMin) * ((float)GetRandomValue(0, RAND_MAX) / RAND_MAX) + InMin;
}

float GetRandomFloat(Vector2 InMinMax)
{
    return GetRandomFloat(InMinMax.x, InMinMax.y);
}

Vector2 GetRandomVector(const Rectangle& InRectangle)
{
    return { InRectangle.x + GetRandomFloat(0.f,InRectangle.width),InRectangle.y + GetRandomFloat(0.f,InRectangle.height) };
}
