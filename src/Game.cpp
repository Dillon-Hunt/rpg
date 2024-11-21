// #include "resource_dir.h"

#include "Game.h"

#include "raylib.h"
#include "raymath.h"

#include "Config.h"
#include "NPC.h"

#include <iostream>
#include <memory>

void Game::init() {
    std::cout << "Initializing game..." << std::endl;

    // SearchAndSetResourceDir("resources");
    InitWindow(WIDTH, HEIGHT, "RPG Game");
    SetTargetFPS(FPS);
    SetExitKey(0);
    
    // Player Setup
    
    player.setTexture(LoadTexture(PLAYER_TEXTURE_PATH));
    player.move({ WIDTH / 2.0f, HEIGHT / 2.0f });

    // NPC Setup
    
    // Frank

    entities.push_back(std::make_unique<NPC>(LoadTexture(NPC_1_TEXTURE_PATH), Vector2{ 1 * CELL_SIZE * SCALE, 1 * CELL_SIZE * SCALE }));

    if (NPC* frank = dynamic_cast<NPC*>(entities.back().get())) {
        frank->addWaypoint({ 10 * CELL_SIZE * SCALE, 1 * CELL_SIZE * SCALE });
        frank->addWaypoint({ 10 * CELL_SIZE * SCALE, 5 * CELL_SIZE * SCALE });
        frank->addWaypoint({ 1 * CELL_SIZE * SCALE, 5 * CELL_SIZE * SCALE });
    }

    // Camera Setup
    
    camera.target = player.getPosition();
    camera.offset = { WIDTH / 2.0f, HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Tile Pallet

    pallet.loadTexture(GRASS_DIRT, GRASS_DIRT_TEXTURE_PATH);
    pallet.loadTexture(GRASS_WATER, GRASS_WATER_TEXTURE_PATH);
    pallet.loadTexture(GRASS_GRASS, GRASS_GRASS_TEXTURE_PATH);

    // Chunks
    
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            chunks.emplace(std::make_pair(x, y), std::make_unique<Chunk>(x, y));
        }
    }

    // Edit mode

    editMode = false;
    selected = -1;

    // tileMap.load(MAP_PATH);
}

void Game::handle_input() {

    // Toggle edit mode
    if (IsKeyPressed(KEY_E)) {
        editMode = !editMode;
        mouse.deselect();
    }

    // Draw tile
    if (mouse.isSelected() || editMode) {
        if (IsKeyPressed(KEY_BACKSPACE)) {
            chunks.at(std::make_pair(mouse.getChunkX(), mouse.getChunkY()))->unset(mouse.getRelativeX(), mouse.getRelativeY());
            mouse.deselect();
        }

        if (editMode && IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            chunks.at(std::make_pair(mouse.getChunkX(), mouse.getChunkY()))->unset(mouse.getRelativeX(), mouse.getRelativeY());
        }

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            int key = pallet.getTextureFromPallet();
            bool draw = true;

            if (editMode) {
                if (key == -1) {
                    key = selected;
                } else {
                    selected = key;
                    draw = false;
                }
            }

            if (key != -1 && draw) {
                chunks.at(
                    std::make_pair(
                        mouse.getChunkX(),
                        mouse.getChunkY())
                )->set(
                    mouse.getRelativeX(),
                    mouse.getRelativeY(),
                    key,
                    chunks
                );

                if (!editMode) {
                    selected = key;
                    mouse.deselect();
                }
            } else {
                mouse.updatePosition(camera.target.x - camera.offset.x, camera.target.y - camera.offset.y);
            }
        }
    } else {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            mouse.select();
        }
    }

    // Deselect tile
    if (IsKeyPressed(KEY_ESCAPE)) {
        mouse.deselect();
    }

    // Determine direction vector
    
    Vector2 direction = { 0, 0 };

    if (IsKeyDown(KEY_RIGHT)) direction.x = 1;
    if (IsKeyDown(KEY_LEFT)) direction.x = -1;
    if (IsKeyDown(KEY_UP)) direction.y = -1;
    if (IsKeyDown(KEY_DOWN)) direction.y = 1;

    direction = Vector2Normalize(direction);

    // Move Player
    player.slide(direction * SCALE * SPEED);

    // Move player back if movement caused collision
    if (player.checkCollisions(entities)) {
        player.slide(direction * SCALE * SPEED * -1);
    }

    // Move camera
    camera.target = Vector2MoveTowards(camera.target, player.getPosition(), Vector2Distance(camera.target, player.getPosition()) / CELL_SIZE / SCALE);

    // Move mouse
    if (!mouse.isSelected()) {
        mouse.updatePosition(camera.target.x - camera.offset.x, camera.target.y - camera.offset.y);
    }
}

void Game::update() {
    BeginDrawing();

    ClearBackground(WHITE);

    BeginMode2D(camera);

    // Load 25 chunks around player
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            std::pair<int, int> chunk = std::make_pair(x + player.getChunkX(), y + player.getChunkY());

            auto iterator = chunks.find(chunk);

            if (iterator == chunks.end()) {
                chunks.emplace(chunk, std::make_unique<Chunk>(chunk.first, chunk.second));
            }
        }
    }

    // Display 9 chunks around player
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            chunks.at(std::make_pair(x + player.getChunkX(), y + player.getChunkY()))->draw(pallet, chunks);
        }
    }

    // Draw mouse selector
    mouse.draw();

    // Display all NPCs within visible chunks
    for (std::unique_ptr<Entity>& entity : entities) {
        if (Vector2Distance(
            {
                (float) entity->getChunkX(),
                (float) entity->getChunkY()
            },
            {
                (float) player.getChunkX(),
                (float) player.getChunkY()
            }
        ) <= 1) {
            entity->update(player);
            entity->draw();
        }
    }

    // Draw Player
    player.draw();

    EndMode2D();

    // Draw pallet selector
    if (mouse.isSelected() || editMode) {
        pallet.renderPallet();
    }

    // Print info to screen
    char text[50];

    snprintf(text, sizeof(text), "Player Position: (%d, %d)", player.getX(), player.getY());

    DrawFPS(CELL_SIZE * SCALE / 2, CELL_SIZE * SCALE / 2);
    DrawText(text, CELL_SIZE * SCALE / 2, CELL_SIZE * SCALE, 15, BLACK);

    EndDrawing();
}

void Game::cleanup() {
    std::cout << "Closing game..." << std::endl;

    // Unload all textures
    pallet.unloadTextures();
    player.unloadTexture();

    for (std::unique_ptr<Entity>& entity : entities) {
        entity->unloadTexture();
    }

    CloseWindow();
}

bool Game::shouldClose() const {
    return WindowShouldClose();
}
