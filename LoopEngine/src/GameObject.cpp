#include "GameObject.h"
#include "Logger.h"
#include "Engine.h"
#include "Global.h"

LE::GameObject2D::GameObject2D(const std::string& InName)
	:_Name(InName)
{
	if (_Name.empty())
	{
		LOG("Un GameObject2D a un nom vide!", TLevel::eWARNING);
	}
}

LE::GameObject2D::GameObject2D(Vector2 InPosition, Vector2 InCollisionBox, int InCollisionMask, const std::string& InName)
	:_Name(InName)
	, _CollisionBox{ InPosition.x,InPosition.y,InCollisionBox.x,InCollisionBox.y }
	, _CollisionMaks(InCollisionMask)
{
	if (_CollisionBox.width < 0.f || _CollisionBox.height < 0.f)
	{
		LOG("GameObject2D nomme " + _Name + " a une boite de collision invalide (valeur negative). Collision desactivee ", TLevel::eWARNING);
		InCollisionMask = 0;
	}

	if (_Name.empty())
	{
		LOG("Un GameObject2D a un nom vide!", TLevel::eWARNING);
	}
}

LE::GameObject2D::~GameObject2D()
{
}

void LE::GameObject2D::SetCollisionMask(int InCollisionGroup)
{
	_CollisionMaks = InCollisionGroup;
}

int LE::GameObject2D::GetCollisionMask() const
{
	return _CollisionMaks;
}

void LE::GameObject2D::SetPosition(Vector2 InPosition)
{
	_CollisionBox.x = InPosition.x;
	_CollisionBox.y = InPosition.y;
}

const Vector2& LE::GameObject2D::GetPosition() const
{
	return { _CollisionBox.x ,_CollisionBox.y };
}

void LE::GameObject2D::SetName(const std::string& InName)
{
	_Name = InName;
}

const std::string& LE::GameObject2D::GetName() const
{
	return _Name;
}

void LE::GameObject2D::SetCollisionBox(const Vector2& InNewBoxSize)
{
	if (InNewBoxSize.x < 0.f || InNewBoxSize.y < 0.f)
	{
		LOG("GameObject2D nomme " + _Name + " a une boite de collision invalide (valeur negative). La boite de collision ne sera pas modifiee.", TLevel::eWARNING);
	}
	else
	{
		_CollisionBox.width = InNewBoxSize.x;
		_CollisionBox.height = InNewBoxSize.y;
	}
}

const Vector2& LE::GameObject2D::GetCollisionBox() const
{
	return { _CollisionBox.width,_CollisionBox.height };
}

const Rectangle& LE::GameObject2D::GetCollisionAtPosition() const
{
	return _CollisionBox;
}


void LE::GameObject2D::OnCollisionEvent(std::function<void(const CollisionEvent&)> InFunctionToCall)
{
	_CallbackOnCollision = InFunctionToCall;

}

bool LE::GameObject2D::CheckCollision(const std::weak_ptr<GameObject2D> InOtherGO, bool InNotify)
{
	if (auto ptrOther = InOtherGO.lock())
	{
		if ((GetCollisionMask() & ptrOther->GetCollisionMask()) != 0)
		{
			bool areColliding = CheckCollisionRecs(GetCollisionAtPosition(), ptrOther->GetCollisionAtPosition());
			if (InNotify && areColliding)
			{
				CollisionEvent event;
				event._Position.x = (GetPosition().x + ptrOther->GetPosition().x) * 0.5f;
				event._Position.y = (GetPosition().y + ptrOther->GetPosition().y) * 0.5f;
				event._OtherObject = ptrOther.get();
				event._MyObject = this;
				if (this->_CallbackOnCollision != nullptr)
				{
					this->_CallbackOnCollision(event);
				}

				if (ptrOther->_CallbackOnCollision != nullptr)
				{
					event._OtherObject = this;
					event._MyObject = ptrOther.get();
					ptrOther->_CallbackOnCollision(event);
				}
			}
			return areColliding;
		}
	}
	return false;
}


void LE::GameObject2D::DrawDebug()
{
	DrawRectangleLinesEx(GetCollisionAtPosition(), 5.f, WHITE);
}

LE::GameObjectSingleImage::GameObjectSingleImage(const std::string& InImageFileName, const std::string& InName)
	:_FilePathToLoad(InImageFileName)
	, GameObject2D(InName)
{
	if (InImageFileName.empty())
	{
		LOG("GameObjectSingleImage nomme " + _Name + " a un nom de fichier image vide à charger.", TLevel::eERROR);
	}

	if (!FileExists(InImageFileName.c_str()))
	{
		LOG("GameObjectSingleImage nomme " + _Name + " a un nom vers un fichier qui n'existe pas.", TLevel::eWARNING);
	}
}

LE::GameObjectSingleImage::~GameObjectSingleImage()
{
	if (_IsLoaded)
	{
		Unload();
	}
}


void LE::GameObjectSingleImage::SetScale(float InScale)
{
	_Scale = InScale;
}

float LE::GameObjectSingleImage::GetScale() const
{
	return _Scale;
}

void LE::GameObjectSingleImage::SetRotation(float InRotationInDegree)
{
	_Rotation = InRotationInDegree;
}

float LE::GameObjectSingleImage::GetRotation() const
{
	return _Rotation;
}

void LE::GameObjectSingleImage::SetColorTint(const Color& InColorTint)
{
	_Tint = InColorTint;
}

const Color& LE::GameObjectSingleImage::GetColorTint() const
{
	return _Tint;
}

const Rectangle& LE::GameObjectSingleImage::GetCollisionAtPosition() const
{
	Rectangle ret = _CollisionBox;
	Vector2 pivot = { _CollisionBox.width * 0.5f, _CollisionBox.height * 0.5f };
	ret.x -= pivot.x;
	ret.y -= pivot.y;
	return ret;
}

void LE::GameObjectSingleImage::Load()
{
	if (!FileExists(_FilePathToLoad.c_str()))
	{
		LOG("GameObjectSingleImage nomme " + _Name + " a un nom vers un fichier qui n'existe pas.", TLevel::eWARNING);
		return;
	}
	if (_IsLoaded)
	{
		LOG("GameObjectSingleImage nomme " + _Name + " est deja charge.", TLevel::eWARNING);
		return;
	}
	_Image = LoadImage(_FilePathToLoad.c_str());
	_Texture = LoadTextureFromImage(_Image);
	_IsLoaded = true;
}

void LE::GameObjectSingleImage::Unload()
{
	if (_IsLoaded)
	{
		UnloadImage(_Image);
		_IsLoaded = false;
	}
	else
	{
		LOG("GameObjectSingleImage nomme " + _Name + " n'est pas charge et ne peut etre dechargee.", TLevel::eWARNING);
	}
}

const Image& LE::GameObjectSingleImage::GetImage() const
{
	return _Image;
}

const Texture& LE::GameObjectSingleImage::GetTexture() const
{
	return _Texture;
}

void LE::GameObjectSingleImage::Draw2D()
{
	Rectangle source = { 0, 0, (float)_Texture.width, (float)_Texture.height };
	Rectangle dest = { GetPosition().x, GetPosition().y, _CollisionBox.width * _Scale, _CollisionBox.height * _Scale };
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

void LE::GameObject2D::Destroy()
{
	//!!!!!Important!!!!!! Si jamais on appel destroy sur un objet invalide!
	//Les méthodes sont appelés quand même sur les objets détruits. Ça crash juste si on accède à un membre...
	if (shared_from_this() != nullptr)
	{
		service_locator.getService<LE::IEngineService>()->SendLateUpdateCommand([self = shared_from_this()](LE::Engine& InEngine)
			{
				if (auto scene = InEngine.GetCurrentActiveScene().lock())
				{
					scene->RemoveGameObject2D(self);
				}
			});
	}
}

LE::GameObjectTile::GameObjectTile(const std::string& InImageFileName, const Rectangle& InSceneRectangle)
	:GameObjectSingleImage(InImageFileName, "GameObjectTile")
{
	_CollisionBox = InSceneRectangle;
}

void LE::GameObjectTile::Draw2D()
{
	Rectangle source = { 0, 0, (float)_CollisionBox.width, (float)_CollisionBox.height };
	Rectangle dest = { GetPosition().x, GetPosition().y, _CollisionBox.width * _Scale, _CollisionBox.height * _Scale };
	Vector2 pivot = { _CollisionBox.width * 0.5f * _Scale, _CollisionBox.height * 0.5f * _Scale };

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
