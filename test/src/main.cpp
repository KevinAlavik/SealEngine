#include <Seal/Seal.h>

SealEngine::Logger logger("SealEngineTest");
SealEngine::Window window("SealEngine Test", 800, 600);

void Setup()
{
    logger.Log(SealEngine::Logger::LogLevel::INFO, "Setup function called");
}

void Update()
{
    logger.Log(SealEngine::Logger::LogLevel::INFO, "Update function called");
    SealEngine::Timer::SleepMilliseconds(100);
}

int main()
{
    logger.Log(SealEngine::Logger::LogLevel::INFO, "Spawning window.");
    window.Spawn(Setup, Update);
    return 0;
}
