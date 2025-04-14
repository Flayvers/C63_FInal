#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>

#include "raylib.h"

#include "LoopEngine/ServiceLocator.h"


using namespace std;

namespace LE
{
	class Engine;
	class GOComposite;
	class IEngineService : public IService
	{
	public:
		virtual void SendLateUpdateCommand(function<void(LE::Engine&)> InNewCommand) = 0;

		virtual void SetClearColor(Color InColor) = 0;
		virtual const Color& GetClearColor() const = 0;
		virtual void SetDebugMode(bool InDebugMode) = 0;
		virtual bool GetDebugMode() const = 0;
		virtual bool IsSceneRegistered(const string& InNewSceneName) const = 0;
		virtual string GetCurrentActiveSceneName() const = 0;
	};

	//Raccourcis au lieu de directement passer par le Service Locator
	extern void SendCommand(function<void(LE::Engine&)> InNewCommand);

	class Engine : public ServiceBase<IEngineService>
	{
	protected:
		map<string, shared_ptr<LE::GOComposite>> _NameToScene;
		weak_ptr<LE::GOComposite> _ActiveScene;
		Color _ClearColor = BLACK;
		int _ResolutionX = 800;
		int _ResolutionY = 800;
		int _FPS = 60;
		string _Title = "Sans titre";

		bool _DebugMode = false;
		bool _RequestClose = false;

		vector<function<void(LE::Engine&)>> _EngineCommandList;
	
	public:
		Engine(int InResolutionX = 800, int InResolutionY = 480, const string& InTitle = "Sans titre", int InTargetFPS = 60);
		virtual ~Engine();

		void StartGame(const string& InStartSceneName);

		void SetClearColor(Color InColor) override;
		const Color& GetClearColor() const override;

		void SetDebugMode(bool InDebugMode) override;
		bool GetDebugMode() const override;

		virtual void SendLateUpdateCommand(function<void(LE::Engine&)> InNewCommand);

		void RegisterScene(shared_ptr<LE::GOComposite> NewScene);
		void UnregisterScene(const string& InSceneName);
		shared_ptr<LE::GOComposite> FindScene(const string& InSceneName) const;
		weak_ptr<LE::GOComposite> GetCurrentActiveScene();

		void RequestClose();

		void SwitchScene(const string&  InNewSceneName);
		bool IsSceneRegistered(const string& InNewSceneName) const override;
		string GetCurrentActiveSceneName() const override;
	};
}

