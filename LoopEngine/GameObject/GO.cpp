#include "LoopEngine/Global.h"
#include "LoopEngine/Visitor.h"
#include "LoopEngine/GameObject/GO.h"

LE::GameObject::GameObject(const std::string& InName)
	:_Name(InName)
{
	if (_Name.empty())
	{
		LOG("Un GameObject a un nom vide!",TLevel::eWARNING);
	}
}

LE::GameObject::GameObject(Vector2 InPosition, Vector2 InCollisionBox, int InCollisionMask, const std::string& InName)
	:_Name(InName)
	,_CollisionBox{ InPosition .x,InPosition .y,InCollisionBox .x,InCollisionBox.y}
	,_CollisionMask(InCollisionMask)
{
	if (_CollisionBox.width < 0.f || _CollisionBox.height < 0.f)
	{
		LOG("GameObject nomme " + _Name + " a une boite de collision invalide (valeur negative). Collision desactivee ",TLevel::eWARNING);
		InCollisionMask = 0;
	}

	if (_Name.empty())
	{
		LOG("Un GameObject a un nom vide!", TLevel::eWARNING);
	}
}

LE::GameObject::~GameObject()
{
}

void LE::GameObject::SetCollisionMask(int InCollisionGroup)
{
	_CollisionMask = InCollisionGroup;
}

int LE::GameObject::GetCollisionMask() const
{
	return _CollisionMask;
}

void LE::GameObject::SetCollisionGroup(int InCollisionGroup)
{
	_CollisionGroup = InCollisionGroup;
}

int LE::GameObject::GetCollisionGroup() const
{
	return _CollisionGroup;
}

void LE::GameObject::SetActive(bool InIsActive)
{
	_IsActive = InIsActive;
}

bool LE::GameObject::IsActive() const
{
	return _IsActive;
}

void LE::GameObject::SetLoaded(bool InIsLoaded)
{
	_IsLoaded = InIsLoaded;
}

bool LE::GameObject::IsLoaded() const
{
	return _IsLoaded;
}

void LE::GameObject::SetPosition(Vector2 InPosition)
{
	_CollisionBox.x = InPosition.x;
	_CollisionBox.y = InPosition.y;
}

void LE::GameObject::SetParentPosition(Vector2 InParentPosition)
{
	_ParentPosition = InParentPosition;
}

Vector2 LE::GameObject::GetPosition() const
{
	return { _CollisionBox.x ,_CollisionBox.y };
}

Vector2 LE::GameObject::GetParentPosition() const
{
	return _ParentPosition;
}

Vector2 LE::GameObject::GetWorldPosition() const
{
	return { GetPosition().x + _ParentPosition.x, GetPosition().y + _ParentPosition.y };
}

void LE::GameObject::SetName(const std::string& InName)
{
	_Name = InName;
}

std::string LE::GameObject::GetName() const
{
	return _Name;
}

void LE::GameObject::SetCollisionBox(const Vector2& InNewBoxSize)
{
	if (InNewBoxSize.x < 0.f || InNewBoxSize.y < 0.f)
	{
		LOG("GameObject nomme " + _Name + " a une boite de collision invalide (valeur negative). La boite de collision ne sera pas modifiee.", TLevel::eWARNING);
	}
	else
	{
		_CollisionBox.width = InNewBoxSize.x;
		_CollisionBox.height = InNewBoxSize.y;
	}
}

Vector2 LE::GameObject::GetCollisionBox() const
{
	return {_CollisionBox.width,_CollisionBox.height};
}

Rectangle LE::GameObject::GetCollisionAtPosition() const
{
	return _CollisionBox;
}

Rectangle LE::GameObject::GetCollisionAtWorldPosition() const
{
	Rectangle worldRectangle = GetCollisionAtPosition();
	worldRectangle.x += _ParentPosition.x;
	worldRectangle.y += _ParentPosition.y;
	return worldRectangle;
}

void LE::GameObject::OnCollisionEvent(std::function<void(const CollisionEvent&)> InFunctionToCall)
{
	_CallbackOnCollision = InFunctionToCall;
}

bool LE::GameObject::CheckCollision(const std::weak_ptr<GameObject> InOtherGO, bool InNotify)
{
	if (auto ptrOther = InOtherGO.lock())
	{
		if (ptrOther->IsActive() && IsActive() && (GetCollisionMask() & ptrOther->GetCollisionGroup()) != 0)
		{
			bool areColliding =  CheckCollisionRecs(GetCollisionAtWorldPosition(), ptrOther->GetCollisionAtWorldPosition());
			if (InNotify && areColliding)
			{
				CollisionEvent event;
				event._Position.x = (GetWorldPosition().x + ptrOther->GetWorldPosition().x) * 0.5f;
				event._Position.y = (GetWorldPosition().y + ptrOther->GetWorldPosition().y) * 0.5f;
				event._OtherObject = ptrOther.get();
				event._MyObject = this;
				if (this->_CallbackOnCollision != nullptr)
				{
					this->_CallbackOnCollision(event);
				}
			}
			return areColliding;
		}
	}
	return false;
}

void LE::GameObject::DrawDebug()
{
	Color lineColor = IsActive() ? GRAY : RED;
	DrawCircleLines((int)GetWorldPosition().x, (int)GetWorldPosition().y, 10.f, lineColor);
	DrawText(GetName().c_str(), (int)GetWorldPosition().x+30, (int)GetWorldPosition().y-14, 28, lineColor);
}

void LE::GameObject::AcceptVisitor(Visitor& InVisitor)
{
	if (shared_from_this() != nullptr)
	{
		InVisitor.Visit(shared_from_this());
	}
}

void LE::GameObject::Destroy()
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