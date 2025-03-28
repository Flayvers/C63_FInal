#include "Engine.h"
#include "Scene.h"
#include "Logger.h"
#include "raylib.h"
#include "ServiceLocator.h"

LE::Engine::Engine(int InResolutionX, int InResolutionY, const std::string& InTitle, int InTargetFPS)
	:_ResolutionX(InResolutionX)
	, _ResolutionY(InResolutionY)
	, _Title(InTitle)
	, _FPS(InTargetFPS)
{

}

LE::Engine::~Engine()
{
	_NameToScene.clear();
	_EngineCommandList.clear();
}

void LE::Engine::SetClearColor(Color InColor)
{
	_ClearColor = InColor;
}

const Color& LE::Engine::GetClearColor() const
{
	return _ClearColor;
}

void LE::Engine::SetDebugMode(bool InDebugMode)
{
	_DebugMode = InDebugMode;
	service_locator.getService<ILoggerService>()->ActivateScreenTrace(InDebugMode);
}

bool LE::Engine::GetDebugMode() const
{
	return _DebugMode;
}

void LE::Engine::SendLateUpdateCommand(std::function<void(LE::Engine&)> InNewCommand)
{
	_EngineCommandList.push_back(InNewCommand);
}

void LE::Engine::StartGame(const std::string& InStartSceneName)
{
	InitWindow(_ResolutionX, _ResolutionY, _Title.c_str());
	SetTargetFPS(_FPS);
	if (!IsSceneRegistered(InStartSceneName))
	{
		return;
	}
	SwitchScene(InStartSceneName);

	while (!WindowShouldClose() && !_RequestClose)
	{
		if (auto scenePtr = _ActiveScene.lock())
		{
			BeginDrawing();
			ClearBackground(_ClearColor);
			scenePtr->CheckAndNotifyCollision();
			scenePtr->PreUpdate();
			scenePtr->Draw3D();
			scenePtr->Draw2D();
			if (_DebugMode)
			{
				scenePtr->DrawDebug();
				DrawFPS(0, 0);
				DrawText("Press P to toggle debug", 100, 0, 20, BLACK);
				service_locator.getService<ILoggerService>()->Draw2D();
			}
			scenePtr->LateUpdate();
			if (IsKeyPressed(KEY_P))
			{
				SetDebugMode(!GetDebugMode());
			}
			EndDrawing();

			for (auto it = _EngineCommandList.begin(); it != _EngineCommandList.end(); ++it)
			{
				std::function<void(LE::Engine&)> element = *it;
				element(*this);
			}
			_EngineCommandList.clear();
		}
	};
}

void LE::Engine::RequestClose()
{
	_RequestClose = true;
}

void LE::Engine::SwitchScene(const std::string& InNewSceneName)
{
	if (IsSceneRegistered(InNewSceneName))
	{
		if (auto oldScene = _ActiveScene.lock())
		{
			if (oldScene->GetName() == InNewSceneName)
			{
				LOG("Scene " + InNewSceneName + " deja active.", TLevel::eWARNING);
				return;
			}
			else
			{
				oldScene->Unload();
			}
		}
		_ActiveScene = _NameToScene[InNewSceneName];
		if (auto newScene = _ActiveScene.lock())
		{
			newScene->Load();
			LOG("Scene " + newScene->GetName() + " maintenant active.", TLevel::eINFO);
		}
	}
	else
	{
		LOG("Scene " + InNewSceneName + " n'est pas enregistre!", TLevel::eERROR);
	}
}

bool LE::Engine::IsSceneRegistered(const std::string& InNewSceneName) const
{
	return _NameToScene.find(InNewSceneName) != _NameToScene.end();
}

void LE::Engine::RegisterScene(std::shared_ptr<LE::Scene> InNewScene)
{
	_NameToScene[InNewScene->GetName()] = InNewScene;
}

void LE::Engine::UnregisterScene(const std::string& InSceneName)
{
	map<string, shared_ptr<LE::Scene>>::iterator f = _NameToScene.find(InSceneName);
	if (f != _NameToScene.end())
	{
		_NameToScene.erase(f);
	}
}

shared_ptr<LE::Scene> LE::Engine::FindScene(const string& InSceneName) const
{
	auto f = _NameToScene.find(InSceneName);
	if (f != _NameToScene.end())
	{
		return (*f).second;
	}
	return nullptr;
}

weak_ptr<LE::Scene> LE::Engine::GetCurrentActiveScene()
{
	return _ActiveScene;
}

void LE::SendCommand(function<void(LE::Engine&)> InNewCommand)
{
	service_locator.getService<IEngineService>()->SendLateUpdateCommand(InNewCommand);
}
