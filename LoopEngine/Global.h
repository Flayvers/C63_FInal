#pragma once

#include <iostream>
#include <memory>
#include <cassert>

#include "raylib.h"

#include "LoopEngine/Engine.h"
#include "LoopEngine/ServiceLocator.h"
#include "LoopEngine/Logger.h"
#include "LoopEngine/RessourceManager.h"

std::shared_ptr<LE::Engine> InitLoopEngine(int InResolutionX = 800, int InResolutionY = 480, const string& InTitle = "Sans titre", int InTargetFPS = 60);

template<typename T>
T& GetService()
{
	//TODO: ajouter un test pour être certain que le service est dans la liste.
	std::shared_ptr<T> serv = service_locator.getService<T>();
	assert(serv != nullptr);
	return *serv;
}

LE::IEngineService& GetIEngine();
LE::ILoggerService& GetILogger();
LE::IRessourceManager& GetIRessourceManager();

//Designe pour remplacer LoadTexture de Raylib 
namespace LE
{
	Texture& LoadTexture(std::string InPathTexture);
}

void SendLateCommand(const std::function<void(LE::Engine&)>& InNewCommand);

float RadianToDegree(float InAngleRadian);
float DegreeToRadian(float InAngleDegree);
float GetRandomFloat(float InMin, float InMax);
float GetRandomFloat(Vector2 InMinMax);
Vector2 GetRandomVector(const Rectangle& InRectangle);