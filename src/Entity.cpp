#include "Entity.h"

#include "raymath.h"

void Entity::move(const Vector2& p) {
    position = p;
}

void Entity::slide(const Vector2& delta) {
    position = Vector2Add(position, delta);
}
