#include "Mouse.h"

#include "raylib.h"

#include "utils/config.h"
#include "EventManager.h"

Point Mouse::getGridPosition() {
    return position;
}

void Mouse::update(Vector2& cameraOffset) {
    // if (IsKeyPressed(KEY_ONE)) {
    //     type = TILE;
    //     selectedTile = DIRT;
    // }
    //
    // if (IsKeyPressed(KEY_TWO)) {
    //     type = TILE;
    //     selectedTile = WATER;
    // }
    //
    // if (IsKeyPressed(KEY_THREE)) {
    //     type = TILE;
    //     selectedTile = GARDEN;
    // }
    //
    // if (IsKeyPressed(KEY_FOUR)) {
    //     type = TILE;
    //     selectedTile = ROAD;
    // }
    //
    // if (IsKeyPressed(KEY_FIVE)) {
    //     type = TILED_OBJECT;
    //     selectedTile = FENCE;
    // }
    //
    // if (IsKeyPressed(KEY_SIX)) {
    //     type = OBJECT;
    //     selectedTile = CHEST;
    // }
    //
    // if (IsKeyPressed(KEY_SEVEN)) {
    //     type = OBJECT;
    //     selectedTile = CAMPFIRE;
    // }
    //
    // if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    //     if (IsKeyDown(KEY_LEFT_SHIFT)) {
    //         EventManager::get().emitEvent(PLACE_TILE, std::pair<Point, Tile>(position, GRASS));
    //     } else {
    //         switch (type) {
    //             case TILE: 
    //                 EventManager::get().emitEvent(PLACE_TILE, std::pair<Point, Tile>(position, selectedTile));
    //                 break;
    //             case OBJECT:
    //                 EventManager::get().emitEvent(PLACE_OBJECT, std::pair<Point, Tile>(position, selectedTile));
    //                 break;
    //             case TILED_OBJECT:
    //                 EventManager::get().emitEvent(PLACE_TILED_OBJECT, std::pair<Point, Tile>(position, selectedTile));
    //                 break;
    //             case ENTITY:
    //                 break;
    //         }
    //     }
    // }


    Vector2 v = GetMousePosition();
    position = Vector2ToGridPosition(Vector2 { (v.x - cameraOffset.x) / SCALE, (v.y - cameraOffset.y) / SCALE });

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        EventManager::get().emitEvent(MOUSE_CLICK, position);
    }
}

void Mouse::draw(Vector2 cameraOffset) const {
    Vector2 v = GetMousePosition();
    DrawTextureEx(texture, { v.x - texture.width / 2.0f, v.y - texture.width / 2.0f }, 0.0f, SCALE, WHITE);
    // TODO: Store selected tile and draw outline if selected
    v = GridPositionToVector2(position);
    DrawRectangleLines((v.x - TILE_SIZE / 2.0f) * SCALE + cameraOffset.x, (v.y - TILE_SIZE / 2.0f) * SCALE + cameraOffset.y, TILE_SIZE * SCALE, TILE_SIZE * SCALE, BLUE);
}
