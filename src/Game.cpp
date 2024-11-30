#include "Game.h"

#include "raylib.h"

#include "EventManager.h"

#include <iostream>

void Game::init() {
    EventManager::get().addListener<Game, const std::string&>(
        LOG_DEBUG_INFO,
        this,
        [this](const std::string& message) {
            logDebugInfo(message);
        }
    );

    // Demo usage
    EventManager::get().emitEvent(LOG_DEBUG_INFO, std::string("Initializing game..."));

    // EventManager::get().removeListener<Game, const std::string&>(LOG_DEBUG_INFO, this);
    // EventManager::get().removeListeners<Game, const std::string&>(this);

    try {
        int sceneID = sceneManager.createScene();
        sceneManager.setScene(sceneID);
        scene = sceneManager.getScene();
    } catch (const std::exception& e) {
        EventManager::get().emitEvent(LOG_DEBUG_INFO, std::string("Game::init() – Error creating scene"));
    }

    cameraManager.follow(player);
}

void Game::logDebugInfo(const std::string message) {
    std::cout << message << std::endl;
}

void Game::update() {
    Vector2 cameraOffset = cameraManager.getOffset();

    // Update player first to know which chunks to load
    player->update();

    if (scene == nullptr) {
        EventManager::get().emitEvent(LOG_DEBUG_INFO, std::string("Game::update() – Scene Not Defined"));
    } else {
        scene->update();
    }

    cameraManager.update();
    mouse.update(cameraOffset);
}

void Game::processCollisions() {
    if (scene == nullptr) {
        EventManager::get().emitEvent(LOG_DEBUG_INFO, std::string("Game::processCollisions() – Scene Not Defined"));
    } else {
        scene->checkCollisions();
    }
}

void Game::draw() const {
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(*cameraManager.getCamera());

    if (scene == nullptr) {
        EventManager::get().emitEvent(LOG_DEBUG_INFO, std::string("Game::draw() – Scene Not Defined"));
    } else {
        scene->draw();
    }

    player->draw();

    DrawCircle(0, 0, 2.0f, BLACK);

    mouse.draw();

    EndMode2D();

    DrawFPS(TILE_SIZE, TILE_SIZE);

    EndDrawing();
}

void Game::cleanup() {
    std::cout << "Closing Game..." << std::endl;

    EventManager::get().removeListeners<Game>(this);
}

[[nodiscard]] bool Game::shouldClose() const {
    return WindowShouldClose();
}
