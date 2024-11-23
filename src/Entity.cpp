#include "Entity.h"

#include "raymath.h"

#include "Config.h"

void Entity::move(const Vector2& p) {
    position = p;
}

void Entity::slide(const Vector2& delta) {
    position = Vector2Add(position, delta);
}

Rectangle Entity::getCollisionShape() const {
    return {
        position.x - 19 * SCALE,
        position.y - 14 * SCALE,
        14 * SCALE,
        14 * SCALE
    };
}
