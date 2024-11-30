#include "GameObject.h"

#include "../Chunk.h"

Asset GameObject::getID() const {
    return id;
}

Vector2 GameObject::getPosition() const {
    return position;
}

std::shared_ptr<Chunk> GameObject::getParent() const {
    return parent.lock();
}


void GameObject::setParent(std::shared_ptr<Chunk> chunk) {
    parent = chunk;
}

void GameObject::addChild(std::shared_ptr<GameObject>& child) {
    children.push_back(child);
}

bool GameObject::isCollidable() const {
    return collidable;
}

const Rectangle GameObject::getColider() const {
    return collider;
}

void GameObject::update() {
    for (std::shared_ptr<GameObject>& child : children) {
        child->update();
    }
}

void GameObject::draw() const {
    for (const std::shared_ptr<GameObject>& child : children) {
        child->draw();
    }

    if (collidable && SHOW_COLLISION_BOXES) {
        DrawRectangleRec(
            getColider(),
            ColorAlpha(RED, 0.4)
        );
    }
}
