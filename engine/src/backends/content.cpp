#include <backends/content.h>
#include <pub/Seal/Draw.h>
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

        if (logger != nullptr)
        {
            delete logger;
            logger = nullptr;
        }
    }

    void SealEngineContentManager::RegisterAsset(const std::string &path, const std::string &name, const AssetTypes type)
    {
        if (type == AssetTypes::TEXTURE)
        {
            textureAssets[name] = new SealEngineDraw::Texture(path);
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

        if (logger)
        {
            logger->info("Asset unregistered: " + name);
        }
    }

    template <>
    SealEngineDraw::Texture *SealEngineContentManager::GetAsset<SealEngineDraw::Texture>(const std::string &name)
    {
        auto it = textureAssets.find(name);
        if (it != textureAssets.end())
        {
            return it->second;
        }

        auto defaultTextureIt = textureAssets.find("no_texture");
        if (defaultTextureIt != textureAssets.end())
        {
            return defaultTextureIt->second;
        }

        throw std::runtime_error("Texture \"" + name + "\" not found! We didnt even find \"no_texture\" texture so something is wrong!");
    }

} // namespace SealEngineContentManager
