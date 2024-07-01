#include <Seal/Seal.h>
#include <Seal/Draw.h>

#define MAX_FPS 120

SealEngine::Logger logger("TestGame");
SealEngine::Window window("Test Game", 800, 600);
SealEngineDraw::Drawer drawer(&window, &logger);

void Setup()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            drawer.PutPixel(i, j, SealEngineDraw::Color(255, 0, 0, 255));
        }
    }
}

void Update()
{
    SealEngine::Timer::SleepMilliseconds(1000 / MAX_FPS);
}

int main()
{
    logger.Log(SealEngine::Logger::LogLevel::INFO, "Spawning window.");
    window.Spawn(Setup, Update);
    logger.Log(SealEngine::Logger::LogLevel::OK, "Finished running TestGame.");
    return 0;
}
