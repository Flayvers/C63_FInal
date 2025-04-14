#pragma once

#include <string>
#include "raylib.h"
#include "LoopEngine/TimerCallback.h"
#include "LoopEngine/GameObject/GOText.h"

using namespace std;
namespace LE
{
	class GOTextCounter : public GOText
	{
		protected:
			LE::TimerCallback _Timer;
			unsigned __int32 _Value = 0;

		public:
			GOTextCounter(int InPositionX, int InPositionY);
			virtual ~GOTextCounter();

			void SetActive( bool InIsActive);
			void Reset();
			void SetDuration(float InDuration);

			virtual void PreUpdate() override;
	};
}
