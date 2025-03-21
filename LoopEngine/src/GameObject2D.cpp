#include "GameObject.h"
#include "ServiceLocator.h"
#include "Logger.h"
#include "engine.h"

namespace LE
{
    GameObject2D::GameObject2D(const std::string& InName)
        : _Name(InName)
    {
        if (_Name.empty())
        {
            LOG("Un objet a un nom vide!", TLevel::eWARNING);
        }
    }

    GameObject2D::GameObject2D(Vector2 InPosition, Vector2 InCollisionBox, int InCollisionMask, const std::string& InName)
        : _Position(InPosition), _CollisionBox(InCollisionBox), _CollisionMask(InCollisionMask), _Name(InName)
    {
        if (_CollisionBox.x < 0 || _CollisionBox.y < 0)
        {
            LOG("L'objet nomm� : " + _Name + " a une boite de collision invalide(valeur n�gative).Collision d�sactiv�e(collision mask = 0).", TLevel::eWARNING);
            _CollisionMask = 0;
        }

        if (_Name.empty())
        {
            LOG("Un objet a un nom vide!", TLevel::eWARNING);
        }
    }

    GameObject2D::~GameObject2D() {}

    void GameObject2D::SetCollisionMask(int InCollisionGroup)
    {
        _CollisionMask = InCollisionGroup;
    }

    int GameObject2D::GetCollisionMask() const
    {
        return _CollisionMask;
    }

    void GameObject2D::SetPosition(Vector2 InPosition)
    {
        _Position = InPosition;
    }

    const Vector2& GameObject2D::GetPosition() const
    {
        return _Position;
    }

    void GameObject2D::SetName(const std::string& InName)
    {
        if (InName.empty())
        {
            LOG("Un objet a un nom vide!", TLevel::eWARNING);
        }
        _Name = InName;
    }

    const std::string& GameObject2D::GetName() const
    {
        return _Name;
    }

    void GameObject2D::SetCollisionBox(const Vector2& InNewBoxSize)
    {
        if (InNewBoxSize.x < 0 || InNewBoxSize.y < 0)
        {
            LOG("L'objet nomm� : " + _Name + " a une boite de collision invalide(valeur n�gative) La boite de collision n'est pas modifi�e.", TLevel::eWARNING);
            return;
        }
        _CollisionBox = InNewBoxSize;
    }

    const Vector2& GameObject2D::GetCollisionBox() const
    {
        return _CollisionBox;
    }

    const Rectangle& GameObject2D::GetCollisionAtPosition() const
    {
        Rectangle collisionRect = { _Position.x - (_CollisionBox.x / 2), _Position.y - (_CollisionBox.y / 2), _CollisionBox.x, _CollisionBox.y };
        return collisionRect;
    }

    void GameObject2D::OnCollisionEvent(std::function<void(const CollisionEvent&)> InFunctionToCall)
    {
        _OnCollisionCallback = InFunctionToCall;
    }

    bool GameObject2D::CheckCollision(const std::weak_ptr<GameObject2D> InOtherGO, bool InNotify)
    {
        
        if (auto other = InOtherGO.lock())
        {
            // & ?? == ?? != ??
            if ((_CollisionMask & other->GetCollisionMask()) != 0)
            {
                Rectangle thisRect = GetCollisionAtPosition();
                Rectangle otherRect = other->GetCollisionAtPosition();

                if (CheckCollisionRecs(thisRect, otherRect))
                {
                    if (InNotify)
                    {
                        if (_OnCollisionCallback)
                        {
                            CollisionEvent collisionEvent;
                            collisionEvent._OtherObject = other.get();
                            _OnCollisionCallback(collisionEvent);
                        }

                        if (other->_OnCollisionCallback)
                        {
                            CollisionEvent collisionEvent;
                            collisionEvent._OtherObject = this;
                            other->_OnCollisionCallback(collisionEvent);
                        }
                    }
                    return true;
                }
            }
        }
        return false;
    }

    void GameObject2D::Destroy()
    {
        //!!!!!Important!!!!!! Si jamais on appel destroy sur un objet invalide!
        //Les m�thodes sont appel�s quand m�me sur les objets d�truits. �a crash juste si on acc�de � un membre...
        if (shared_from_this() != nullptr)
        {
            service_locator.getService<IEngineService>()->SendLateUpdateCommand([self = shared_from_this()](Engine& InEngine) {
                if (auto scene = InEngine.GetCurrentActiveScene().lock())
                {
                    scene->RemoveGameObject2D(self);
                }
                });
        }
    }


}
