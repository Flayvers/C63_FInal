#pragma once

#include <string>
#include <functional>
#include <vector>
#include "raylib.h"
#include "LoopEngine/BaseObject.h"
#include "LoopEngine/TimerCallback.h"
#include "LoopEngine/GameObject/GOSimpleTexture.h"

using namespace std;
namespace LE
{
	class GOAnimated : public GOSimpleTexture
	{
	protected:
		int _NbHorizontalFrame = 1;
		int _NbVerticalFrame = 1;
		int _CurrentFrameIndex = 0;
		bool _IsLooping = true;
		bool _IsVisible = true;
		vector<int> _FramesIndexToPlay;
		TimerCallback _Clock;

		void OnFrameChange();
	public:

		GOAnimated(const string& InFilePath, const Vector2& InPosition = { 0.f,0.f }, int InNbHorizontalFrame = 1, int InNbVerticalFrame = 1);
		virtual ~GOAnimated();

		void SetLooping(bool IsLooping);
		void SetVisible(bool IsVisible);
		void SetFrameDuration( float InFrameDuration);
		void SetFrames( vector<int>&& InFramesToPlay);
		void Pause();
		void Start();

		virtual void PreUpdate() override;
		virtual void Draw2D() override;
		virtual void DrawDebug() override;
	};
}
