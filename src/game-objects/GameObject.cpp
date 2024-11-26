#include "GameObject.h"

#include "../Chunk.h"

int GameObject::getID() const {
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

void GameObject::setTexture(Texture2D& t) {
    texture = t;
}

void GameObject::addChild(std::unique_ptr<GameObject>& child) {
    children.push_back(std::move(child));
}

void GameObject::update() {
    for (std::unique_ptr<GameObject>& child : children) {
        child->update();
    }
}

void GameObject::draw() const {
    for (const std::unique_ptr<GameObject>& child : children) {
        child->draw();
    }
}
