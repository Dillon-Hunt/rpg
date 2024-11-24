#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Random.h"

class Enemy : public Entity {
    private:
        Vector2 spawn;
        Vector2 target;
        float direction;
        bool locked;

    public:
        Enemy(const Texture& texture, const Vector2& position) : Entity(texture, position) {
            spawn = Vector2{ position };
            direction = getRandomNumber() * 2.0f * PI;
            locked = false;

            updateTarget();
        };

        void updateTarget();

        void update(const std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& /*chunks*/, const Entity& /*player*/) override;

        Vector2 getOrigin() const override;

        void draw() const override;
};

#endif // ENEMY_H
