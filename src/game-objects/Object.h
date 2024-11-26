#ifndef OBJECT_H
#define OBJECT_H

#include "raylib.h"

#include "GameObject.h"

#include <memory>

class Object : public GameObject {
    public:
        Object(int id, Vector2 position, Texture2D& texture, std::shared_ptr<Chunk> parent) : GameObject(id, position, texture, parent) {}

        virtual ~Object() {}
};

#endif // OBJECT_H
