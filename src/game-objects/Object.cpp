#include "Object.h"

#include "../utils/config.h"

const Rectangle Object::getColider() const {
    return Rectangle {
        position.x + collider.x - TILE_SIZE / 2.0f,
        position.y + collider.y - TILE_SIZE / 2.0f,
        collider.width,
        collider.height,
    };
}


void Object::draw() const {
    DrawTexture(
        *texture,
        position.x - TILE_SIZE / 2.0f,
        position.y - TILE_SIZE / 2.0f,
        WHITE
    );

    GameObject::draw();
}
