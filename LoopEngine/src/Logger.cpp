#include "Logger.h"
#include "raylib.h"

using namespace LE;

Logger::Logger(const TLevel InLoggingLevel, bool InConsoleTraceActive, bool InFileTraceActive, bool InScreenTraceActive)
    : _LoggingLevel(InLoggingLevel), _IsConsoleTraceActive(InConsoleTraceActive), _IsFileTraceActive(InFileTraceActive), _IsScreenTraceActive(InScreenTraceActive)
{
    ActivateFileTrace(InFileTraceActive);
    ActivateConsoleTrace(InConsoleTraceActive);
    ActivateScreenTrace(InScreenTraceActive);
}

Logger::~Logger()
{
    if (_ptrFileStream != nullptr && _ptrFileStream->is_open())
    {
        _ptrFileStream->close();
        delete _ptrFileStream;
        _ptrFileStream = nullptr;
    }
}

void Logger::ActivateConsoleTrace(bool InIsActive)
{
    _IsConsoleTraceActive = InIsActive;
}

void Logger::ActivateScreenTrace(bool InIsActive)
{
    _IsScreenTraceActive = InIsActive;
}

void Logger::SetLoggingLevel(const TLevel InLoggingLevel)
{
    _LoggingLevel = InLoggingLevel;
}

void Logger::Log(const string& msg, const TLevel InLoggingLevel)
{
    string loggingLevel;
    switch (InLoggingLevel)
    {
    case eINFO:
        loggingLevel = "INFO";
        break;
    case eWARNING:
        loggingLevel = "WARNING";
        break;
    case eDEBUG:
        loggingLevel = "DEBUG";
        break;
    case eERROR:
        loggingLevel = "ERROR";
        break;
    default:
        loggingLevel = "UNKNOWN";
        break;
    }

    string loggingMsg = loggingLevel + " - " + msg + "\n";

    if (InLoggingLevel >= _LoggingLevel)
    {
        if (_IsConsoleTraceActive)
        {
            std::cout << loggingMsg;
        }
        if (_IsFileTraceActive && _ptrFileStream != nullptr)
        {
            *_ptrFileStream << loggingMsg;
        }
        if (_IsScreenTraceActive) {
            _ScreenTraceMessages.push_back(loggingMsg);

            while (_ScreenTraceMessages.size() > 3) {
                _ScreenTraceMessages.pop_front();
            }
        }
    }

    assert(InLoggingLevel < _AbortLevel);
}

void Logger::ActivateFileTrace(bool InIsActive)
{
    if (InIsActive != _IsFileTraceActive)
    {
        _IsFileTraceActive = InIsActive;
        _IsFileTraceActive ? TryOpenFile() : TryCloseFile();
    }
}

void Logger::SetFileTraceName(const string InFileTraceName)
{
    if (_IsFileTraceActive || _ptrFileStream != nullptr)
    {
        this->Log("Cannot change trace file name while file trace is active. Operation aborted.", TLevel::eERROR);
        return;
    }

    if (InFileTraceName.empty())
    {
        this->Log("Trace file name cannot be empty.", TLevel::eERROR);
        return;
    }
    _TraceFileName = InFileTraceName;
}

void Logger::SetAbortLevel(const TLevel InAbortLevel)
{
    _AbortLevel = InAbortLevel;
}

bool Logger::TryOpenFile()
{
    if (_ptrFileStream != nullptr)
    {
        this->Log("Cannot open the logging file again.", TLevel::eERROR);
        return false;
    }

    _ptrFileStream = new ofstream(_TraceFileName);
    if (_ptrFileStream->is_open())
    {
        this->Log("Logging file open", TLevel::eINFO);
    }
    else
    {
        this->Log("Logging file could not open", TLevel::eERROR);
        delete _ptrFileStream;
        _ptrFileStream = nullptr;
        return false;
    }
    return true;
}

bool Logger::TryCloseFile()
{
    if (_ptrFileStream == nullptr || !_ptrFileStream->is_open())
    {
        this->Log("Cannot close the logging file.", TLevel::eERROR);
        return false;
    }
    _ptrFileStream->close();
    delete _ptrFileStream;
    _ptrFileStream = nullptr;
    this->Log("Logging file closed.", TLevel::eINFO);
    return true;
}

void Logger::Draw2D() const
{
    //if (_ScreenTraceMessages.empty()) return; // Guard clause

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    DrawRectangle(0, screenHeight - 100, screenWidth, 100, Fade(GRAY, 0.8f));

    int fontSize = 20;
    Color textColor = WHITE;
    int yPos = screenHeight - 90;

    for (auto it = _ScreenTraceMessages.rbegin(); it != _ScreenTraceMessages.rend(); ++it)
    {
        DrawText(it->c_str(), 10, yPos, fontSize, textColor);
        yPos += 20;
    }
}
