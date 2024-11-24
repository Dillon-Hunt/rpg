#include "Entity.h"

#include "raymath.h"

#include "Config.h"

void Entity::setTexture(const Texture2D& t) {
    texture = t;
}

void Entity::move(const Vector2& p) {
    position = p;
}

void Entity::slide(const Vector2& delta) {
    position = Vector2Add(position, delta);
}

Vector2 Entity::getPosition() const {
    return position;
}

int Entity::getX() const {
    return (position.x - texture.width * SCALE / 2.0f) / (CELL_SIZE * SCALE) - (position.x < 0 ? 1 : 0);
}

int Entity::getY() const {
    return position.y / (CELL_SIZE * SCALE) - (position.y < 0 ? 1 : 0);
}

int Entity::getChunkX() const {
    return getX() / CHUNK_SIZE - (position.x < 0 ? 1 : 0);
}

int Entity::getChunkY() const {
    return getY() / CHUNK_SIZE - (position.y < 0 ? 1 : 0);
}

Rectangle Entity::getCollisionShape() const {
    return {
        position.x - 19 * SCALE,
        position.y - 14 * SCALE,
        14 * SCALE,
        14 * SCALE
    };
}

// Rectangle GameObject::getCollisionShape() const {
//     return {
//         position.x - (texture.width * SCALE),
//         position.y - (texture.height * SCALE),
//         texture.width * SCALE,
//         texture.height * SCALE
//     };
// }

Rectangle Entity::getDestinationShape() const {
    return {
        position.x - (texture.width * SCALE),
        position.y - (texture.height * SCALE),
        texture.width * SCALE,
        texture.height * SCALE
    };
}

Vector2 Entity::getOrigin() const {
    return {
        0.0f,
        0.0f
    };
}

void Entity::draw() const {
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

void Entity::unloadTexture() {
    UnloadTexture(texture);
}
