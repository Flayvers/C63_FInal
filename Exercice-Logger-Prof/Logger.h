#pragma once

#include <string>
using namespace std;

namespace LoopEngine
{
    class Logger
    {
    public:
        enum TLevel
        {
            eINFO = 0,
            eWARNING = 1,
            eDEBUG = 2,
            eERROR = 3,

            eMAX,
            eNONE = eMAX,
        };

        Logger(const TLevel InLoggingLevel = TLevel::eDEBUG, bool InConsoleTraceActive = true, bool InFileTraceActive = true);
        ~Logger();

        void ActivateConsoleTrace(bool InIsActive);

        void SetLoggingLevel( const TLevel InLoggingLevel);
        void Log(string msg, const TLevel InLoggingLevel) const;

        //Ne fais rien si la valeur de _IsConsoleTraceActive est identique.
        void ActivateFileTrace(bool InIsActive);
        void ActivateFileTrace(bool InIsActive, const string& InFileName);
        //Log une eERROR si la trace de fichier en actuellement active.
        //Log une eERROR si le nom de fichier est vide.
        void SetFileTraceName(const string InFileTraceName);

        void SetAbortLevel(const TLevel InAbortLevel);

    private:
        TLevel _LoggingLevel = eDEBUG;
        TLevel _AbortLevel = TLevel::eERROR;

        bool _IsConsoleTraceActive = false;
        bool _IsFileTraceActive = false;

        ofstream* _ptrFileStream = nullptr;
        string _TraceFileName = "LoopEngine.log";

        //Méthodes suggérées mais pas obligatoire.
        bool TryOpenFile();
        bool TryCloseFile();
    };
};

