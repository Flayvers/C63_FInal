#include "Scene.h"
#include "Logger.h"

LE::Scene::Scene(const std::string& InName)
	:_Name(InName)
{
}

LE::Scene::~Scene()
{
	_GO2D.clear();
}

void LE::Scene::AddGameObject2D(std::shared_ptr<GameObject2D> InNewGameObject)
{
	if (!HasGameObject2D(InNewGameObject))
	{
		_GO2D.push_back(InNewGameObject);
	}
	else
	{
		LOG("Object named " + InNewGameObject->GetName() + " could not be added to Scene named " + GetName() + " since it already exists.", TLevel::eWARNING);
	}
}

void LE::Scene::RemoveGameObject2D(std::shared_ptr<GameObject2D> InRemovedGameObject)
{
	auto item = std::find(_GO2D.begin(), _GO2D.end(), InRemovedGameObject);
	if (item != _GO2D.end())
	{
		_GO2D.erase(item);
	}
	else
	{
		LOG("Object named " + InRemovedGameObject->GetName() + " could not be removed from Scene named " + GetName(), TLevel::eWARNING);
	}
}

bool LE::Scene::HasGameObject2D(std::shared_ptr<GameObject2D> InGameObject)
{
	return  std::find(_GO2D.begin(), _GO2D.end(), InGameObject) != _GO2D.end();
}

void LE::Scene::Load()
{
	for (auto& go : _GO2D)
	{
		if (go != nullptr)
		{
			go->Load();
		}
	}
}

void LE::Scene::Unload()
{

	for (auto& go : _GO2D)
	{
		if (go != nullptr)
		{
			go->Unload();
		}
	}
}

void LE::Scene::PreUpdate()
{
	for (auto& go : _GO2D)
	{
		if (go != nullptr)
		{
			go->PreUpdate();
		}
	}
}

void LE::Scene::Draw3D()
{
	for (auto& go : _GO2D)
	{
		if (go != nullptr)
		{
			go->Draw3D();
		}
	}
}

void LE::Scene::Draw2D()
{
	for (auto& go : _GO2D)
	{
		if (go != nullptr)
		{
			go->Draw2D();
		}
	}
}

void LE::Scene::DrawDebug()
{
	for (auto& go : _GO2D)
	{
		if (go != nullptr)
		{
			go->DrawDebug();
		}
	}
}

void LE::Scene::CheckAndNotifyCollision()
{
	for (int i = 0; i < _GO2D.size(); ++i)
	{
		auto go = _GO2D[i];
		for (int j = i + 1; j < _GO2D.size(); ++j)
		{
			go->CheckCollision(_GO2D[j], true);
		}
	}
}

void LE::Scene::LateUpdate()
{
	for (auto& go : _GO2D)
	{
		if (go != nullptr)
		{
			go->LateUpdate();
		}
	}
}

const std::string& LE::Scene::GetName() const { return _Name; }

