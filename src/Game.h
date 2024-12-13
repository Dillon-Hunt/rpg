#ifndef GAME_H
#define GAME_H

#include "Mouse.h"
#include "NoCopy.h"
#include "Inventory.h"
#include "CameraManager.h"
#include "SceneManager.h"
#include "game-objects/entities/Player.h"

#include <memory>

/**
 * Mangages game state and perfroms main game loop.
 *
 * Responsible for updating game state, rendering frames and communicating between components
 */
class Game : public NoCopy {
    private:
        Mode mode;
        Mouse mouse;
        std::shared_ptr<Player> player;
        CameraManager cameraManager;
        EventManager& eventManager;
        SceneManager sceneManager;
        std::shared_ptr<Scene> scene;
        Inventory inventory;

    public:
        /**
         * Constructor for Game
         */
        Game() :
            mode(GAME),
            mouse(mode),
            player(std::make_shared<Player>(Vector2 { 0.0f, 0.0f })),
            eventManager(EventManager::get()),
            sceneManager(player) {}

        /**
         * Sets app all relevent components for a new game
         */
        void init();

        /**
         * Handles bahaviour when the user clicks the screen
         *
         * @param gridPosition the position of the tile being clicked
         */
        void clickHandler(const Point& gridPosition);

        /**
         * Switch between gameplay and edit modes
         */
        void toggleMode();

        /**
         * Handle key presses and emit relevant events
         */
        void handleKeyPresses();

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
