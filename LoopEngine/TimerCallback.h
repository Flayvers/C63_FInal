#pragma once
#include <functional>
#include <string>
#include "raylib.h"
#include "LoopEngine/BaseObject.h"

namespace LE
{
    class TimerCallback : public IBaseObject
    {
        private:
            std::function<void()> _Callback;
            float _Duration = 0.f;
            float _Accumulator = 0.f;
            bool _Active = true;
            bool _IsPlayingOnce = false;
            std::string _Name = "No name";
            bool _Verbosity = true;

        public:
            TimerCallback(float InDuration = 1.f, const std::function<void()>& InTimerCallback = nullptr, const std::string& InName = "Generic timer", bool InAutoActive = true, bool InIsPlayingOnce = false);

            void SetCallback(const std::function<void()>& InTimerCallback);
            bool Update(float InFrameDuration);

            const std::string& GetName() const;

            std::string GetStatusString() const;
            void SetVerbosity(bool InIsVerbose);
            bool IsVerbose() const;

            bool IsActive() const;
            void SetActive(bool InIsActive);

            bool IsPlayingOnce() const;
            void PlayOnce(bool InIsPlayingOnce);

            float GetDuration() const;
            void SetDuration(float InDuration);

            void Reset();
    };
}