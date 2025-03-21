#include "Engine.h"
#include "Logger.h"

namespace LE
{
    Engine::Engine(int InResolutionX, int InResolutionY, const string& InTitle, int InTargetFPS)
        : _ResolutionX(InResolutionX), _ResolutionY(InResolutionY), _Title(InTitle), _TargetFPS(InTargetFPS),
        _ClearColor(BLACK), _DebugMode(false), _RequestClose(false)
    {
        if (InResolutionX < 0 || InResolutionY < 0)
        {
            LOG("Resolution négative.", eERROR);
        }

        if (InTargetFPS < 5 || InTargetFPS > 100)
        {
            LOG("TargetFPS en dehors de [5,100].", eERROR);
        }

        LOG("Engine est construit.", eINFO);
    }

    Engine::~Engine()
    {
        
    }

    void Engine::StartGame(const string& InStartSceneName)
    {
        if (_RegisteredScenes.empty())
        {
            LOG("Aucune scène enregistrée.", eERROR);
            return;
        }

        auto sceneIt = _RegisteredScenes.find(InStartSceneName);
        if (sceneIt == _RegisteredScenes.end())
        {
            LOG("Scène de démarrage n'existe pas.", eERROR);
            return;
        }

        _CurrentActiveScene = sceneIt->second;
        LOG("Le jeu a démarré avec la scène " + InStartSceneName, eINFO);

        InitWindow(_ResolutionX, _ResolutionY, _Title.c_str());
        SetTargetFPS(_TargetFPS);

        while (!WindowShouldClose() && !_RequestClose)
        {
            BeginDrawing();
            ClearBackground(_ClearColor);

            if (_CurrentActiveScene)
            {
                _CurrentActiveScene->PreUpdate();
                _CurrentActiveScene->CheckAndNotifyCollision();
                _CurrentActiveScene->Draw3D();
                _CurrentActiveScene->Draw2D();
                _CurrentActiveScene->LateUpdate();
            }

            if (_DebugMode)
            {
                DrawFPS(10, 10);
                DrawText("Press P to toggle debug", 10, 30, 20, DARKGRAY);
                service_locator.getService<ILoggerService>()->Draw2D();
            }

            for (auto& command : _LateUpdateCommands)
            {
                command(*this);
            }
            _LateUpdateCommands.clear();

            EndDrawing();

            if (IsKeyPressed(KEY_P))
            {
                _DebugMode = !_DebugMode;
            }
        }

        CloseWindow();
    }


    void Engine::SetClearColor(Color InColor)
    {
        _ClearColor = InColor;
    }

    const Color& Engine::GetClearColor() const
    {
        return _ClearColor;
    }

    void Engine::SetDebugMode(bool InDebugMode)
    {
        _DebugMode = InDebugMode;
    }

    bool Engine::GetDebugMode() const
    {
        return _DebugMode;
    }

    void Engine::SendLateUpdateCommand(function<void(Engine&)> InNewCommand)
    {
        _LateUpdateCommands.push_back(InNewCommand);
    }

    void Engine::RegisterScene(shared_ptr<Scene> NewScene)
    {
        const string& sceneName = NewScene->GetName();
        if (sceneName.empty())
        {
            LOG("Nom fourni est vide.", eERROR);
            return;
        }

        if (_RegisteredScenes.find(sceneName) != _RegisteredScenes.end())
        {
            LOG("Scène " + sceneName + " existe déjà.", eERROR);
            return;
        }

        _RegisteredScenes[sceneName] = NewScene;
        LOG("Scène " + sceneName + " est enregistrée.", eINFO);
    }

    void Engine::UnregisterScene(const string& InSceneName)
    {
        _RegisteredScenes.erase(InSceneName);
    }

    shared_ptr<Scene> Engine::FindScene(const string& InSceneName) const
    {
        auto it = _RegisteredScenes.find(InSceneName);
        if (it != _RegisteredScenes.end())
        {
            return it->second;
        }
        return nullptr;
    }

    weak_ptr<Scene> Engine::GetCurrentActiveScene()
    {
        return _CurrentActiveScene;
    }

    void Engine::RequestClose()
    {
        _RequestClose = true;
    }

    void Engine::SwitchScene(const string& InNewSceneName)
    {
        auto sceneIt = _RegisteredScenes.find(InNewSceneName);
        if (sceneIt == _RegisteredScenes.end())
        {
            LOG("Scène " + InNewSceneName + " n'existe pas.", eERROR);
            return;
        }

        if (_CurrentActiveScene && _CurrentActiveScene->GetName() == InNewSceneName)
        {
            LOG("Scène " + InNewSceneName + " est déjà activée.", eWARNING);
            return;
        }
        _CurrentActiveScene->Unload();
        _CurrentActiveScene = sceneIt->second;
        _CurrentActiveScene->Load();
        LOG("Scène " + InNewSceneName + " maintenant active.", eINFO);
    }

    bool Engine::IsSceneRegistered(const string& InNewSceneName) const
    {
        return _RegisteredScenes.find(InNewSceneName) != _RegisteredScenes.end();
    }

    void SendCommand(function<void(Engine&)> InNewCommand)
    {
        service_locator.getService<IEngineService>()->SendLateUpdateCommand(InNewCommand);
    }
}
