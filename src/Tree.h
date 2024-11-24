#ifndef TREE_H
#define TREE_H

#include "Entity.h"

class Tree : public Entity {
    public:
        Tree(const Texture& texture, const Vector2& position) : Entity(texture, position) {};

        Rectangle getCollisionShape() const override;

        Vector2 getOrigin() const override;
};

#endif // TREE_H
