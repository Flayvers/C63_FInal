#include "raylib.h"

#include <functional>
#include <string>

namespace LE
{
    class TimerCallback 
    {
        private:
            std::function<void()> _Callback;
            float _Duration = 0.f;
            float _Accumulator = 0.f;
            bool _Active = true;
            bool _Looping = false;
            std::string _Name = "No name";
            bool _Verbosity = true;

        public:
            //=STATUS= signifie qu'il faut écrire
            //(name = NAME) (looping = yes/no) (duration = X) (acumulator = Y)
            //Écrire cette méthode pour retourner =STATUS=
            std::string GetStatusString() const;

            const std::string& GetName() const;

            //WARNING - Timer invalid duration. =STATUS=
            //Si verbose...
            //INFO - Timer now active/inactive =STATUS=
            TimerCallback(float InDuration, const std::function<void()>& InTimerCallback, const std::string& InName, bool InAutoActive = true, bool InLooping = false);

            //Retourne true si est a été activé ce frame.
            //INFO - Timer was triggered =STATUS=
            bool Update(float InFrameDuration);

            bool IsActive() const;
            //Si verbose...
            //INFO - Timer active/inactive =STATUS=
            void SetActive(bool InIsActive);

            bool IsLooping() const;
            //Si verbose et si actif en ce moment...
            //INFO - Timer active/inactive =STATUS=
            void SetLooping(bool InIsLooping);

            float GetDuration() const;
            //Seulement si c'est actif en ce moment...
            //INFO - Timer active =STATUS=
            //WARNING - Timer received invalid duration. Duration set to 1.0f  =STATUS=
            void SetDuration(float InDuration);

            //Si verbose...
            //INFO - TimerCallback was reset  =STATUS=
            void Reset();

            //Affiche toujours
            //INFO - TimerCallback now verbose/silent  =STATUS=
            void SetVerbosity(bool InIsVerbose);
            bool IsVerbose() const;
    };
}