#ifndef CONTENT_H
#define CONTENT_H

#include <string>
#include <unordered_map>
#include <vector>
#include "files.h"
#include "../utilities/logger.h"

namespace SealEngineContentManager
{
    enum class AssetTypes
    {
        TEXTURE,
        SOUND
    };

    class SealEngineContentManager
    {
    public:
        SealEngineContentManager(const std::string &name);
        ~SealEngineContentManager();
        void RegisterAsset(const std::string &path, const std::string &name, const AssetTypes type);
        SealFileManager::File *GetAsset(const std::string &name, const AssetTypes type);
        void UnregisterAsset(const std::string &name, const AssetTypes type);

    private:
        std::unordered_map<std::string, SealFileManager::File *> textureAssets;
        std::unordered_map<std::string, SealFileManager::File *> soundAssets;
        SealLogger::Logger *logger;
    };

} // namespace SealEngineContentManager

#endif // CONTENT_H
