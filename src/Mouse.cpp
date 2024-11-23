#include "Mouse.h"

#include "Config.h"

void Mouse::select() {
    selected = true;
}

void Mouse::deselect() {
    selected = false;
}

bool Mouse::isSelected() const {
    return selected;
}

int Mouse::getX() const {
    return x;
}

int Mouse::getY() const {
    return y;
}

int Mouse::getRelativeX() const {
    return getX() < 0 ? CHUNK_SIZE + getX() % CHUNK_SIZE : getX() % CHUNK_SIZE;
}

int Mouse::getRelativeY() const {
    return getY() < 0 ? CHUNK_SIZE + getY() % CHUNK_SIZE : getY() % CHUNK_SIZE;
}

int Mouse::getChunkX() const {
    return x / CHUNK_SIZE - (x < 0 ? 1 : 0);
}

int Mouse::getChunkY() const {
    return y / CHUNK_SIZE - (y < 0 ? 1 : 0);
}

void Mouse::updatePosition(int offsetX, int offsetY) {
    Vector2 position = GetMousePosition();

    position.x += offsetX;
    position.y += offsetY;

    x = (position.x) / CELL_SIZE / SCALE;
    y = (position.y) / CELL_SIZE / SCALE;

    if (position.x < 0) x--;
    if (position.y < 0) y--;
}

void Mouse::draw() const {
    DrawRectangleLinesEx(
        {
            x * CELL_SIZE * SCALE,
            y * CELL_SIZE * SCALE, 
            width * CELL_SIZE * SCALE,
            height * CELL_SIZE * SCALE
        },
        2.0f,
        selected ? RED : color
    );
}
