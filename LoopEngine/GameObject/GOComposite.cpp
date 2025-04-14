#include "LoopEngine/GameObject/GOComposite.h"
#include "LoopEngine/Logger.h"
#include "LoopEngine/Global.h"
#include "LoopEngine/Visitor.h"


LE::GOComposite::GOComposite(const std::string InName)
	:GameObject(InName)
{
}

void LE::GOComposite::AddGameObject2D(std::shared_ptr<LE::GameObject> InNewGameObject)
{
	if (!HasGameObject2D(InNewGameObject))
	{
		_Components.push_back(InNewGameObject);
		if (GetIEngine().GetCurrentActiveSceneName() == GetName())
		{
			InNewGameObject->Load();
			InNewGameObject->SetLoaded(true);
		}
	}
	else
	{
		LOG("Object named " + InNewGameObject->GetName() + " could not be added to Scene named " + GetName() + " since it already exists.", TLevel::eWARNING);
	}
}

void LE::GOComposite::RemoveGameObject2D(std::shared_ptr<GameObject> InRemovedGameObject)
{
	auto item = std::find(_Components.begin(), _Components.end(), InRemovedGameObject);
	if (item != _Components.end())
	{
		if (GetIEngine().GetCurrentActiveSceneName() == GetName())
		{
			InRemovedGameObject->Unload();
			InRemovedGameObject->SetLoaded(false);
		}
		_Components.erase(item);
	}
	else
	{
		LOG("Object named " + InRemovedGameObject->GetName() + " could not be removed from Scene named " + GetName(), TLevel::eWARNING);
	}
}

bool LE::GOComposite::HasGameObject2D(std::shared_ptr<GameObject> InGameObject)
{
	return  std::find(_Components.begin(), _Components.end(), InGameObject) != _Components.end();
}

std::vector<std::shared_ptr<LE::GameObject>> LE::GOComposite::GetComponents()
{
	return _Components;
}

void LE::GOComposite::Load()
{
	for (auto& go : _Components)
	{
		if (go != nullptr && not go->IsLoaded())
		{
			go->Load();
			go->SetLoaded(true);
		}
	}
}

void LE::GOComposite::Unload()
{
	for (auto& go : _Components)
	{
		if (go != nullptr && go->IsLoaded())
		{
			go->Unload();
			go->SetLoaded(false);
		}
	}
}

void LE::GOComposite::PreUpdate()
{
	for (auto& go : _Components)
	{
		if (go != nullptr && go->IsActive() && go->IsLoaded())
		{
			go->PreUpdate();
		}
	}
}

void LE::GOComposite::Draw3D()
{
	for (auto& go : _Components)
	{
		if (go != nullptr && go->IsActive() && go->IsLoaded())
		{
			go->Draw3D();
		}
	}
}

void LE::GOComposite::Draw2D()
{
	for (auto& go : _Components)
	{
		if (go != nullptr && go->IsActive() && go->IsLoaded())
		{
			go->Draw2D();
		}
	}
}

void LE::GOComposite::DrawDebug()
{
	GameObject::DrawDebug();
	for (auto& go : _Components)
	{
		if (go != nullptr && go->IsActive() && go->IsLoaded())
		{
			Color lineColor = IsActive() ? PINK : RED;
			lineColor.a = 100;
			DrawLineEx(GetWorldPosition(), go->GetWorldPosition(),2.f,lineColor);
			go->DrawDebug();
		}
	}
}

void LE::GOComposite::LateUpdate()
{
	for (auto& go : _Components)
	{
		if (go != nullptr && go->IsActive() && go->IsLoaded())
		{
			go->LateUpdate();
		}
	}
}

void LE::GOComposite::AcceptVisitor(Visitor& InVisitor)
{
	if (shared_from_this() != nullptr)
	{
		InVisitor.Visit(std::dynamic_pointer_cast<GOComposite>(shared_from_this()));
	}
}

bool LE::GOComposite::CheckCollision(const std::weak_ptr<GameObject> InOtherGO, bool InNotify)
{
	bool hasCollision = GameObject::CheckCollision(InOtherGO, InNotify);
	if (auto go = InOtherGO.lock())
	{
		for (int i = 0; i < _Components.size(); ++i)
		{
			hasCollision |= _Components[i]->CheckCollision(go, true);
		}
	}
	return hasCollision;
}
