#include "Logger.h"

using namespace std;

namespace LoopEngine {

    Logger::Logger(const TLevel InLoggingLevel, bool InConsoleTraceActive, bool InFileTraceActive)
        : _LoggingLevel(InLoggingLevel),
        _IsConsoleTraceActive(InConsoleTraceActive),
        _IsFileTraceActive(InFileTraceActive) {
        if (InFileTraceActive) {
            TryOpenFile();
        }
    }

    Logger::~Logger() {
        TryCloseFile();
    }

    void Logger::ActivateConsoleTrace(bool InIsActive) {
        _IsConsoleTraceActive = InIsActive;
    }

    void Logger::SetLoggingLevel(const TLevel InLoggingLevel) {
        _LoggingLevel = InLoggingLevel;
    }

    void Logger::Log(string msg, const TLevel InLoggingLevel) const {
        SetConsoleOutputCP(1252);
        if (InLoggingLevel < _LoggingLevel) {
            return;
        }

        string prefix;
        switch (InLoggingLevel) {
        case eINFO:    prefix = "[INFO] "; break;
        case eWARNING: prefix = "[WARNING] "; break;
        case eDEBUG:   prefix = "[DEBUG] "; break;
        case eERROR:   prefix = "[ERROR] "; break;
        default:       prefix = "[UNKNOWN] "; break;
        }

        string fullMsg = prefix + msg;

        if (_IsConsoleTraceActive) {

            cout << fullMsg << endl;
        }

        if (_IsFileTraceActive && _ptrFileStream != nullptr && _ptrFileStream->is_open()) {
            (*_ptrFileStream) << fullMsg << endl;
        }
        assert(InLoggingLevel >= _AbortLevel);

        /* if (InLoggingLevel >= _AbortLevel) {
            CustomAbort(fullMsg);
        }*/
    }

    void Logger::ActivateFileTrace(bool InIsActive) {
        if (InIsActive == _IsFileTraceActive) {
            return;
        }

        _IsFileTraceActive = InIsActive;

        if (_IsFileTraceActive) {
            TryOpenFile();
        }
        else {
            TryCloseFile();
        }
    }

    void Logger::ActivateFileTrace(bool InIsActive, const string& InFileName) {
        if (InFileName.empty()) {
            Log("ActivateFileTrace : nom de fichier vide", eERROR);
            return;
        }

        SetFileTraceName(InFileName);
        ActivateFileTrace(InIsActive);
    }

    void Logger::SetFileTraceName(const string InFileTraceName) {
        if (InFileTraceName.empty()) {
            if (_IsFileTraceActive) {
                Log("SetFileTraceName: nom de fichier vide", eERROR);
            }
            return;
        }
        else if (_IsFileTraceActive) {
            Log("SetFileTraceName: Impossible de changer le nom du fichier lorsque la trace est activé", eERROR);
        }

        if (InFileTraceName == _TraceFileName) {
            return;
        }

        string previousName = _TraceFileName;
        _TraceFileName = InFileTraceName;

        if (_IsFileTraceActive) {
            if (!TryOpenFile()) {
                _TraceFileName = previousName;
                if (!TryOpenFile()) {
                    _IsFileTraceActive = false;
                    Log("SetFileTraceName : échec d'ouverture du fichier, désactivation de la trace fichier", eERROR);
                }
                else {
                    Log("SetFileTraceName : échec d'ouverture du nouveau fichier, retour à l'ancien", eERROR);
                }
            }
        }
    }

    void Logger::SetAbortLevel(const TLevel InAbortLevel) {
        _AbortLevel = InAbortLevel;
    }

    bool Logger::TryOpenFile() {
        if (_ptrFileStream != nullptr) {
            return true;
        }

        _ptrFileStream = new ofstream();
        _ptrFileStream->open(_TraceFileName, ios::app);

        if (!_ptrFileStream->is_open()) {
            delete _ptrFileStream;
            _ptrFileStream = nullptr;
            return false;
        }

        return true;
    }

    bool Logger::TryCloseFile() {
        if (_ptrFileStream == nullptr) {
            return true;
        }

        if (_ptrFileStream->is_open()) {
            _ptrFileStream->close();
        }

        delete _ptrFileStream;
        _ptrFileStream = nullptr;

        return true;
    }

    void Logger::CustomAbort(const string fullMsg) const {
        string abortMessage = "ABORTED:\n" + fullMsg;

        MessageBoxA(nullptr, abortMessage.c_str(), "ERREUR", MB_ICONERROR);


        exit(EXIT_FAILURE);
    }

}