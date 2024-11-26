#ifndef PLAYER_H
#define PLAYER_H

#include "../Entity.h"

#include "../../Pallet.h"

class Player : public Entity {
    public:
        Player(int id, Vector2 position) : Entity(id, position, Pallet::get().getTexture(PLAYER), nullptr) {}

        void update() override;

        void draw() const override;

        ~Player() {}
};

#endif // PLAYER_H
