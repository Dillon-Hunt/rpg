#include "Game.h"
#include "Pallet.h"

#include <memory>

int main() {
    SetTraceLogLevel(LOG_ERROR); 
    InitWindow(WIDTH, HEIGHT, "RPG Game");
    SetTargetFPS(FPS);
    SetExitKey(0);

    Pallet::get().load();

    std::shared_ptr<Game> game = std::make_shared<Game>();

    game->init();

    while (!game->shouldClose()) {
        game->update();
        game->processCollisions();
        game->draw();
    }

    return 0;
}
