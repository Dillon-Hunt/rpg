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
    SetTraceLogLevel(LOG_ERROR); 
    
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

    // Base Textures
    pallet.loadTexture(GRASS_DIRT, GRASS_DIRT_TEXTURE_PATH, true);
    pallet.loadTexture(GRASS_WATER, GRASS_WATER_TEXTURE_PATH, true);
    pallet.loadTexture(GRASS_GARDEN, GRASS_GARDEN_TEXTURE_PATH, true);

    // Intermediate Textures
    pallet.loadTexture(DIRT_WATER, DIRT_WATER_TEXTURE_PATH, false);

    // Chunks
    
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            chunks.emplace(std::make_pair(x, y), std::make_unique<Chunk>(x, y, chunks, pallet));
        }
    }

    // Edit mode

    editMode = false;
    selected = -1;

    // Other

    largeShadow = LoadTexture(LARGE_SHADOW_TEXTURE_PATH);
    largeShadow = LoadTexture(SMALL_SHADOW_TEXTURE_PATH);

    // tileMap.load(MAP_PATH);
}

void Game::placeGameObject(int texture) {
    chunks.at(std::make_pair(mouse.getChunkX(), mouse.getChunkY()))->place(mouse.getRelativeX(), mouse.getRelativeY(), texture);
}

void Game::handle_input() {

    // Toggle edit mode
    if (IsKeyPressed(KEY_E)) {
        editMode = !editMode;
        mouse.deselect();
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        editMode = false;
        mouse.deselect();
    }

    // Draw tile
    if (editMode) {
        if (IsKeyDown(KEY_BACKSPACE)) {
            chunks.at(std::make_pair(mouse.getChunkX(), mouse.getChunkY()))->unset(mouse.getRelativeX(), mouse.getRelativeY());
            mouse.deselect();
        }

        if ((IsMouseButtonDown(MOUSE_LEFT_BUTTON) && IsKeyDown(KEY_LEFT_SHIFT)) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            chunks.at(std::make_pair(mouse.getChunkX(), mouse.getChunkY()))->unset(mouse.getRelativeX(), mouse.getRelativeY());
        } else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            int key = pallet.getTextureFromPallet();
            bool draw = true;

            if (key == -1) {
                key = selected;
            } else {
                selected = key;
                draw = false;
            }

            if (key != -1 && draw) {
                chunks.at(
                    std::make_pair(
                        mouse.getChunkX(),
                        mouse.getChunkY())
                )->set(
                    mouse.getRelativeX(),
                    mouse.getRelativeY(),
                    key
                );

                selected = key;
            } else {
                mouse.updatePosition(camera.target.x - camera.offset.x, camera.target.y - camera.offset.y);
            }
        }
    } else {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !IsKeyDown(KEY_LEFT_SHIFT)) {
            mouse.updatePosition(camera.target.x - camera.offset.x, camera.target.y - camera.offset.y);
            mouse.select();
        }
    }
    
    if (mouse.isSelected() && IsKeyPressed(KEY_P)) {
        placeGameObject(FENCE);
        mouse.deselect();
    }

    // Determine direction vector
    
    Vector2 direction = { 0, 0 };

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) direction.x = 1;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) direction.x = -1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) direction.y = -1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) direction.y = 1;

    direction = Vector2Normalize(direction);

    // Move Player
    player.slide(Vector2{ direction.x, 0.0f } * SCALE * SPEED);

    // Move player back if movement caused collision
    if (player.checkCollisions<Entity>(entities)) {
        player.slide(Vector2{ -direction.x, 0.0f } * SCALE * SPEED);
    }

    // Move Player
    player.slide(Vector2{ 0.0f, direction.y } * SCALE * SPEED);

    // Move player back if movement caused collision
    if (player.checkCollisions<Entity>(entities)) {
        player.slide(Vector2{ 0.0f, -direction.y } * SCALE * SPEED);
    }

    // Move camera
    camera.target = Vector2MoveTowards(camera.target, player.getPosition(), Vector2Distance(camera.target, player.getPosition()) / CELL_SIZE / SCALE);

    // Move mouse
    if (!mouse.isSelected()) {
        mouse.updatePosition(camera.target.x - camera.offset.x, camera.target.y - camera.offset.y);
    }
}

void Game::update() {
    //std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;

    BeginDrawing();

    ClearBackground(WHITE);

    BeginMode2D(camera);

    // Load 25 chunks around player
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            std::pair<int, int> chunk = std::make_pair(x + player.getChunkX(), y + player.getChunkY());

            auto iterator = chunks.find(chunk);

            if (iterator == chunks.end()) {
                chunks.emplace(chunk, std::make_unique<Chunk>(chunk.first, chunk.second, chunks, pallet));
            }
        }
    }

    // Display 9 chunks around player
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            chunks.at(std::make_pair(x + player.getChunkX(), y + player.getChunkY()))->draw();
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
    if (editMode) {
        pallet.renderPallet();
    }

    float y = CELL_SIZE * SCALE / 2;

    DrawFPS(CELL_SIZE * SCALE / 2, y);

    y += TEXT_SEPARATION;

    // Print info to screen
    char text[50];
    snprintf(text, sizeof(text), "Player Position: (%d, %d)", player.getX(), player.getY());
    DrawText(text, CELL_SIZE * SCALE / 2, y, 15, BLACK);

    y += TEXT_SEPARATION * 2;

    if (mouse.isSelected()) {
        strcpy(text, "Selected Tile:");
        DrawText(text, CELL_SIZE * SCALE / 2, y, 15, BLACK);

        y += TEXT_SEPARATION;

        snprintf(text, sizeof(text), "Position: (%d, %d)", mouse.getX(), mouse.getY());
        DrawText(text, CELL_SIZE * SCALE / 2, y, 15, BLACK);

        y += TEXT_SEPARATION;

        int key = chunks.at(std::make_pair(mouse.getChunkX(), mouse.getChunkY()))->getTileTexture(mouse.getRelativeX(), mouse.getRelativeY());

        std::string tile = "";

        switch (key) {
            case GRASS:
                tile = "Grass";
                break;
            case DIRT: 
                tile = "Dirt";
                break;
            case WATER: 
                tile = "Water";
                break;
            case GARDEN: 
                tile = "Garden";
                break;
        }
        
        snprintf(text, sizeof(text), "Name: %s", tile.c_str());
        DrawText(text, CELL_SIZE * SCALE / 2, y, 15, BLACK);
    }

    EndDrawing();
}

void Game::cleanup() {
    std::cout << "Closing game..." << std::endl;

    // Unload all textures
    pallet.unloadTextures();
    player.unloadTexture();

    for (auto& pair : chunks) {
        pair.second->unloadTextures();
    }

    for (std::unique_ptr<Entity>& entity : entities) {
        entity->unloadTexture();
    }

    CloseWindow();
}

bool Game::shouldClose() const {
    return WindowShouldClose();
}
