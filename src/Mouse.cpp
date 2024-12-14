#include "Mouse.h"

#include "raylib.h"
#include "raymath.h"

#include "utils/config.h"

Point Mouse::getGridPosition() {
    return position;
}

bool Mouse::clickHandler() {
    Vector2 newPos = GridPositionToVector2(position);

    if (selected && newPos == selectedTile) {
        selected = false;
    } else {
        selected = true;
        selectedTile = newPos;
    }

    return true;
}

void Mouse::update(Vector2& cameraOffset) {
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

    if (mode == EDIT) {
        selectedTile = GridPositionToVector2(position);
    }
}

void Mouse::drawSelector() const {
    if (selected || mode == EDIT) {
        DrawTexture(
            selectedTexture,
            (selectedTile.x - selectedTexture.width / 2.0f),
            (selectedTile.y - selectedTexture.height / 2.0f),
            WHITE
        );
    }
}

void Mouse::drawCursor() const {
    Vector2 v = GetMousePosition();
    DrawTextureEx(cursorTexture, { v.x - (cursorTexture.width / 2.0f) * SCALE, v.y - (cursorTexture.width / 2.0f) * SCALE }, 0.0f, SCALE, WHITE);
}
