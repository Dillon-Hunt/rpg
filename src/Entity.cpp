#include "Entity.h"

#include "raymath.h"

#include "Config.h"

void Entity::setTexture(const Texture2D& newTexture) {
    texture = newTexture;
}

void Entity::move(const Vector2& p) {
    position = p;
}

void Entity::slide(const Vector2& delta) {
    position += delta;
}

bool Entity::checkCollision(const Entity& entity) const {
    return CheckCollisionRecs(getCollisionShape(), entity.getCollisionShape());
}

bool Entity::checkCollisions(const std::vector<std::unique_ptr<Entity>>& entities) const {
    Rectangle collisionShape = getCollisionShape();

    for (const std::unique_ptr<Entity>& entity : entities) {
        if (CheckCollisionRecs(collisionShape, entity->getCollisionShape())) {
            return true;
        }
    }

    return false;
}

Vector2 Entity::getPosition() const {
    return position;
}

int Entity::getX() const {
    return position.x / (CELL_SIZE * SCALE) - 0.5f - (position.x - CELL_SIZE * SCALE * 0.5f < 0 ? 1 : 0);
}

int Entity::getY() const {
    return position.y / (CELL_SIZE * SCALE) - 0.5f - (position.y - CELL_SIZE * SCALE * 0.5f < 0 ? 1 : 0);
}

int Entity::getChunkX() const {
    return getX() / CHUNK_SIZE - (position.x < 0 ? 1 : 0);
}

int Entity::getChunkY() const {
    return getY() / CHUNK_SIZE - (position.y < 0 ? 1 : 0);
}

Rectangle Entity::getCollisionShape() const {
    return {
        position.x - 8 * SCALE,
        position.y - 12 * SCALE,
        16 * SCALE,
        12 * SCALE
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
            24,
            48
        },
        {
            position.x,
            position.y,
            24 * SCALE,
            48 * SCALE
        },
        {
            12.0f * SCALE,
            48.0f * SCALE
        },
        0.0f,
        WHITE
    );
}

void Entity::unloadTexture() {
    UnloadTexture(texture);
}
