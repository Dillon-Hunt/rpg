#include "Game.h"

#include "raylib.h"

#include "EventManager.h"

#include <iostream>

void Game::init() {
    eventManager.addListener<Game, const Point&>(
        MOUSE_CLICK,
        this,
        [this](const Point& position) {
            clickHandler(position);
        }
    );

    // Demo usage
    eventManager.emitEvent(LOG_DEBUG_INFO, std::string("Initializing game..."));

    // eventManager.removeListener<Game, const std::string&>(LOG_DEBUG_INFO, this);
    // eventManager.removeListeners<Game, const std::string&>(this);

    try {
        int sceneID = sceneManager.createScene();
        sceneManager.setScene(sceneID);
        scene = sceneManager.getScene();
    } catch (const std::exception& e) {
        eventManager.emitEvent(LOG_DEBUG_INFO, std::string("Game::init() – Error creating scene"));
    }

    cameraManager.follow(player);
}

void Game::clickHandler(const Point& gridPosition) {
    Vector2 mousePosition = GetMousePosition();

    // Allow handeling of clicks by z-axis priority

    if (inventory.clickHandler(mousePosition)) return;

    switch (mode) {
        case GAME:
            if (mouse.clickHandler(gridPosition)) return;
            break; 
        case EDIT:
            if (pallet.clickHandler(mousePosition)) return;
            if (scene->clickHandler(gridPosition)) return;
            break;
    }

    std::cout << "Click not handled" << std::endl;
}

void Game::toggleMode() {
    switch (mode) {
        case GAME:
            mode = EDIT;
            break;
        case EDIT:
            mode = GAME;
            break;
    }
}

void Game::handleKeyPresses() {

    // Click
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        eventManager.emitEvent(MOUSE_CLICK, mouse.getGridPosition());
    }

    // Toggle Mode
    if (IsKeyPressed(KEY_M)) {
        toggleMode();
    }

    // Escape
    if (IsKeyPressed(KEY_ESCAPE)) {
        eventManager.emitEvent(ESCAPE);
    }

    // Number keys reserved for inventory hotbar (managed in Inventory.cpp)
}

void Game::update() {
    handleKeyPresses();

    Vector2 cameraOffset = cameraManager.getOffset();

    // Update player first to know which chunks to load
    player->update();

    if (scene == nullptr) {
        eventManager.emitEvent(LOG_DEBUG_INFO, std::string("Game::update() – Scene Not Defined"));
    } else {
        scene->update();
    }

    inventory.update();
    cameraManager.update();
    mouse.update(cameraOffset);
}

void Game::processCollisions() {
    if (scene == nullptr) {
        eventManager.emitEvent(LOG_DEBUG_INFO, std::string("Game::processCollisions() – Scene Not Defined"));
    } else {
        scene->checkCollisions();
    }
}

void Game::draw() const {
    // Vector2 cameraOffset = cameraManager.getOffset();

    BeginDrawing();
    ClearBackground(WHITE);

    BeginMode2D(*cameraManager.getCamera());
    DrawCircle(0, 0, 2.0f, BLACK);

    if (scene == nullptr) {
        eventManager.emitEvent(LOG_DEBUG_INFO, std::string("Game::draw() – Scene Not Defined"));
    } else {
        scene->draw();
    }

    player->draw();
    mouse.drawSelector();

    EndMode2D();

    DrawFPS(TILE_SIZE, TILE_SIZE);

    if (mode == EDIT) pallet.draw();
    inventory.draw();
    mouse.drawCursor();

    EndDrawing();
}

void Game::cleanup() {
    eventManager.emitEvent(LOG_DEBUG_INFO, std::string("Closing Game..."));
    eventManager.removeListeners<Game>(this);
}

[[nodiscard]] bool Game::shouldClose() const {
    return WindowShouldClose();
}
