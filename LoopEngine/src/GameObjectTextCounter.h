#pragma once

#include <string>
#include "raylib.h"
#include "GameObjectText.h"
#include "TimerCallback.h"

using namespace std;
namespace LE
{
	class GameObjectTextCounter : public GameObjectText
	{
		protected:
			LE::TimerCallback _Timer;
			unsigned __int32 _Value = 0;

		public:
			GameObjectTextCounter(int InPositionX, int InPositionY);
			virtual ~GameObjectTextCounter();

			void SetActive( bool InIsActive);
			void Reset();
			void SetDuration(float InDuration);

			virtual void PreUpdate() override;
	};
}
