#include "Player.h"

#include "raylib.h"
#include "raymath.h"

#include "../../utils/config.h"

const Vector2& Player::getPosition() const {
    return position;
}

const Vector2& Player::getLastDirection() const {
    return lastDirection;
}

const Vector2& Player::getLastPosition() const {
    return lastPosition;
}

void Player::update() {
    lastPosition = position;

    Vector2 direction = { 0, 0 };

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) direction.x = 1;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) direction.x = -1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) direction.y = -1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) direction.y = 1;

    direction = Vector2Normalize(direction);

    lastDirection = direction;

    position += direction * PLAYER_SPEED;

    Entity::draw();
}

void Player::draw() const {
    DrawTexturePro(
        texture,
        {
            0,
            0,
            (float) texture.width,
            (float) texture.height
        },
        {
            position.x,
            position.y,
            (float) texture.width,
            (float) texture.height
        },
        {
            texture.width / 2.0f,
            (float) texture.height
        },
        0.0f,
        WHITE
    );

    Entity::draw();
}
