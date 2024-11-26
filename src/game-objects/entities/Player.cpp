#include "Player.h"

#include "raylib.h"
#include "raymath.h"

#include "../../utils/config.h"

void Player::update() {
    Vector2 direction = { 0, 0 };

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) direction.x = 1;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) direction.x = -1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) direction.y = -1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) direction.y = 1;

    direction = Vector2Normalize(direction);

    position += direction * PLAYER_SPEED;
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
}
