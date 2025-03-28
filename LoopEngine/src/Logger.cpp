#include <iostream>
#include <fstream>
#include <cassert>
#include "Logger.h"
#include "raylib.h"

using namespace LE;

LE::Logger::Logger(const TLevel InLoggingLevel, bool InConsoleTraceActive, bool InFileTraceActive, bool InScreenTraceActive)
	:_LoggingLevel(InLoggingLevel)
{
	ActivateFileTrace(InFileTraceActive);
	ActivateConsoleTrace(InConsoleTraceActive);
	ActivateScreenTrace(InScreenTraceActive);
}

Logger::~Logger()
{
	if (_ptrFileStream != nullptr)
	{
		TryCloseFile();
	}
}

void LE::Logger::ActivateFileTrace(bool InIsActive)
{
	if (InIsActive != _IsFileTraceActive)
	{
		_IsFileTraceActive = InIsActive;
		_IsFileTraceActive ? TryOpenFile() : TryCloseFile();
	}
}

void LE::Logger::SetFileTraceName(const string InFileTraceName)
{
	if (_IsFileTraceActive || _ptrFileStream != nullptr)
	{
		this->Log("Cannot change trace file name while file trace is active. Operation aborted.", TLevel::eERROR);
		return;
	}

	if (_TraceFileName.empty())
	{
		this->Log("Trace file name cannot be empty.", TLevel::eERROR);
		return;
	}
	_TraceFileName = InFileTraceName;
}

void LE::Logger::ActivateConsoleTrace(bool InIsActive)
{
	_IsConsoleTraceActive = InIsActive;
}

void LE::Logger::ActivateScreenTrace(bool InIsActive)
{
	_IsScreenTraceActive = InIsActive;
}

void Logger::SetLoggingLevel(const TLevel InLoggingLevel)
{
	_LoggingLevel = InLoggingLevel;
}

void LE::Logger::SetAbortLevel(const TLevel InAbortLevel)
{
	_AbortLevel = InAbortLevel;
}

void LE::Logger::Draw2D() const
{
	if (_IsScreenTraceActive)
	{
		constexpr int msgBoxHeight = 100;
		int curY = GetScreenHeight() - msgBoxHeight;
		DrawRectangle(0, curY, GetScreenWidth(), msgBoxHeight, Color{ 0,0,0,100 });
		for (const auto& msg : _QueueMsg)
		{
			DrawText(msg.c_str(), 0, curY, 24, Color{ 200,200,200,100 });
			curY += 20;
		}
	}
}

void LE::Logger::Log(const string& msg, const TLevel InLoggingLevel)
{
	if (InLoggingLevel >= _LoggingLevel)
	{
		std::string completeMsg = __LevelPrefix[(int)InLoggingLevel] + " - " + msg;
		if (_IsConsoleTraceActive)
		{
			cout << completeMsg << endl;
		}
		if (_IsFileTraceActive && _ptrFileStream != nullptr)
		{
			*_ptrFileStream << completeMsg << endl;
		}
		if (_IsScreenTraceActive)
		{
			if (_QueueMsg.size() > __ScreenMaxMessage)
			{
				_QueueMsg.pop_back();
			}
			_QueueMsg.push_front(completeMsg);
		}
	}

	assert(InLoggingLevel < _AbortLevel);
}

bool LE::Logger::TryOpenFile()
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

bool LE::Logger::TryCloseFile()
{
	if (_ptrFileStream == nullptr || !_ptrFileStream->is_open())
	{
		this->Log("Cannot close the logging file.", TLevel::eERROR);
		return false;
	}
	_ptrFileStream->close();
	_ptrFileStream = nullptr;
	this->Log("Logging file closed.", TLevel::eINFO);
	return true;
}