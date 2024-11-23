#ifndef TREE_H
#define TREE_H

#include "GameObject.h"

class Tree : public GameObject {
    public:
        Tree(const Texture& texture, const Vector2& position) : GameObject(texture, position) {};

        Rectangle getCollisionShape() const override;

        Vector2 getOrigin() const override;
};

#endif // TREE_H
