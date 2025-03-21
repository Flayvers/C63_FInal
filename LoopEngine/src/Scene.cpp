#include "Scene.h"
#include "Logger.h"

namespace LE
{
    Scene::Scene(const std::string& InName)
        : _Name(InName), _IsLoaded(false)
    {
        if (_Name.empty())
        {
            LOG("Nom de sc�ne vide.", eERROR);
        }
    }

    Scene::~Scene()
    {
        Unload();
    }

    const std::string& Scene::GetName() const
    {
        return _Name;
    }

    void Scene::AddGameObject2D(std::shared_ptr<GameObject2D> InNewGameObject)
    {
        if (HasGameObject2D(InNewGameObject))
        {
            LOG("Objet nomm� " + InNewGameObject->GetName() + " d�j� dans la sc�ne, l'objet n'est pas ajout�.", eWARNING);
            return;
        }

        _GameObjects.push_back(InNewGameObject);

        if (_IsLoaded)
        {
            LOG("Loading " + InNewGameObject->GetName(), eDEBUG)
            InNewGameObject->Load();
        }
    }

    void Scene::RemoveGameObject2D(std::shared_ptr<GameObject2D> InRemovedGameObject)
    {
        auto it = std::find(_GameObjects.begin(), _GameObjects.end(), InRemovedGameObject);
        if (it == _GameObjects.end())
        {
            LOG("Objet nomm� " + InRemovedGameObject->GetName() + " n'est pas dans la sc�ne, l'objet n'est pas enlev�.", eWARNING);
            return;
        }

        if (_IsLoaded)
        {
            (*it)->Unload();
        }

        _GameObjects.erase(it);
    }

    bool Scene::HasGameObject2D(std::shared_ptr<GameObject2D> InGameObject)
    {
        return std::find(_GameObjects.begin(), _GameObjects.end(), InGameObject) != _GameObjects.end();
    }

    void Scene::Load()
    {
        if (_IsLoaded)
        {
            LOG("Sc�ne d�j� load�e, la sc�ne ne reloadera pas.", eWARNING);
            return;
        }

        for (const auto& obj : _GameObjects)
        {
            
            obj->Load();
        }

        _IsLoaded = true;
    }

    void Scene::Unload()
    {
        if (!_IsLoaded)
        {
            LOG("Sc�ne n'est pas load�e, la sc�ne ne d�loadera pas.", eWARNING);
            return;
        }

        for (const auto& obj : _GameObjects)
        {
            obj->Unload();
        }

        _IsLoaded = false;
    }

    void Scene::PreUpdate()
    {
        for (const auto& obj : _GameObjects)
        {
            obj->PreUpdate();
        }
    }

    void Scene::Draw3D()
    {
        for (const auto& obj : _GameObjects)
        {
            obj->Draw3D();
        }
    }

    void Scene::Draw2D()
    {
        for (const auto& obj : _GameObjects)
        {
            obj->Draw2D();
        }
    }

    void Scene::CheckAndNotifyCollision()
    {
        for (size_t i = 0; i < _GameObjects.size(); ++i)
        {
            for (size_t j = i + 1; j < _GameObjects.size(); ++j)
            {
                _GameObjects[i]->CheckCollision(_GameObjects[j], true);
            }
        }
    }

    void Scene::LateUpdate()
    {
        for (const auto& obj : _GameObjects)
        {
            obj->LateUpdate();
        }
    }
}
