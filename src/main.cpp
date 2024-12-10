#include "Game.h"
#include "Pallet.h"
#include "Database.h"

int main() {
    SetTraceLogLevel(LOG_ERROR); 
    InitWindow(WIDTH, HEIGHT, "RPG Game");
    SetTargetFPS(FPS);
    SetExitKey(0);
    HideCursor();

    Pallet::get().load();

    Database::get().load("resources/data.db");

    Game game;

    game.init();

    while (!game.shouldClose()) {
        game.update();
        game.processCollisions();
        game.draw();
    }

    return 0;
}
