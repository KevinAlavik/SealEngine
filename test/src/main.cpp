#include <Seal/Seal.h>
#include <Seal/Draw.h>
#include <Seal/Types.h>

SealEngine::Logger logger("TestGame");
SealEngine::Window window("Test Game", 800, 600);
SealEngineDraw::Drawer drawer(&window, &logger);
SealEngineContentManager::SealEngineContentManager contentManager("GameContentManager");

int w = window.GetWindowWidth();
int h = window.GetWindowHeight();

void Setup()
{
    window.Clear(SealEngineTypes::Color(255));
    contentManager.RegisterAsset("assets/textures/no_texture.png", "no_texture", SealEngineContentManager::AssetTypes::TEXTURE);
    SealEngineDraw::Texture noTexture(contentManager.GetAsset("no_texture", SealEngineContentManager::AssetTypes::TEXTURE)->GetPath(), new SealEngine::Logger("no_texture"));
    noTexture.Draw(&drawer, 0, 0);
    window.GetWindow()->verbose = true;
}

void Update()
{
}

int main()
{
    window.Spawn(Setup, Update);
    logger.Log(SealEngine::Logger::LogLevel::OK, "Finished running TestGame.");
    return 0;
}
