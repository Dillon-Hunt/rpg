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

enum Mode {
    GAME,
    EDIT
};

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
        Game() : player(std::make_shared<Player>(Vector2 { 0.0f, 0.0f })), sceneManager(player), mode(GAME) {}

        void init();

        void logDebugInfo(const std::string message);

        void clickHandler(const Point& position);

        void update();

        void processCollisions();

        void draw() const;

        void cleanup();

        [[nodiscard]] bool shouldClose() const;

        ~Game() {
            cleanup();
        }
};

#endif // GAME_H
