#include "Game.h"
#include "Pallet.h"
#include "Database.h"

/**
 * Prints debug information to the console
 *
 * @param message the message to print
 */
void logDebugInfo(const std::string message) {
    std::cout << message << std::endl;
}

int main() {
    SetTraceLogLevel(LOG_ERROR); 
    InitWindow(WIDTH, HEIGHT, "RPG Game");
    SetTargetFPS(FPS);
    SetExitKey(0);
    HideCursor();

    std::cout << EventManager::get().addListener<std::nullptr_t, const std::string&>(
        LOG_DEBUG_INFO,
        nullptr,
        [](const std::string& message) {
            logDebugInfo(message);
        }
    ) << std::endl;

    Pallet::get().load();

    Database::get().load("resources/data.db");

    Game game;

    game.init();

    while (!game.shouldClose()) {
        game.update();
        game.processCollisions();
        game.draw();
    }

    EventManager::get().removeListeners<std::nullptr_t>(nullptr);

    return 0;
}
