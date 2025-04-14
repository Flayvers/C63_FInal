#pragma once

#include "raylib.h"
#include <string>
#include <map>
#include "LoopEngine/ServiceLocator.h"
#include "LoopEngine/BaseObject.h"

namespace LE
{
    class IRessourceManager : public IService, public IBaseObject
    {
        public:
             virtual Texture& Load(std::string& InPath) = 0;
             virtual void UnloadAll() = 0;
    };

    class RessourceManager : public ServiceBase<IRessourceManager>
    {
        public:
            RessourceManager() {}
            virtual ~RessourceManager() {}

            Texture& Load(std::string& InPath) override;
            void UnloadAll() override;

        private:
            std::map<std::string, Texture2D> _mapLoadedTexture;
    };
};

