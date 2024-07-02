#ifndef CONTENT_H
#define CONTENT_H

#include <string>
#include <unordered_map>
#include <vector>
#include "files.h"
#include "../utilities/logger.h"

namespace SealEngineDraw
{
    class Texture;
}

namespace SealEngineContentManager
{
    enum class AssetTypes
    {
        TEXTURE
    };

    class SealEngineContentManager
    {
    public:
        SealEngineContentManager(const std::string &name);
        ~SealEngineContentManager();
        void RegisterAsset(const std::string &path, const std::string &name, const AssetTypes type);
        void UnregisterAsset(const std::string &name, const AssetTypes type);

        template <typename T>
        T *GetAsset(const std::string &name);

        template <typename T>
        std::vector<std::string> GetAssetNamesOfType();

    private:
        std::unordered_map<std::string, SealEngineDraw::Texture *> textureAssets;
        SealLogger::Logger *logger;
    };

    template <>
    SealEngineDraw::Texture *SealEngineContentManager::GetAsset<SealEngineDraw::Texture>(const std::string &name);

} // namespace SealEngineContentManager

#endif // CONTENT_H
