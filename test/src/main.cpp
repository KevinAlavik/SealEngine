#include <Seal/Seal.h>
#include <Seal/Draw.h>
#include <Seal/Types.h>

#include <SDL2/SDL.h>
#include <unordered_map>
#include <functional>

// Function prototypes
void PrintKeyInfo(SDL_Event *event);
void PrintModifiers(Uint16 mod);

// Logger, window, drawer, and content manager setup
SealEngine::Logger logger("TestGame");
SealEngine::Window window("Test Game", 800, 600);
SealEngineDraw::Drawer drawer(&window, new SealEngine::Logger("GameDrawer"));
SealEngineContentManager::SealEngineContentManager contentManager("GameContentManager");

// Hooks / Handlers
SealEngine::Keyboard keyboardManager;
SealEngine::KeyboardEvent *keyboardHook = new SealEngine::KeyboardEvent;

// Textures
SealEngineDraw::Texture *mario;
SealEngineDraw::Texture *missing_texture;

// Window stuff
int w = window.GetWindowWidth();
int h = window.GetWindowHeight();
int verbose = window.GetWindow()->verbose = false;

// Function to load assets (duh)
void LoadAssets()
{
    contentManager.RegisterAsset("assets/textures/missing_texture.png", "missing_texture", SealEngineContentManager::AssetTypes::TEXTURE);
    contentManager.RegisterAsset("assets/textures/mario.png", "mario", SealEngineContentManager::AssetTypes::TEXTURE);

    mario = contentManager.GetAsset<SealEngineDraw::Texture>("mario");
    missing_texture = contentManager.GetAsset<SealEngineDraw::Texture>("missing_texture");
}

// Mario settings
#define STEP_SIZE 10
int marioX = 0;
int marioY = 0;
int playerWidth = 32;
int playerHeight = 32;

void Setup()
{
    window.AttatchEventHook(keyboardHook);

    LoadAssets();

    keyboardManager.RegisterEvent("Right", []()
                                  { marioX += STEP_SIZE; });
    keyboardManager.RegisterEvent("Left", []()
                                  { marioX -= STEP_SIZE; });
    keyboardManager.RegisterEvent("Up", []()
                                  { marioY -= STEP_SIZE; });
    keyboardManager.RegisterEvent("Down", []()
                                  { marioY += STEP_SIZE; });
}

void Update()
{
    window.Clear(SealEngineTypes::Color(255));
    mario->Draw(&drawer, marioX, marioY, &playerWidth, &playerHeight);
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
