#include <backends/content.h>
#include <stdexcept>

namespace SealEngineContentManager
{
    SealEngineContentManager::SealEngineContentManager(const std::string &name)
        : logger(new SealLogger::Logger(name))
    {
    }

    SealEngineContentManager::~SealEngineContentManager()
    {
        for (auto &pair : textureAssets)
        {
            delete pair.second;
        }
        textureAssets.clear();

        for (auto &pair : soundAssets)
        {
            delete pair.second;
        }
        soundAssets.clear();

        delete logger;
    }

    void SealEngineContentManager::RegisterAsset(const std::string &path, const std::string &name, const AssetTypes type)
    {
        if (type == AssetTypes::TEXTURE)
        {
            textureAssets[name] = new SealFileManager::File(path);
        }
        else if (type == AssetTypes::SOUND)
        {
            soundAssets[name] = new SealFileManager::File(path);
        }

        if (logger)
        {
            logger->info("Asset registered: " + name);
        }
    }

    void SealEngineContentManager::UnregisterAsset(const std::string &name, const AssetTypes type)
    {
        if (type == AssetTypes::TEXTURE)
        {
            auto it = textureAssets.find(name);
            if (it != textureAssets.end())
            {
                delete it->second;
                textureAssets.erase(it);
            }
        }
        else if (type == AssetTypes::SOUND)
        {
            auto it = soundAssets.find(name);
            if (it != soundAssets.end())
            {
                delete it->second;
                soundAssets.erase(it);
            }
        }

        if (logger)
        {
            logger->info("Asset unregistered: " + name);
        }
    }

    SealFileManager::File *SealEngineContentManager::GetAsset(const std::string &name, const AssetTypes type)
    {
        if (type == AssetTypes::TEXTURE)
        {
            auto it = textureAssets.find(name);
            if (it != textureAssets.end())
            {
                return it->second;
            }
        }
        else if (type == AssetTypes::SOUND)
        {
            auto it = soundAssets.find(name);
            if (it != soundAssets.end())
            {
                return it->second;
            }
        }

        throw std::runtime_error("Asset not found: " + name);
    }
} // namespace SealEngineContentManager
