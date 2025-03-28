#include "Button.h"
#include "Logger.h"
#include "GameObjectAnimated.h"
#include "Global.h"

void LE::GameObjectAnimated::OnFrameChange()
{
	++_CurrentFrameIndex;
	if(!_IsLooping && _CurrentFrameIndex == (_NbHorizontalFrame * _NbVerticalFrame))
	{
		_CurrentFrameIndex = 0;
		_IsVisible = false;
		Pause();
	}
	SetFrame(_CurrentFrameIndex);
}

LE::GameObjectAnimated::GameObjectAnimated(const string& InFilePath, const Vector2& InPosition, int InFrameWidth, int InFrameHeight)
	:GameObjectSingleImage(InFilePath,"Animation")
	,_NbHorizontalFrame(InFrameWidth)
	, _NbVerticalFrame(InFrameHeight)
{
	SetPosition(InPosition);
	_Clock.SetDuration(0.1f);
	_Clock.PlayOnce(false);
	_Clock.SetActive(true);
	///////////////////////////
	//12) Trouvez une solution pour que _Clock appelle la méthode OnFrameChange() de this à chaque déclenchement
	_Clock.SetCallback(std::bind(&GameObjectAnimated::OnFrameChange, this));
	//Retournez main.cpp pour la suite
	///////////////////////////
}

LE::GameObjectAnimated::~GameObjectAnimated()
{
}

void LE::GameObjectAnimated::SetLooping(bool IsLooping)
{
	_IsLooping = IsLooping;
}

void LE::GameObjectAnimated::SetVisible(bool IsVisible)
{
	_IsVisible = IsVisible;
}

void LE::GameObjectAnimated::SetFrameDuration(float InFrameDuration)
{
	_Clock.SetDuration(InFrameDuration);
}

void LE::GameObjectAnimated::SetFrame(int InCurrentFrameIndex)
{
	_CurrentFrameIndex = InCurrentFrameIndex % (_NbHorizontalFrame * _NbVerticalFrame);
}

void LE::GameObjectAnimated::Pause()
{
	_Clock.SetActive(false);
}

void LE::GameObjectAnimated::Start()
{
	_IsVisible = true;
	_Clock.SetActive(true);
}

void LE::GameObjectAnimated::PreUpdate()
{
	_Clock.Update(GetFrameTime());
}

void LE::GameObjectAnimated::Draw2D()
{
	if (!_IsVisible)
	{return;}
	const float singleFrameWidth = (float)_Texture.width / _NbHorizontalFrame;
	const float singleFrameHeight = (float)_Texture.height / _NbVerticalFrame;

	///////////////////////////
	//11) La valeur courrante de _CurrentFrameIndex est 2 et vous devrez faire afficher le 3 dans l'image. Autrement dit,
	//  selon la valeur de _CurrentFrameIndex, trouvez une manière de ...
	//	a) Trouver la ligne sur laquelle on est rendu
	//	b) Trouver la colone sur laquelle on est rendu
	//	c) Découper la source correctement en fonction de la ligne et colonne.
	//	d) Dans le main, changez le paramètre de la ligne animNumbers->SetFrame(2) pour vous assurez que ça fonctionne.
	const int line = _CurrentFrameIndex % _NbHorizontalFrame;
	const int column = _CurrentFrameIndex / _NbVerticalFrame ;
	const Rectangle source = { line * singleFrameWidth, column * singleFrameWidth, singleFrameWidth, singleFrameHeight};
	//Allez ensuite le constructeur de GameObjectAnimated
	///////////////////////////
	const Rectangle dest = { GetPosition().x, GetPosition().y, _CollisionBox.width * _Scale, _CollisionBox.height * _Scale };
	const Vector2 pivot = { _CollisionBox.width * 0.5f * _Scale, _CollisionBox.height * 0.5f * _Scale };

	if (_IsLoaded)
	{
		DrawTexturePro(_Texture, source, dest, pivot, _Rotation, WHITE);
	}
	else
	{
		DrawRectanglePro(_CollisionBox, pivot, _Rotation, _Tint);
	}

	if (GetIEngine().GetDebugMode())
	{
		DrawRectangleLinesEx(GetCollisionAtPosition(), 5.f, _Tint);
	}
}
