#include "LoopEngine/Logger.h"
#include "LoopEngine/Engine.h"
#include "LoopEngine/Global.h"
#include "LoopEngine/GameObject/GOSimpleTexture.h"

LE::GOSimpleTexture::GOSimpleTexture(const std::string& InImageFileName, const std::string& InName)
	:_FilePathToLoad(InImageFileName)
	,GOComposite(InName)
{
	if (InImageFileName.empty())
	{
		LOG("GOSimpleTexture nomme " + _Name + " a un nom de fichier image vide à charger.", TLevel::eERROR);
	}

	if (!FileExists(InImageFileName.c_str()))
	{
		LOG("GOSimpleTexture nomme " + _Name + " a un nom vers un fichier qui n'existe pas.", TLevel::eWARNING);
	}
}

LE::GOSimpleTexture::~GOSimpleTexture()
{
	if (_IsLoaded)
	{
		Unload();
	}
}


void LE::GOSimpleTexture::SetScale(float InScale)
{
	_Scale = InScale;
}

float LE::GOSimpleTexture::GetScale() const
{
	return _Scale;
}

void LE::GOSimpleTexture::SetRotation(float InRotationInDegree)
{
	_Rotation = InRotationInDegree;
}

float LE::GOSimpleTexture::GetRotation() const
{
	return _Rotation;
}

void LE::GOSimpleTexture::SetColorTint(const Color& InColorTint)
{
	_Tint = InColorTint;
}

const Color& LE::GOSimpleTexture::GetColorTint() const
{
	return _Tint;
}

Rectangle LE::GOSimpleTexture::GetCollisionAtPosition() const
{
	Rectangle ret = _CollisionBox;
	Vector2 pivot = { _CollisionBox.width * 0.5f, _CollisionBox.height * 0.5f };
	ret.x -= pivot.x;
	ret.y -= pivot.y;
	return ret;
}

void LE::GOSimpleTexture::Load()
{
	GOComposite::Load();
	if (!FileExists(_FilePathToLoad.c_str()))
	{
		LOG("GOSimpleTexture nomme " + _Name + " a un nom vers un fichier qui n'existe pas.", TLevel::eWARNING);
		return;
	}
	if (_IsLoaded)
	{
		LOG("GOSimpleTexture nomme " + _Name + " est deja charge.", TLevel::eWARNING);
		return;
	}
	_Texture = LE::LoadTexture(_FilePathToLoad);
	_IsLoaded = true;
}

void LE::GOSimpleTexture::Unload()
{
	if (_IsLoaded)
	{
		_IsLoaded = false;
	}
	else
	{
		LOG("GOSimpleTexture nomme " + _Name + " n'est pas charge et ne peut etre dechargee.", TLevel::eWARNING);
	}
	GOComposite::Unload();
}

Texture LE::GOSimpleTexture::GetTexture() const
{
	return _Texture;
}

void LE::GOSimpleTexture::Draw2D()
{
	GOComposite::Draw2D();
	Rectangle source = { 0, 0, (float)_Texture.width, (float)_Texture.height };
	Rectangle dest = { GetWorldPosition().x, GetWorldPosition().y, _CollisionBox.width * _Scale, _CollisionBox.height * _Scale };
	Vector2 pivot = { _CollisionBox.width * 0.5f * _Scale, _CollisionBox.height * 0.5f * _Scale };

	if (_IsLoaded)
	{
		DrawTexturePro(_Texture, source, dest, pivot, _Rotation, WHITE);
	}
	else
	{
		DrawRectanglePro(_CollisionBox, pivot,_Rotation, _Tint);
	}
}

void LE::GOSimpleTexture::DrawDebug()
{
	GOComposite::DrawDebug();
	DrawRectangleLinesEx(GetCollisionAtWorldPosition(), 5.f, _Tint);
}
