#include "TimerCallback.h"
#include "Global.h"
#include "Logger.h"

std::string LE::TimerCallback::GetStatusString() const
{
    const std::string looper = IsLooping() ? "yes" : "no";
    const std::string act = IsActive() ? "yes" : "no";
    const std::string res = " (Active = " + act + ") (looping = " + looper + ") (duration = " + std::to_string(GetDuration()) + ") (accumulator = " + std::to_string(_Accumulator) + ")";
    return res;
}

LE::TimerCallback::TimerCallback(float InDuration, const std::function<void()>& InTimerCallback, const std::string& InName, bool InAutoActive, bool InLooping)
    : _Duration(InDuration)
    , _Callback(InTimerCallback)
    , _Active(false)
    , _Looping(InLooping)
    , _Name(InName)
{
    SetVerbosity(true);
    SetLooping(InLooping);
    SetDuration(InDuration);
    SetActive(InAutoActive);
}

bool LE::TimerCallback::Update(float InFrameDuration) {
    if (_Active)
    {
        _Accumulator += InFrameDuration;
        if (_Accumulator > _Duration)
        {
            _Callback();
            if (_Verbosity)
            {
                LOG("Timer was triggered" + GetStatusString(), TLevel::eINFO);
            }
            if (_Looping)
            {
                _Accumulator -= _Duration;
            }
            else
            {
                SetActive(false);
            }
            return true;
        }
    }
    return false;
}

bool LE::TimerCallback::IsActive() const { return _Active; }

void LE::TimerCallback::SetActive(bool InIsActive) {

    _Active = InIsActive;
    if (_Verbosity)
    {
        if (_Active)
        {
            std::string strA = GetStatusString();
            std::string strB = "Timer now active" + strA;
            LOG(strB, TLevel::eINFO);
        }
        else
        {
            LOG("Timer named now inactive" + GetStatusString(), TLevel::eINFO);
        }
    }
}

bool LE::TimerCallback::IsLooping() const { return _Looping; }

void LE::TimerCallback::SetLooping(bool InIsLooping) {

    _Looping = InIsLooping;

    if (IsActive())
    {
        SetActive(IsActive());
    }
}

float LE::TimerCallback::GetDuration() const { return _Duration; }

void LE::TimerCallback::SetDuration(float InDuration)
{
    if (InDuration > 0.f)
    {
        _Duration = InDuration;
    }
    else
    {
        _Duration = 1.f;
        LOG("Timer received invalid duration." + GetStatusString(), TLevel::eWARNING);
    }

    if (IsActive())
    {
        SetActive(IsActive());
    }
}

void LE::TimerCallback::Reset()
{
    if (_Verbosity)
    {
        LOG("Timer was reset" + GetStatusString(), TLevel::eINFO);
    }
    _Accumulator = 0.f;
}

void LE::TimerCallback::SetVerbosity(bool InIsVerbose)
{
    _Verbosity = InIsVerbose;
    if (_Verbosity)
    {
        LOG("Timer now verbose" + GetStatusString(), TLevel::eINFO);

    }
    else
    {
        LOG("Timer now silent" + GetStatusString(), TLevel::eINFO);
    }
}

bool LE::TimerCallback::IsVerbose() const
{
    return _Verbosity;
}

const std::string& LE::TimerCallback::GetName() const
{
    return _Name;
}
