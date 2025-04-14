#include <vector>

#include "LoopEngine/GameObject/GOComposite.h"
#include "LoopEngine/Logger.h"
#include "LoopEngine/Global.h"
#include "Visitor.h"

void LE::Visitor::Visit(std::shared_ptr<GOComposite> InNode)
{
	if (InNode)
	{
		for (auto& go : InNode->GetComponents())
		{
			if (go != nullptr)
			{
				go->AcceptVisitor(*this);
			}
		}
	}
}

void LE::Collector::Visit(std::shared_ptr<GameObject> InNode)
{
	if (InNode)
	{
		_Collection.push_back(InNode);
	}
}
void LE::Collector::Visit(std::shared_ptr<GOComposite> InNode)
{
	if (InNode)
	{
		_Collection.push_back(InNode);
		Visitor::Visit(InNode);
	}
}

std::vector<std::shared_ptr<LE::GameObject>> LE::Collector::GetCollection() const
{
	return _Collection;
}

void LE::ParentPositionUpdate::Visit(std::shared_ptr<GameObject> InNode)
{
	return;
}

void LE::ParentPositionUpdate::Visit(std::shared_ptr<GOComposite> InNode)
{
	if (InNode)
	{
		for (auto& go : InNode->GetComponents())
		{
			if (go != nullptr)
			{
				go->SetParentPosition(InNode->GetWorldPosition());
				go->AcceptVisitor(*this);
			}
		}
	}
}