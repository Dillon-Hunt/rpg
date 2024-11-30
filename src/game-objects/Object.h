#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"

#include "GameObject.h"

#include <memory>

class Object : public GameObject {
    public:
        Object(Asset id, Vector2 position, std::shared_ptr<Chunk> parent) : GameObject(id, position, parent) {}

        const Rectangle getColider() const override;

        void draw() const override;

        virtual ~Object() {}
};

#endif // OBJECT_H
