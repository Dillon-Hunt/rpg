#include "Inventory.h"

bool Inventory::clickHandler(const Vector2& position) {
    // TODO: Create Rectangle to store this calculation
    if (
        position.x < (float) WIDTH / 2 - ((float) HOTBAR_SIZE / 2) * (TILE_SIZE + 2) * SCALE - 5 * ((float) (HOTBAR_SIZE - 1) / 2) ||
        position.x > (float) WIDTH / 2 + ((float) HOTBAR_SIZE / 2) * (TILE_SIZE + 2) * SCALE + 5 * ((float) (HOTBAR_SIZE - 1) / 2) ||
        position.y < HEIGHT - TILE_SIZE * SCALE - WINDOW_PADDING ||
        position.y > HEIGHT - WINDOW_PADDING
    ) {
        return false;
    }

    selected = ((position.x - ((float) WIDTH / 2) + (TILE_SIZE * SCALE) * ((float) HOTBAR_SIZE / 2) + ((float) HOTBAR_SIZE / 2) * 8) / (TILE_SIZE * SCALE + 8));

    return true;
}

void Inventory::update() {
    if (IsKeyPressed(KEY_ONE)) {
        selected = 0;
    } else if (IsKeyPressed(KEY_TWO)) {
        selected = 1;
    } else if (IsKeyPressed(KEY_THREE)) {
        selected = 2;
    } else if (IsKeyPressed(KEY_FOUR)) {
        selected = 3;
    } else if (IsKeyPressed(KEY_FIVE)) {
        selected = 4;
    } else if (IsKeyPressed(KEY_SIX)) {
        selected = 5;
    } else if (IsKeyPressed(KEY_SEVEN)) {
        selected = 6;
    } else if (IsKeyPressed(KEY_EIGHT)) {
        selected = 7;
    } else if (IsKeyPressed(KEY_NINE)) {
        selected = 8;
    }
}

void Inventory::draw() const {
    for (int i = 0; i < HOTBAR_SIZE; i++) {
        DrawRectangleLinesEx(
            {
                (float) WIDTH / 2 -
                (
                    (float) HOTBAR_SIZE / 2 -
                    i
                ) * (TILE_SIZE + 2) * SCALE +
                5 * i -
                5 * ((float) (HOTBAR_SIZE - 1) / 2),
                HEIGHT - TILE_SIZE * SCALE - WINDOW_PADDING - 2,
                (TILE_SIZE + 2) * SCALE,
                (TILE_SIZE + 2) * SCALE
            },
            2.0f,
            selected == i ? BLUE : BLACK
        );

        DrawRectangle(
            (float) WIDTH / 2 -
            (
                (float) HOTBAR_SIZE / 2 -
                i
            ) * TILE_SIZE * SCALE +
            9 * i -
            9 * ((float) (HOTBAR_SIZE - 1) / 2),
            HEIGHT - TILE_SIZE * SCALE - WINDOW_PADDING,
            TILE_SIZE * SCALE,
            TILE_SIZE * SCALE,
            ColorAlpha(WHITE, 0.2f)
        );

        if (slots[i].quantity != 0 && slots[i].item != NONE) {
            DrawTexturePro(
                *slots[i].texture,
                {
                    0,
                    0,
                    TILE_SIZE,
                    TILE_SIZE
                },
                {
                    (float) WIDTH / 2 -
                    (
                        (float) HOTBAR_SIZE / 2 -
                        i
                    ) * TILE_SIZE * SCALE +
                    9 * i -
                    9 * ((float) (HOTBAR_SIZE - 1) / 2),
                    HEIGHT - TILE_SIZE * SCALE - WINDOW_PADDING,
                    TILE_SIZE * SCALE,
                    TILE_SIZE * SCALE
                },
                { 0.0f, 0.0f },
                0.0f,
                WHITE
            );
        }
    }
}
