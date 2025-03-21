#include "Global.h"

std::shared_ptr<LE::Engine> InitLoopEngine(int InResolutionX, int InResolutionY, const string& InTitle, int InTargetFPS)
{
    std::shared_ptr<LE::Logger> logger = std::make_shared<LE::Logger>();
    service_locator.registerService(logger);
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

void SendLateCommand(const std::function<void(LE::Engine&)>& InNewCommand)
{
    GetIEngine().SendLateUpdateCommand(InNewCommand);
}