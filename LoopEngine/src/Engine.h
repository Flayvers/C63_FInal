#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>
#include "raylib.h"
#include "ServiceLocator.h"
#include "Scene.h"

using namespace std;

namespace LE
{
	class Engine;
	class IEngineService : public IService
	{
	public:
		virtual void SendLateUpdateCommand(function<void(LE::Engine&)> InNewCommand) = 0;

		virtual void SetClearColor(Color InColor) = 0;
		virtual const Color& GetClearColor() const = 0;
		virtual void SetDebugMode(bool InDebugMode) = 0;
		virtual bool GetDebugMode() const = 0;
		virtual bool IsSceneRegistered(const string& InNewSceneName) const = 0;
	};

	//Fonction globale pour envoyer des commandes a Engine via le Service Locator
	//C'est juste un raccourcis au lieu de directement passer par le Service Locator
	extern void SendCommand(function<void(LE::Engine&)> InNewCommand);

	class Engine : public ServiceBase<IEngineService>
	{
	public:
		//Log INFO: À la fin du constructeur, signaler que Engine est construit.
		//Log ERROR: Resolution négative, TargetFPS en dehors de [5,100].
		Engine(int InResolutionX = 800, int InResolutionY = 480, const string& InTitle = "Sans titre", int InTargetFPS = 60);
		virtual ~Engine();

		//Appeler cette méthode pour ouvrir la fenêtre et démarrer la boucle while
		//Log INFO: Signaler que le jeu a démarré avec la scène InStartSceneName
		//Log ERROR: Scène de démarrage n'existe pas.
		//Log ERROR: Aucune scène enregistrée.
		void StartGame(const string& InStartSceneName);

		//Couleur de fond de l'application
		void SetClearColor(Color InColor);
		const Color& GetClearColor() const;

		//Si à vrai, va afficher le FPS en haut à droite et le message suivant: "Press P to toggle debug"
		//Codez aussi que si l'usager appuie sur la touche p, le mode debug change de vrai à faux ou l'inverse
		void SetDebugMode(bool InDebugMode);
		bool GetDebugMode() const;

		//*=*=*=*=*=*=*=*AVANCÉ=*=*=*=*=*=*=*=*=//
		//Permet d'exécuter une méthode entre 2 frames
		virtual void SendLateUpdateCommand(function<void(LE::Engine&)> InNewCommand);
		//*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=//

		//Scene register/unregister
		//Log INFO: Scène "InNewSceneName" est enregistrée
		//Log ERROR: Scène "InNewSceneName" existe déjà.
		//Log ERROR: Nom fourni est vide.
		void RegisterScene(shared_ptr<LE::Scene> NewScene);
		void UnregisterScene(const string& InSceneName);
		shared_ptr<LE::Scene> FindScene(const string& InSceneName) const;
		weak_ptr<LE::Scene> GetCurrentActiveScene();

		//Si appelé, on doit fermé l'application en quittant le "while" de manière propre.
		void RequestClose();

		//Change la scène active
		//Log INFO: Scène "InNewSceneName" maintenant active.
		//Log WARNING: Scène "InNewSceneName" est déjà activée.
		//Log ERROR: Scène "InNewSceneName" n'existe pas.
		void SwitchScene(const string&  InNewSceneName);
		//Vérifie si la scène est enregistrée dans Engine
		bool IsSceneRegistered(const string& InNewSceneName) const;

	private:
		int _ResolutionX;
		int _ResolutionY;
		string _Title;
		int _TargetFPS;
		Color _ClearColor;
		bool _DebugMode;
		map<string, shared_ptr<Scene>> _RegisteredScenes;
		shared_ptr<Scene> _CurrentActiveScene;
		vector<function<void(Engine&)>> _LateUpdateCommands;
		bool _RequestClose;
	};
}

