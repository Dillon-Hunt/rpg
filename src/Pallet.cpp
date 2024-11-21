#include "Pallet.h"

#include "Config.h"

#include <iostream>

void Pallet::loadTexture(int key, const char* path) {
    textures.emplace(key, std::make_unique<Texture2D>(LoadTexture(path)));
}

const std::shared_ptr<Texture2D> Pallet::getTexture(int key) const {
    return textures.at(key);
}

int Pallet::getTextureFromPallet() const {
    Vector2 position = GetMousePosition();

    int x = (position.x - WIDTH + CELL_SIZE * SCALE * 2 + PALLET_BORDER * SCALE) / CELL_SIZE / SCALE;
    int y = (position.y - PALLET_BORDER * SCALE) / CELL_SIZE / SCALE;

    if (x < 0 || y > ceil((textures.size() + 1) / 2)) {
        return -1;
    }

    if (x + y * 2 >= (int) textures.size()) {
        return -1;
    }

    return x + y * 2;
}

void Pallet::unloadTextures() {
    for (const auto& pair : textures) {
        UnloadTexture(*pair.second);
    }
}

void Pallet::renderPallet() const {
    int i = 0;

    DrawRectangle(
        WIDTH - CELL_SIZE * SCALE * 2 - PALLET_BORDER * SCALE * 2,
        0,
        CELL_SIZE * SCALE * 2 + PALLET_BORDER * SCALE * 2,
        CELL_SIZE * SCALE * ceil((textures.size() + 1) / 2) + PALLET_BORDER * SCALE * 2,
        WHITE
    );

    for (const auto& pair : textures) {
        DrawTexturePro(
            *pair.second,
            {
                0 * CELL_SIZE,
                3 * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE
            },
            {
                WIDTH + CELL_SIZE * SCALE * (i % 2) -  CELL_SIZE * SCALE * 2 - PALLET_BORDER * SCALE,
                CELL_SIZE * SCALE * (i - i % 2) / 2 + PALLET_BORDER * SCALE,
                CELL_SIZE * SCALE,
                CELL_SIZE * SCALE
            },
            {
                0.0f,
                0.0f
            },
            0.0f,
            WHITE
        );

        i++;
    }
}

Vector2 Pallet::getImageSourcePosition(const std::array<int, 4>& keys) const {
    static const std::map<std::array<int, 4>, Vector2> mapping = {
        {{ 0, 0, 0, 0 }, { 2, 1 }},
        {{ 1, 1, 1, 1 }, { 0, 3 }},

        {{ 0, 0, 0, 1 }, { 2, 2 }},
        {{ 0, 0, 1, 0 }, { 3, 1 }},
        {{ 0, 1, 0, 0 }, { 2, 0 }},
        {{ 1, 0, 0, 0 }, { 1, 1 }},

        {{ 1, 1, 0, 0 }, { 3, 0 }},
        {{ 0, 0, 1, 1 }, { 1, 2 }},
        {{ 0, 1, 1, 0 }, { 3, 2 }},
        {{ 1, 0, 0, 1 }, { 1, 0 }},

        {{ 1, 1, 1, 0 }, { 0, 0 }},
        {{ 1, 1, 0, 1 }, { 1, 3 }},
        {{ 1, 0, 1, 1 }, { 0, 2 }},
        {{ 0, 1, 1, 1 }, { 3, 3 }},

        {{ 0, 1, 0, 1 }, { 0, 1 }},
        {{ 1, 0, 1, 0 }, { 2, 3 }},
    };

    return mapping.find(keys)->second;
    
}

void Pallet::drawTile(int x, int y, int key, const std::array<int, 4>& keys) const {
    Vector2 sourceImagePosition = getImageSourcePosition(keys);

    DrawTexturePro(
        *getTexture(key),
        {
            sourceImagePosition.x * CELL_SIZE,
            sourceImagePosition.y * CELL_SIZE,
            CELL_SIZE,
            CELL_SIZE
        },
        {
            x * CELL_SIZE * SCALE,
            y * CELL_SIZE * SCALE,
            CELL_SIZE * SCALE,
            CELL_SIZE * SCALE
        },
        {
            0.0f,
            0.0f
        },
        0.0f,
        WHITE
    );
}
