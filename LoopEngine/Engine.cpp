#include <cassert>

#include "Engine.h"
#include "Logger.h"
#include "raylib.h"
#include "LoopEngine/ServiceLocator.h"
#include "LoopEngine/RessourceManager.h"
#include "LoopEngine/Visitor.h"
#include "LoopEngine/GameObject/GOComposite.h"

LE::Engine::Engine(int InResolutionX, int InResolutionY, const std::string& InTitle, int InTargetFPS)
	:_ResolutionX(InResolutionX)
	,_ResolutionY(InResolutionY)
	,_Title(InTitle)
	,_FPS(InTargetFPS)
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

				//Position update
				ParentPositionUpdate parentPositionUpdate;
				parentPositionUpdate.Visit(scenePtr);

				//Collision
				Collector collector;
				collector.Visit(scenePtr);
				std::vector<std::shared_ptr<GameObject>> allGo = collector.GetCollection();
				for (int i = 0; i < allGo.size(); ++i)
				{
					for (int j = i + 1; j < allGo.size(); ++j)
					{
						allGo[i]->CheckCollision(allGo[j], true);
						allGo[j]->CheckCollision(allGo[i], true);
					}
				}

				scenePtr->PreUpdate();
				scenePtr->Draw3D();
				scenePtr->Draw2D();
				if (_DebugMode)
				{
					scenePtr->DrawDebug();
				}
				scenePtr->LateUpdate();
				if (IsKeyPressed(KEY_P))
				{
					SetDebugMode(!GetDebugMode());
				}
				if (_DebugMode)
				{
					DrawFPS(0, 0);
					DrawText("Press P to toggle debug", 100, 0, 20, BLACK);
					service_locator.getService<ILoggerService>()->Draw2D();
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
	service_locator.getService<LE::IRessourceManager>()->UnloadAll();
}

void LE::Engine::RequestClose()
{
	_RequestClose = true;
}

void LE::Engine::SwitchScene(const std::string& InNewSceneName)
{
	if (not _EngineCommandList.empty())
	{
		LOG("Engine command not empty while switching scene: unwanted behaviors might occur. Reason: You stacked engine commands while switching scenes.", TLevel::eERROR);
	}
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

string LE::Engine::GetCurrentActiveSceneName() const
{
	string name = "NO SCENE";
	if (auto scenePtr = _ActiveScene.lock())
	{
		name = scenePtr->GetName();
	}
	return name;
}

void LE::Engine::RegisterScene(std::shared_ptr<LE::GOComposite> InNewScene)
{
	_NameToScene[InNewScene->GetName()] = InNewScene;
}

void LE::Engine::UnregisterScene(const std::string& InSceneName)
{
	map<string, shared_ptr<LE::GOComposite>>::iterator f = _NameToScene.find(InSceneName);
	if (f != _NameToScene.end())
	{
		_NameToScene.erase(f);
	}
}

shared_ptr<LE::GOComposite> LE::Engine::FindScene(const string& InSceneName) const
{
	auto f = _NameToScene.find(InSceneName);
	if (f != _NameToScene.end())
	{
		return (*f).second;
	}
	return nullptr;
}

weak_ptr<LE::GOComposite> LE::Engine::GetCurrentActiveScene()
{
	return _ActiveScene;
}

void LE::SendCommand(function<void(LE::Engine&)> InNewCommand)
{
	service_locator.getService<IEngineService>()->SendLateUpdateCommand(InNewCommand);
}
