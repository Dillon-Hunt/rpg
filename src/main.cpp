#include "Game.h"

int main() {
    Game game;

    while (!game.shouldClose()) {
        game.handle_input();
        game.update();
    }

    game.cleanup();

    return 0;
}
