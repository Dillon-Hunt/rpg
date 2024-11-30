#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity.h"

#include "../../Pallet.h"

class Player : public Entity {
    private:
        Vector2 lastDirection;
        Vector2 lastPosition;

    public:
        Player(Vector2 position) : Entity(PLAYER_TEXTURE, position, nullptr), lastDirection({ 0.0f, 0.0f }), lastPosition(position) {}

        const Vector2& getPosition() const;

        const Vector2& getLastDirection() const;

        const Vector2& getLastPosition() const;

        void update() override;

        void draw() const override;

        ~Player() {}
};

#endif // PLAYER_H
