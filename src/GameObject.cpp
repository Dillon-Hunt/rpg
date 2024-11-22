#include "GameObject.h"

#include "Config.h"

void GameObject::setTexture(const Texture2D& t, int w, int h) {
    texture = t;
    width = w;
    height = h;
}

Vector2 GameObject::getPosition() const {
    return position;
}

int GameObject::getX() const {
    return position.x / (CELL_SIZE * SCALE) - 0.5f - (position.x - CELL_SIZE * SCALE * 0.5f < 0 ? 1 : 0);
}

int GameObject::getY() const {
    return position.y / (CELL_SIZE * SCALE) - 0.5f - (position.y - CELL_SIZE * SCALE * 0.5f < 0 ? 1 : 0);
}

int GameObject::getChunkX() const {
    return getX() / CHUNK_SIZE - (position.x < 0 ? 1 : 0);
}

int GameObject::getChunkY() const {
    return getY() / CHUNK_SIZE - (position.y < 0 ? 1 : 0);
}

Rectangle GameObject::getCollisionShape() const {
    return {
        position.x - 8 * SCALE,
        position.y - 12 * SCALE,
        16 * SCALE,
        12 * SCALE
    };
}

Vector2 GameObject::getOrigin() const {
    return {
        width / 2.0f * SCALE,
        height * SCALE
    };
}

void GameObject::draw() const {
    if (SHOW_COLLISION_SHAPE) {
        DrawRectangleRec(getCollisionShape(), RED);
    }

    DrawTexturePro(
        texture,
        {
            0,
            0,
            (float) width,
            (float) height
        },
        {
            position.x,
            position.y,
            width * SCALE,
            height * SCALE
        },
        getOrigin(),
        0.0f,
        WHITE
    );
}

void GameObject::unloadTexture() {
    UnloadTexture(texture);
}
