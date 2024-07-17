#include <Seal/Seal.h>
#include <Seal/Draw.h>
#include <Seal/Types.h>

#include <SDL2/SDL.h>
#include <unordered_map>
#include <functional>

// Logger, window, drawer, and content manager setup
SealEngine::Logger logger("TestGame");
SealEngine::Window window("Test Game", 800, 600);
SealEngineDraw::Drawer drawer(&window, new SealEngine::Logger("GameDrawer"));
SealEngineContentManager::SealEngineContentManager contentManager("GameContentManager");

// Hooks / Handlers
SealEngine::Keyboard keyboardManager;
SealEngine::KeyboardEvent *keyboardHook = new SealEngine::KeyboardEvent;

// Textures and Sprites
SealEngine::Sprite *mario;
SealEngineDraw::Texture *missing_texture;

// Window stuff
int w = window.GetWindowWidth();
int h = window.GetWindowHeight();
int verbose = window.GetWindow()->verbose = false;

// Settings
#define STEP_SIZE 10
int playerWidth = 32;
int playerHeight = 32;

// Asset list
std::vector<std::string> textureNames;

// Function to load assets (duh)
void LoadAssets()
{
    contentManager.RegisterAsset("assets/textures/missing_texture.png", "missing_texture", SealEngineContentManager::AssetTypes::TEXTURE);
    contentManager.RegisterAsset("assets/textures/mario.png", "mario", SealEngineContentManager::AssetTypes::TEXTURE);

    mario = new SealEngine::Sprite("mario", SealEngineTypes::Vector2(0, 0), SealEngineTypes::Vector2(playerWidth, playerHeight), &contentManager, &drawer, new SealEngine::Logger("SpriteMario"));
    missing_texture = contentManager.GetAsset<SealEngineDraw::Texture>("missing_texture");
}

int curTexIdx = 0;
void NextTexture()
{
    if (textureNames.empty())
    {
        logger.Log(SealEngine::Logger::LogLevel::ERROR, "No textures to load!");
        window.Quit();
    }

    mario->SetTexture(textureNames[curTexIdx]);
    curTexIdx = (curTexIdx + 1) % textureNames.size();
}

void Setup()
{
    window.AttatchEventHook(keyboardHook);

    LoadAssets();
    textureNames = contentManager.GetAssetNamesOfType<SealEngineDraw::Texture>();

    keyboardManager.RegisterEvent("Right", []()
                                  { mario->Move(mario->GetPosition().Lerp(SealEngineTypes::Vector2::Vector2(mario->GetPosition().X + STEP_SIZE, mario->GetPosition().Y), 0.3)); });

    keyboardManager.RegisterEvent("Left", []()
                                  { mario->Move(mario->GetPosition().Lerp(SealEngineTypes::Vector2(mario->GetPosition().X - STEP_SIZE, mario->GetPosition().Y), 0.3)); });

    keyboardManager.RegisterEvent("Up", []()
                                  { mario->Move(mario->GetPosition().Lerp(SealEngineTypes::Vector2(mario->GetPosition().X, mario->GetPosition().Y - STEP_SIZE), 0.3)); });

    keyboardManager.RegisterEvent("Down", []()
                                  { mario->Move(mario->GetPosition().Lerp(SealEngineTypes::Vector2(mario->GetPosition().X, mario->GetPosition().Y + STEP_SIZE), 0.3)); });

    keyboardManager.RegisterEvent("Space", []()
                                  { NextTexture(); });

    mario->Show();

    logger.Log(SealEngine::Logger::LogLevel::OK, "Finished setting up TestGame.");
    logger.Log(SealEngine::Logger::LogLevel::INFO, "Welcome to TestGame! Use arrows to move and space to cycle to textures.");
}

void Update()
{
    window.Clear(SealEngineTypes::Color(255));
    mario->Update();
}

void Cleanup()
{
    window.~Window();
    drawer.~Drawer();
    logger.~Logger();
    mario->~Sprite();
    contentManager.~SealEngineContentManager();
}

int main()
{
    window.Spawn(Setup, Update);
    logger.Log(SealEngine::Logger::LogLevel::OK, "Finished running TestGame.");
    Cleanup();
    return 0;
}
