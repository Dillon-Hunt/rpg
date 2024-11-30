#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

#include "GameObject.h"

#include <memory>

class Entity : public GameObject {
    public:
        Entity(Asset id, Vector2 position, std::shared_ptr<Chunk> parent) : GameObject(id, position, parent) {}

        void slide(Vector2 delta);

        void move(Vector2 v);

        const Rectangle getColider() const override;

        virtual ~Entity() {}
};

#endif // ENTITY_H
