// EXERCICELOGGER.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <cassert>
#include "Logger.h"

using namespace LoopEngine;

int main()
{
    // Écriture dans la console et le fichier "C63Demo/Exercice-Logger/LoopEngine.log"
    Logger* log = new Logger(Logger::TLevel::eINFO, true, true);
    assert(log != nullptr);

    log->Log("De l'information seulement.", Logger::TLevel::eINFO);
    log->Log("Un avertissement, peut causer des problèmes mineurs.", Logger::TLevel::eWARNING);
    log->Log("Pour débogger", Logger::TLevel::eDEBUG);
    // log->Log("Une erreur, c'est grave et va casser l'application. Va suspendre avec la configuration par défaut!", Logger::TLevel::eERROR);
    // log->SetFileTraceName("JeVaisInterrompre!");
    log->ActivateFileTrace(false);
    log->SetFileTraceName("NouveauLog.log");
    log->ActivateFileTrace(true);
    log->Log("Va écrire dans la console et NouveauLog.log.", Logger::TLevel::eINFO);

    log->SetLoggingLevel(Logger::TLevel::eWARNING);
    log->Log("Cette entrée sera ignorée.", Logger::TLevel::eINFO);

    // Ne va jamais interrompre
    log->SetAbortLevel(Logger::eNONE);
    // Cause une erreur
    log->SetFileTraceName("");

    // Toujours libérer sa mémoire
    delete log;
    log = nullptr;
}