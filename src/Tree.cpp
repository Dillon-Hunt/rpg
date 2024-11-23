#include "Tree.h"

#include "Config.h"

Rectangle Tree::getCollisionShape() const {
    return {
        position.x - (texture.width - 50) * SCALE,
        position.y + (texture.height - 21) * SCALE,
        46 * SCALE,
        9 * SCALE
    };
}

Vector2 Tree::getOrigin() const {
    return {
        0,
        0 + texture.width * SCALE / 4.0f
    };
}
