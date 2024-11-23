#include "Obstacle.h"

#include "Config.h"

#include <iostream>

Rectangle Obstacle::getCollisionShape() const {
    if (key == 6 || key == 10 || key == 15) return {
        position.x + CELL_SIZE * SCALE / 2.0f,
        position.y + CELL_SIZE * SCALE / 2.0f,
        CELL_SIZE * SCALE / 2.0f,
        CELL_SIZE * SCALE
    };

    if (key == 8 || key == 14 || key == 19) return {
        position.x + CELL_SIZE * SCALE,
        position.y + CELL_SIZE * SCALE / 2.0f,
        CELL_SIZE * SCALE / 2.0f,
        CELL_SIZE * SCALE
    };

    return {
        position.x + CELL_SIZE * SCALE / 2.0f,
        position.y + CELL_SIZE * SCALE / 2.0f,
        CELL_SIZE * SCALE,
        CELL_SIZE * SCALE
    };
}

Vector2 Obstacle::getOrigin() const {
    return {
        -CELL_SIZE * SCALE / 2.0f,
        -CELL_SIZE * SCALE / 2.0f
    };
}

void Obstacle::draw() const {
    std::cout << position.x << " " << position.y << std::endl;
    if (SHOW_COLLISION_SHAPE) {
        DrawRectangleRec(getCollisionShape(), RED);
    }

    DrawTexturePro(
        texture,
        {
            (float) CELL_SIZE * (int) (key % (texture.width / CELL_SIZE)),
            (float) CELL_SIZE * (int) (key / (texture.width / CELL_SIZE)),
            CELL_SIZE,
            CELL_SIZE
        },
        {
            position.x,
            position.y,
            CELL_SIZE * SCALE,
            CELL_SIZE * SCALE
        },
        getOrigin(),
        0.0f,
        WHITE
    );
}
