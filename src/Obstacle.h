#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"

class Obstacle : public GameObject {
    private:
        int index;

    public:
        Obstacle() {};

        Obstacle(const Texture& texture, const Vector2& position, int index, int width, int height) : GameObject(texture, position, width, height), index(index) {};

        Rectangle getCollisionShape() const override;

        Vector2 getOrigin() const override;

        void draw() const override;
};

#endif // OBSTACLE_H

