#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"

class Entity : public GameObject {
    public:
        Entity() {};

        Entity(const Texture& texture, const Vector2& position) : GameObject(texture, position) {};

        void move(const Vector2& position);

        void slide(const Vector2& delta);
        
        Rectangle getCollisionShape() const override;

        void update(const GameObject& /*player*/) override {};
};

#endif // ENTITY_H
