#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

#include "GameObject.h"

#include <memory>

class Entity : public GameObject {
    public:
        Entity(int id, Vector2 position, Texture2D& texture, std::shared_ptr<Chunk> parent) : GameObject(id, position, texture, parent) {}

        virtual ~Entity() {}
};

#endif // ENTITY_H
