#include <iostream>
#include <fstream>
#include "Logger.h"
#include <cassert>

using namespace LoopEngine;

LoopEngine::Logger::Logger(const TLevel InLoggingLevel, bool InConsoleTraceActive, bool InFileTraceActive)
	:_LoggingLevel(InLoggingLevel)
{
	ActivateFileTrace(InFileTraceActive);
	ActivateConsoleTrace(InConsoleTraceActive);
}

Logger::~Logger()
{
	if (_ptrFileStream != nullptr)
	{
		TryCloseFile();
	}
}

void LoopEngine::Logger::ActivateFileTrace(bool InIsActive, const string& InFileName)
{
	if (InIsActive != _IsFileTraceActive)
	{
		SetFileTraceName(InFileName);
		ActivateFileTrace(InIsActive);
	}
}

void LoopEngine::Logger::ActivateFileTrace(bool InIsActive)
{
	if (InIsActive != _IsFileTraceActive)
	{
		_IsFileTraceActive = InIsActive;
		_IsFileTraceActive ? TryOpenFile() : TryCloseFile();
	}
}

void LoopEngine::Logger::SetFileTraceName(const string InFileTraceName)
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

void LoopEngine::Logger::ActivateConsoleTrace(bool InIsActive)
{
	_IsConsoleTraceActive = InIsActive;
}

void Logger::SetLoggingLevel(const TLevel InLoggingLevel)
{
	_LoggingLevel = InLoggingLevel;
}

void LoopEngine::Logger::SetAbortLevel(const TLevel InAbortLevel)
{
	_AbortLevel = InAbortLevel;
}

void Logger::Log(string msg, const TLevel InLoggingLevel) const
{
	if (InLoggingLevel >= _LoggingLevel)
	{
		if (_IsConsoleTraceActive)
		{
			cout << msg << endl;
		}
		if (_IsFileTraceActive && _ptrFileStream != nullptr)
		{
			*_ptrFileStream << msg << endl;
		}
	}

	assert(InLoggingLevel < _AbortLevel);
}

bool LoopEngine::Logger::TryOpenFile()
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

bool LoopEngine::Logger::TryCloseFile()
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