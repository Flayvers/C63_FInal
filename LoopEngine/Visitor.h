#pragma once
#include <vector>
#include <memory>

#include "LoopEngine/BaseObject.h"
#include "LoopEngine/GameObject/GO.h"
#include "LoopEngine/GameObject/GOComposite.h"

namespace LE
{
	class Visitor : public IBaseObject
	{
		public:
			virtual ~Visitor() = default;
			virtual void Visit(std::shared_ptr<GameObject> InNode) = 0;
			virtual void Visit(std::shared_ptr<GOComposite> InNode);
	};

	class Collector : public Visitor
	{
		private:
			std::vector<std::shared_ptr<LE::GameObject>> _Collection;
		public:
			virtual void Visit(std::shared_ptr<GameObject> InNode);
			virtual void Visit(std::shared_ptr<GOComposite> InNode);

			std::vector<std::shared_ptr<LE::GameObject>> GetCollection() const;
	};

	class ParentPositionUpdate : public Visitor
	{
		public:
			virtual void Visit(std::shared_ptr<GameObject> InNode);
			virtual void Visit(std::shared_ptr<GOComposite> InNode);
	};
}