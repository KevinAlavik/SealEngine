#include <iostream>
#include <backends/window.h>
#include <utilities/logger.h>

int main()
{
    SealLogger::Logger logger("SealEngineMain");
    SealWindow::Window window("Seal Test", 800, 600);

    if (!window.spawn())
    {
        logger.fatal("Failed to spawn window.");
        return -1;
    }

    logger.ok("Window spawned successfully.");

    while (window.isRunning())
    {
        window.handleEvents();
        window.clear(0, 0, 0, 255);
        window.present();
    }

    return 0;
}