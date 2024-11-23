#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

class Obstacle : public GameObject {
    private:
        int key;

    public:
        Obstacle() {};

        Obstacle(const Texture& texture, const Vector2& position, int key) : GameObject(texture, position), key(key) {};

        Rectangle getCollisionShape() const override;

        Vector2 getOrigin() const override;

        void draw() const override;
};

#endif // OBSTACLE_H

