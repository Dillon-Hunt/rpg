#ifndef GAME_H
#define GAME_H

#include "Mouse.h"
#include "NoCopy.h"
#include "Inventory.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "game-objects/entities/Player.h"

#include <memory>
#include <string>

/// Mode the game is in, determines game behaviour
enum Mode {
    GAME,
    EDIT
};

/**
 * Mangages game state and perfroms main game loop.
 *
 * Responsible for updating game state, rendering frames and communicating between components
 */
class Game : public NoCopy {
    private:
        Mouse mouse;
        std::shared_ptr<Player> player;
        CameraManager cameraManager;
        // Overlays overlays;
        SceneManager sceneManager;
        std::shared_ptr<Scene> scene;
        Inventory inventory;
        Mode mode;

    public:
        /**
         * Constructor for Game
         */
        Game() :
            player(std::make_shared<Player>(Vector2 { 0.0f, 0.0f })),
            sceneManager(player),
            mode(GAME) {}

        /**
         * Sets app all relevent components for a new game
         */
        void init();

        /**
         * Prints debug information to the console
         *
         * @param message the message to print
         */
        void logDebugInfo(const std::string message);

        /**
         * Handles bahaviour when the user clicks the screen
         *
         * @param gridPosition the position of the tile being clicked
         */
        void clickHandler(const Point& gridPosition);

        /**
         * Called every farm to update the game state
         */
        void update();

        /**
         * Checks for collisions between entities/objects
         */
        void processCollisions();

        /**
         * Clears previous frame and draws the new frame to the screen
         */
        void draw() const;

        /**
         * Unloads any resources before exiting game
         */
        void cleanup();

        /**
         * Determines if the window should close or if game loop should continue
         *
         * @returns true iff game window should close
         */
        [[nodiscard]] bool shouldClose() const;

        /**
         * Deconstructor for Game
         */
        ~Game() {
            cleanup();
        }
};

#endif // GAME_H
