#include <numeric>

#include "LoopEngine/Logger.h"
#include "LoopEngine/Global.h"
#include "LoopEngine/GameObject/GoButton.h"
#include "LoopEngine/GameObject/GOAnimated.h"

void LE::GOAnimated::OnFrameChange()
{
	if(_FramesIndexToPlay.empty())
	{return;}

	++_CurrentFrameIndex;
	if(!_IsLooping && _CurrentFrameIndex >= _FramesIndexToPlay.size())
	{
		_CurrentFrameIndex = 0;
		_IsVisible = false;
		Pause();
	}
	_CurrentFrameIndex = _CurrentFrameIndex % _FramesIndexToPlay.size();
}

LE::GOAnimated::GOAnimated(const string& InFilePath, const Vector2& InPosition, int InFrameWidth, int InFrameHeight)
	:GOSimpleTexture(InFilePath,"Animation")
	,_NbHorizontalFrame(InFrameWidth)
	, _NbVerticalFrame(InFrameHeight)
	, _FramesIndexToPlay(_NbHorizontalFrame* _NbVerticalFrame)
{
	SetPosition(InPosition);
	_Clock.SetDuration(0.1f);
	_Clock.PlayOnce(false);
	_Clock.SetActive(true);
	std::iota(_FramesIndexToPlay.begin(), _FramesIndexToPlay.end(), 0);
	///////////////////////////
	//10) Trouvez une solution pour que _Clock appelle la méthode OnFrameChange() de this à chaque déclenchement
	std::function<void()> methodOnFrameChange = [this]() {OnFrameChange();};
	_Clock.SetCallback(methodOnFrameChange);
	///////////////////////////
}

LE::GOAnimated::~GOAnimated()
{
}

void LE::GOAnimated::SetLooping(bool IsLooping)
{
	_IsLooping = IsLooping;
}

void LE::GOAnimated::SetVisible(bool IsVisible)
{
	_IsVisible = IsVisible;
}

void LE::GOAnimated::SetFrameDuration(float InFrameDuration)
{
	_Clock.SetDuration(InFrameDuration);
}

void LE::GOAnimated::SetFrames(vector<int>&& InFramesToPlay)
{
	_FramesIndexToPlay = InFramesToPlay;
	for (auto f = begin(_FramesIndexToPlay); f != end(_FramesIndexToPlay); ++f)
	{
		ASSERT(*f >= 0 && *f < (_NbHorizontalFrame * _NbVerticalFrame), "Animation index with invalid range.");
	}
}

void LE::GOAnimated::Pause()
{
	_Clock.SetActive(false);
}

void LE::GOAnimated::Start()
{
	_IsVisible = true;
	_Clock.SetActive(true);
}

void LE::GOAnimated::PreUpdate()
{
	_Clock.Update(GetFrameTime());
}

void LE::GOAnimated::Draw2D()
{
	if (!_IsVisible || _FramesIndexToPlay.empty())
	{return;}
	float singleFrameWidth = (float)_Texture.width / _NbHorizontalFrame;
	float singleFrameHeight = (float)_Texture.height / _NbVerticalFrame;
	const int _currentFrameIndexToDisplay = _FramesIndexToPlay[_CurrentFrameIndex];
	///////////////////////////
	//11) Selon la valeur de _currentFrameIndexToDisplay, trouvez une manière de ...
	//	a) Trouver la ligne sur laquelle on est rendu
	//	b) Trouver la colone sur laquelle on est rendu
	//	c) Découper la source correctement en fonction de la ligne et colonne afin qu'on voit les images changées dans le bon ordre (1 à 16).
	int line = _currentFrameIndexToDisplay % _NbHorizontalFrame;
	int column = _currentFrameIndexToDisplay / _NbVerticalFrame;
	Rectangle source = { (float)(line) *singleFrameWidth, (float)column * singleFrameHeight, singleFrameWidth, singleFrameHeight};
	//Retournez ensuite dans main.cpp
	///////////////////////////
	Rectangle dest = { GetWorldPosition().x, GetWorldPosition().y, _CollisionBox.width * _Scale, _CollisionBox.height * _Scale };
	Vector2 pivot = { _CollisionBox.width * 0.5f * _Scale, _CollisionBox.height * 0.5f * _Scale };

	if (_IsLoaded)
	{
		DrawTexturePro(_Texture, source, dest, pivot, _Rotation, WHITE);
	}
	else
	{
		DrawRectanglePro(_CollisionBox, pivot, _Rotation, _Tint);
	}
}

void LE::GOAnimated::DrawDebug()
{
	GameObject::DrawDebug();
	DrawRectangleLinesEx(GetCollisionAtWorldPosition(), 5.f, _Tint);
}
