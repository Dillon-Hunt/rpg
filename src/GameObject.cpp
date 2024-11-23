#include "GameObject.h"

#include "Config.h"

void GameObject::setTexture(const Texture2D& t) {
    texture = t;
}

Vector2 GameObject::getPosition() const {
    return position;
}

int GameObject::getX() const {
    return position.x / (CELL_SIZE * SCALE) - (position.x - CELL_SIZE * SCALE * 0.5f < 0 ? 1 : 0);
}

int GameObject::getY() const {
    return position.y / (CELL_SIZE * SCALE) - (position.y - CELL_SIZE * SCALE * 0.5f < 0 ? 1 : 0);
}

int GameObject::getChunkX() const {
    return getX() / CHUNK_SIZE - (position.x < 0 ? 1 : 0);
}

int GameObject::getChunkY() const {
    return getY() / CHUNK_SIZE - (position.y < 0 ? 1 : 0);
}

Rectangle GameObject::getCollisionShape() const {
    return {
        position.x - (texture.width * SCALE),
        position.y - (texture.height * SCALE),
        texture.width * SCALE,
        texture.height * SCALE
    };
}

Rectangle GameObject::getDestinationShape() const {
    return {
        position.x - (texture.width * SCALE),
        position.y - (texture.height * SCALE),
        texture.width * SCALE,
        texture.height * SCALE
    };
}

Vector2 GameObject::getOrigin() const {
    return {
        0.0f,
        0.0f
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
            (float) texture.width,
            (float) texture.height
        },
        getDestinationShape(),
        getOrigin(),
        0.0f,
        WHITE
    );
}

void GameObject::unloadTexture() {
    UnloadTexture(texture);
}
