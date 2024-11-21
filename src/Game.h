#ifndef GAME_H
#define GAME_H

#include "Chunk.h"
#include "Entity.h"
#include "Mouse.h"

#include <vector>
#include <map>

class Game {
    private:
        std::map<std::pair<int, int>, std::unique_ptr<Chunk>> chunks;
        Pallet pallet;
        Camera2D camera;
        Entity player;
        std::vector<std::unique_ptr<Entity>> entities;
        Mouse mouse;
        bool editMode;
        int selected;

    public:
        /* Constructor for the Game class
         *
         */
        Game() : mouse(0, 0) {
            init();
        };

        /* Initialises a new game window
         *
         */
        void init();

        /* Check for inputs
         */
        void handle_input();

        /* Updates the current game state
         */
        void update();

        /* Performs cleanup actions after closing the game windoe
         */
        void cleanup();

        /* Determines whither to close the game window
         */
        bool shouldClose() const;
};

#endif // GAME_H
