#ifndef LIGHT_H
#define LIGHT_H

#include "../GameObject.h"

class Light : public GameObject {
    private:
        int radius;

    public:
        Light(Asset id, Vector2 position, int radius, std::shared_ptr<Chunk> parent) : GameObject(id, position, parent), radius(radius) {}

        void draw() const override;

        ~Light() {}
};

#endif // LIGHT_H
