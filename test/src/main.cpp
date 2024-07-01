#include <Seal/Seal.h>
#include <Seal/Draw.h>

SealEngine::Logger logger("TestGame");
SealEngine::Window window("Test Game", 800, 600);
SealEngineDraw::Drawer drawer(&window, &logger);

int w = window.GetWindowWidth();
int h = window.GetWindowHeight();

void Setup()
{
}

void Update()
{

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            drawer.PutPixel(i, j, SealEngineDraw::Color(255, 0, 0, 255));
        }
    }
}

int main()
{
    window.Spawn(Setup, Update);
    logger.Log(SealEngine::Logger::LogLevel::OK, "Finished running TestGame.");
    return 0;
}
