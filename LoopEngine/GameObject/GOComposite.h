#pragma once

#include <vector>
#include <memory>

#include "LoopEngine/BaseObject.h"
#include "LoopEngine/GameObject/GO.h"

namespace LE
{
	class GameObject;
	class GOComposite : public GameObject
	{
		private:
			std::vector<std::shared_ptr<GameObject>> _Components;

		public:
			GOComposite(const std::string InName);

			template<typename T, typename... Args>
			std::shared_ptr<T> AddNew(Args&&... args)
			{
				auto newGo = std::make_shared<T>(std::forward<Args>(args)...);
				AddGameObject2D(newGo);
				return newGo;
			}

			void AddGameObject2D(std::shared_ptr<GameObject> InNewGameObject);
			void RemoveGameObject2D(std::shared_ptr<GameObject> InRemovedGameObject);
			bool HasGameObject2D(std::shared_ptr<GameObject> InGameObject);

			std::vector<std::shared_ptr<GameObject>> GetComponents();

			virtual void Load() override;
			virtual void Unload() override;

			virtual void PreUpdate() override;
			virtual void Draw3D() override;
			virtual void Draw2D() override;
			virtual void DrawDebug() override;
			virtual void LateUpdate() override;

			virtual void AcceptVisitor(Visitor& InVisitor) override;

			virtual bool CheckCollision(const std::weak_ptr<GameObject> InOtherGO, bool InNotify = false) override;
	};
}