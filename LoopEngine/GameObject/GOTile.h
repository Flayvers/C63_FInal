#pragma once
#include <functional>
#include <memory>
#include <string>
#include "raylib.h"
#include "LoopEngine/GameObject/GOSimpleTexture.h"

namespace LE
{
	class GameObjectTile : public GOSimpleTexture
	{
		protected:
			float _TextureScale = 1.0f;

		public:
			GameObjectTile(const std::string& InImageFileName, const Rectangle& InSceneRectangle);
			virtual void Draw2D() override;
	};
}

