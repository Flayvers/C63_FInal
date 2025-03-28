#pragma once

#include <string>
#include <functional>
#include "raylib.h"
#include "BaseObject.h"
#include "GameObject.h"
#include "TimerCallback.h"

using namespace std;
namespace LE
{
	class GameObjectAnimated : public GameObjectSingleImage
	{
	protected:
		int _NbHorizontalFrame = 1;
		int _NbVerticalFrame = 1;
		int _CurrentFrameIndex = 0;
		bool _IsLooping = true;
		bool _IsVisible = true;

		TimerCallback _Clock;

		void OnFrameChange();
	public:

		GameObjectAnimated(const string& InFilePath, const Vector2& InPosition = { 0.f,0.f }, int InNbHorizontalFrame = 1, int InNbVerticalFrame = 1);
		virtual ~GameObjectAnimated();

		void SetLooping(bool IsLooping);
		void SetVisible(bool IsVisible);
		void SetFrameDuration( float InFrameDuration);
		void SetFrame(int InCurrentFrameIndex);
		void Pause();
		void Start();

		virtual void PreUpdate() override;
		virtual void Draw2D() override;
	};
}
