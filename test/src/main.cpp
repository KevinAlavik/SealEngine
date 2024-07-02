#include <Seal/Seal.h>
#include <Seal/Draw.h>
#include <Seal/Types.h>

// Handlers
SealEngine::Logger logger("TestGame");
SealEngine::Window window("Test Game", 800, 600);
SealEngineDraw::Drawer drawer(&window, new SealEngine::Logger("GameDrawer"));
SealEngineContentManager::SealEngineContentManager contentManager("GameContentManager");

// Textures
SealEngineDraw::Texture *mario;
SealEngineDraw::Texture *no_texture;

// Window width and height
int w = window.GetWindowWidth();
int h = window.GetWindowHeight();

// Config
int playerWidth = 32;
int playerHeight = 32;

void LoadAssets()
{
    // Register textures into the content manager
    contentManager.RegisterAsset("assets/textures/no_texture.png", "no_texture", SealEngineContentManager::AssetTypes::TEXTURE);
    contentManager.RegisterAsset("assets/textures/mario.png", "mario", SealEngineContentManager::AssetTypes::TEXTURE);

    // Load the textures
    mario = contentManager.GetAsset<SealEngineDraw::Texture>("mario");
    no_texture = contentManager.GetAsset<SealEngineDraw::Texture>("no_texture");
}

void Setup()
{
    window.Clear(SealEngineTypes::Color(255));
    LoadAssets();
}

void Update()
{
    window.Clear(SealEngineTypes::Color(255));
    mario->Draw(&drawer, 0, 0, &playerWidth, &playerHeight);
}

void Cleanup()
{
    window.~Window();
    drawer.~Drawer();
    logger.~Logger();
    contentManager.~SealEngineContentManager();
}

int main()
{
    window.Spawn(Setup, Update);
    logger.Log(SealEngine::Logger::LogLevel::OK, "Finished running TestGame.");
    Cleanup();
    return 0;
}
