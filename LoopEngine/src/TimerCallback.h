#pragma once

#include "raylib.h"

#include <functional>
#include <string>
#include "BaseObject.h"

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
            //Lorsque ce sera écrit =STATUS=, il faut écrire les informations suivantes
            //(name = NAME) (play once = yes/no) (duration = X) (acumulator = Y)
            //La méthode GetStatusString retourne la string =STATUS=
            std::string GetStatusString() const;

            //INFO - TimerCallback now verbose/silent  =STATUS=
            void SetVerbosity(bool InIsVerbose);

            bool IsVerbose() const;

            const std::string& GetName() const;

            //Si temps négatif, on ne change pas sa valeur et on affiche
                //WARNING - Timer invalid duration, no change. =STATUS=
            //Si verbose...
                //INFO - Timer now active/inactive =STATUS=
            TimerCallback(float InDuration = 1.f, const std::function<void()>& InTimerCallback = nullptr, const std::string& InName = "Generic timer", bool InAutoActive = true, bool InIsPlayingOnce = false);

            //Retourne true si est a été activé ce frame.
            //INFO - Timer was triggered =STATUS=
            //Si le callback est nullptr au moment de l'activation, afficher
                //WARNING - Timer callback is nullptr =STATUS=
            bool Update(float InFrameDuration);

            void SetCallback(const std::function<void()>& InTimerCallback);

            bool IsActive() const;
            //Si verbose...
                //INFO - Timer active/inactive =STATUS=
            void SetActive(bool InIsActive);

            bool IsPlayingOnce() const;
            //Si verbose et si actif...
                //INFO - Timer active/inactive =STATUS=
            void PlayOnce(bool InIsPlayingOnce);

            float GetDuration() const;
            //Si actif...
                //INFO - Timer active =STATUS=
                //WARNING - Timer received invalid duration. Duration set to 1.0f  =STATUS=
            void SetDuration(float InDuration);

            //Si verbose...
                //INFO - TimerCallback was reset  =STATUS=
            void Reset();
    };
}