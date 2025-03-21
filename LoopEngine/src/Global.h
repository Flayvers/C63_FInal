#pragma once

#include <iostream>
#include <memory>
#include <cassert>

#include "raylib.h"

#include "Engine.h"
#include "ServiceLocator.h"
#include "Logger.h"


std::shared_ptr<LE::Engine> InitLoopEngine(int InResolutionX = 800, int InResolutionY = 480, const string& InTitle = "Sans titre", int InTargetFPS = 60);

template<typename ServiceType>
ServiceType& GetService()
{
	//TODO: ajouter un test pour être certain que le service est dans la liste.
	std::shared_ptr<ServiceType> serv = service_locator.getService<ServiceType>();
	assert(serv != nullptr);
	return *serv;
}

LE::IEngineService& GetIEngine();
LE::ILoggerService& GetILogger();

void SendLateCommand(const std::function<void(LE::Engine&)>& InNewCommand);