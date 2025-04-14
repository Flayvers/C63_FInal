#pragma once
#include <functional>
#include <memory>
#include <string>
#include "raylib.h"
#include "LoopEngine/BaseObject.h"
#include "LoopEngine/GameObject/GOComposite.h"

namespace LE
{
	class GOSimpleTexture : public GOComposite
	{
		protected:
			Texture _Texture{0,0,0,0,0};
			Color _Tint = WHITE;
			float _Rotation = 0.0f;
			float _Scale = 1.0f;
			std::string _FilePathToLoad;

		public:
			GOSimpleTexture(const std::string& InImageFileName,const std::string& InName = "GOSimpleTexture");
			virtual ~GOSimpleTexture();

			void SetScale(float InScale);
			float GetScale() const;

			void SetRotation(float InRotationInDegree);
			float GetRotation() const;

			void SetColorTint(const Color& InColorTint);
			const Color& GetColorTint() const;

			virtual Rectangle GetCollisionAtPosition() const;

			virtual void Load();
			virtual void Unload();

			Texture GetTexture() const;
			virtual void Draw2D() override;
			virtual void DrawDebug() override;
	};
}

