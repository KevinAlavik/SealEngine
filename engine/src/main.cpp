#include <iostream>
#include <backends/window.h>
#include <utilities/logger.h>

class TestHandleHook : public SealWindow::SealWindowHookHandleEvent
{
public:
    TestHandleHook() : logger("TestHandleHook") {}

    void handleEventsHook(SDL_Event &event) override
    {
        logger.info("Handling events...");
    }

private:
    SealLogger::Logger logger;
};

int main()
{
    SealLogger::Logger logger("SealEngineMain");
    SealWindow::Window window("Seal Test", 800, 600);

    if (!window.spawn())
    {
        logger.fatal("Failed to spawn window.");
        return -1;
    }

    logger.info("Window spawned successfully.");
    TestHandleHook testHandleHook;
    window.attachHandleEventHook(&testHandleHook);
    logger.info("Created test handle hook.");

    while (window.isRunning())
    {
        window.handleEvents();
        window.clear(0, 0, 0, 255);
        window.present();
    }

    return 0;
}
