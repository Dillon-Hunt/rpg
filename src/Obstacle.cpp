#include "Obstacle.h"

#include "Config.h"

Rectangle Obstacle::getCollisionShape() const {
    if (index == 6 || index == 10 || index == 15) return {
        position.x + CELL_SIZE * SCALE / 2.0f,
        position.y + CELL_SIZE * SCALE / 2.0f,
        CELL_SIZE * SCALE / 2.0f,
        CELL_SIZE * SCALE
    };

    if (index == 8 || index == 14 || index == 19) return {
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
    if (SHOW_COLLISION_SHAPE) {
        DrawRectangleRec(getCollisionShape(), RED);
    }

    DrawTexturePro(
        texture,
        {
            (float) CELL_SIZE * (int) (index % (width / CELL_SIZE)),
            (float) CELL_SIZE * (int) (index / (width / CELL_SIZE)),
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
