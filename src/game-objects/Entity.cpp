#include "Entity.h"

#include "../utils/config.h"

void Entity::slide(Vector2 delta) {
    position.x += delta.x;
    position.y += delta.y;
}

void Entity::move(Vector2 v) {
    position = v;
}

const Rectangle Entity::getColider() const {
    return {
        position.x + collider.x - TILE_SIZE / 2.0f,
        position.y + collider.y,
        collider.width,
        collider.height,
    };
}
