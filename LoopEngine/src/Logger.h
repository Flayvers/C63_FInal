#pragma once

#include <string>
#include <deque>
#include <iostream>
#include <fstream>
#include <cassert>
#include "ServiceLocator.h"
#include "BaseObject.h"

//Macro qui donne seulement le nom de fichier et non son chemin complet (valide pour Windows seulement).
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

//Définir une macro  qui va accéder au logger via le ServiceLocator
//Il devra ajouter le fichier et la ligne au message passé par l'utilisateur.
//Exemple d'utilisation dans le code: LOG("Attention: objet dans un état invalide!",LE::TLevel::eERROR)
//Affichera dans la console: ERROR - main.cpp:36 Attention: objet dans un état invalide!
#define LOG(msg, level)  if(service_locator.hasService<ILoggerService>()){ service_locator.getService<ILoggerService>()->Log(std::string(__FILENAME__) + ":" + to_string(__LINE__) + " " + msg, level);}

using namespace std;
namespace LE
{
    enum TLevel
    {
        eINFO = 0,
        eWARNING = 1,
        eDEBUG = 2,
        eERROR = 3,

        eMAX,
        eNONE = eMAX,
    };

    class ILoggerService : public IService, public IBaseObject
    {
    public:
        virtual void ActivateConsoleTrace(bool InIsActive) = 0;
        virtual void ActivateScreenTrace(bool InIsActive) = 0;
        virtual void SetLoggingLevel(const TLevel InLoggingLevel) = 0;
        virtual void Log(const string& msg, const TLevel InLoggingLevel) = 0;
        virtual void ActivateFileTrace(bool InIsActive) = 0;
        virtual void SetFileTraceName(const string InFileTraceName) = 0;
        virtual void SetAbortLevel(const TLevel InAbortLevel) = 0;
        virtual void Draw2D() const = 0;
    };

    class Logger : public ServiceBase<ILoggerService>
    {
    public:

        Logger(const TLevel InLoggingLevel = TLevel::eDEBUG, bool InConsoleTraceActive = true, bool InFileTraceActive = true, bool InScreenTraceActive = false);
        virtual ~Logger();

        virtual void ActivateConsoleTrace(bool InIsActive) override;
        virtual void ActivateScreenTrace(bool InIsActive) override;

        virtual void SetLoggingLevel(const TLevel InLoggingLevel) override;
        //Se comporte comme avant, mais en plus, on précède le message par le niveau de l'erreur. Ex:
        //logger.Log("Coucou!",LE::TLevel::eINFO) affichera
        // INFO - Coucou!
        virtual void Log(const string& msg, const TLevel InLoggingLevel) override;

        virtual void ActivateFileTrace(bool InIsActive) override;
        virtual void SetFileTraceName(const string InFileTraceName) override;

        virtual void SetAbortLevel(const TLevel InAbortLevel) override;

        //Dessine en bas de l'écran en petit un carré gris semi-transparent ainsi que le texte des 3 derniers messages en semi-transparent.
        //Cette méthode doit être appelé dans la méthode StartGame (qui contient le while) de Engine.
        virtual void Draw2D() const override;


    private:
        TLevel _LoggingLevel = eDEBUG;
        TLevel _AbortLevel = TLevel::eERROR;

        bool _IsConsoleTraceActive = true;
        bool _IsFileTraceActive = false;

        bool _IsScreenTraceActive = true;


        ofstream* _ptrFileStream = nullptr;
        string _TraceFileName = "LoopEngine.log";
        std::deque<std::string> _ScreenTraceMessages;

        //Méthodes suggérées mais pas obligatoire.
        bool TryOpenFile();
        bool TryCloseFile();
    };
};

