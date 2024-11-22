#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"

class Entity : public GameObject {
    public:
        Entity() {};

        Entity(const Texture& texture, const Vector2& position, int width, int height) : GameObject(texture, position, width, height) {};

        void move(const Vector2& position);

        void slide(const Vector2& delta);

        void update(const GameObject& /*player*/) override {};
};

#endif // ENTITY_H
