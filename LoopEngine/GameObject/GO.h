#pragma once
#include <functional>
#include <memory>
#include <string>
#include "raylib.h"
#include "LoopEngine/BaseObject.h"

namespace LE
{
	class Visitor;
	class GameObject;
	struct CollisionEvent
	{
		CollisionEvent() {};
		Vector2 _Position{0.f,0.f};
		GameObject const * _MyObject = nullptr;
		GameObject const * _OtherObject = nullptr;
	};

	class GameObject : public IBaseObject, public std::enable_shared_from_this<GameObject>
	{
	protected:
		Rectangle _CollisionBox = Rectangle{0.f,0.f,100.f,100.f};
		Vector2 _ParentPosition{ 0.f,0.f };
		int _CollisionMask = 0;
		int _CollisionGroup = 0;
		std::string _Name = "Nameless";
		std::function<void(const CollisionEvent&)> _CallbackOnCollision = nullptr;

		bool _IsActive = true;
		bool _IsLoaded = false;

	public:
		GameObject(const std::string& InName = "GameObject");
		GameObject(Vector2 InPosition, Vector2 InCollisionBox, int InCollisionMask, const std::string& InName = "GameObject");
		virtual ~GameObject();

		void SetCollisionMask(int InCollisionMask);
		int GetCollisionMask() const;

		void SetCollisionGroup(int InCollisionGroup);
		int GetCollisionGroup() const;

		void SetActive(bool InIsActive);
		bool IsActive() const;
		void SetLoaded(bool InIsLoaded);
		bool IsLoaded() const;

		virtual void SetPosition(Vector2 InPosition);
		virtual void SetParentPosition(Vector2 InParentPosition);

		Vector2 GetPosition() const;
		Vector2 GetParentPosition() const;
		Vector2 GetWorldPosition() const;

		void SetName(const std::string& InName);
		std::string GetName() const;

		void  SetCollisionBox(const Vector2& InNewBoxSize);
		Vector2 GetCollisionBox() const;
		virtual Rectangle GetCollisionAtPosition() const;
		Rectangle GetCollisionAtWorldPosition() const;

		virtual void OnCollisionEvent(std::function<void(const CollisionEvent&)> InFunctionToCall);
		virtual bool CheckCollision(const std::weak_ptr<GameObject> InOtherGO, bool InNotify = false);

		virtual void Load() { _IsLoaded = true; }
		virtual void Unload() { _IsLoaded = false; }

		virtual void PreUpdate() {}
		virtual void Draw3D() {}
		virtual void Draw2D() {}
		virtual void DrawDebug();
		virtual void LateUpdate() {}

		virtual void AcceptVisitor(Visitor& InVisitor);
		virtual void Destroy();
	};
}

