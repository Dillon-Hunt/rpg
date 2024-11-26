#include "Game.h"

#include "raylib.h"

#include "EventManager.h"

#include <iostream>

void Game::init() {
    EventManager::get().addListener<Game, const std::string>(
        LOG_DEBUG_INFO,
        this,
        [this](const std::string& message) {
            logDebugInfo(message);
        }
    );

    // Demo usage
    EventManager::get().emitEvent(LOG_DEBUG_INFO, std::string("Initializing game..."));
    EventManager::get().removeListener<Game, const std::string>(LOG_DEBUG_INFO, this);
    EventManager::get().removeListeners<Game, const std::string>(this);
    EventManager::get().emitEvent(LOG_DEBUG_INFO, std::string("Test"));

    int sceneID = sceneManager.createScene();
    sceneManager.setScene(sceneID);

    scene = sceneManager.getScene();

    cameraManager.follow(player);
}

void Game::logDebugInfo(const std::string message) {
    std::cout << message << std::endl;
}

void Game::update() {
    Vector2 cameraOffset = cameraManager.getOffset();

    // Player updates first so the game knows where to load chunks
    player->update();

    if (scene != nullptr) {
        scene->update();
    }

    cameraManager.update();
    mouse.update(cameraOffset);
}

void Game::processCollisions() {

}

void Game::draw() const {
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(*cameraManager.getCamera());

    if (scene != nullptr) {
        scene->draw();
    }

    player->draw();

    DrawCircle(0, 0, 2.0f, BLACK);

    mouse.draw();

    EndMode2D();
    EndDrawing();
}

void Game::cleanup() {
    std::cout << "Closing Game..." << std::endl;
}

bool Game::shouldClose() const {
    return WindowShouldClose();
}
