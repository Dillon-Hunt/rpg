#include "Pallet.h"

#include "Config.h"

void Pallet::loadTexture(int key, const char* path, bool isBase) {
    if (isBase) countBase++;
    textures.emplace(key, std::make_pair(std::make_unique<Texture2D>(LoadTexture(path)), isBase));
}

const std::shared_ptr<Texture2D> Pallet::getTexture(int key) const {
    return textures.at(key).first;
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

    return x + y * 2 + 1;
}

void Pallet::unloadTextures() {
    for (const auto& pair : textures) {
        UnloadTexture(*pair.second.first);
    }
}

void Pallet::renderPallet() const {
    int i = 0;

    DrawRectangle(
        WIDTH - CELL_SIZE * SCALE * 2 - PALLET_BORDER * SCALE * 2,
        0,
        CELL_SIZE * SCALE * 2 + PALLET_BORDER * SCALE * 2,
        CELL_SIZE * SCALE * ceil((countBase + 1) / 2) + PALLET_BORDER * SCALE * 2,
        WHITE
    );

    for (const auto& pair : textures) {
        if (pair.second.second) {
            DrawTexturePro(
                *pair.second.first,
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
}

IntPair Pallet::getMinMax(const std::array<int, 4>& keys) const {
    IntPair result;

    result.min = *std::min_element(keys.begin(), keys.end());
    result.max = *std::max_element(keys.begin(), keys.end());

    if (result.min == result.max) result.min = GRASS;

    return result;
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

    IntPair limits = getMinMax(keys);

    std::array<int, 4> limited = { 0, 0, 0, 0 };

    if (limited != keys) {
        for (int i = 0; i < 4; i++) {
            if (keys[i] == limits.max) {
                limited[i] = 1;
            }
        }
    }

    return mapping.find(limited)->second;
    
}

const std::shared_ptr<Texture2D> Pallet::getTileTexture(const std::array<int, 4>& keys) const {
    IntPair limits = getMinMax(keys);
    std::array<int, 2> key = { limits.min, limits.max };

    static const std::map<std::array<int, 2>, int> mapping = {
        {{ GRASS, GRASS }, GRASS_DIRT },
        {{ GRASS, DIRT }, GRASS_DIRT },
        {{ GRASS, WATER }, GRASS_WATER },
        {{ GRASS, GARDEN }, GRASS_GARDEN },
        {{ DIRT, WATER }, DIRT_WATER }
    };

    auto it = mapping.find(key);

    if (it == mapping.end()) return getTexture(GRASS_DIRT);
    return getTexture(it->second);

}

void Pallet::drawTile(int x, int y, const std::array<int, 4>& keys) const {
    Vector2 sourceImagePosition = getImageSourcePosition(keys);

    DrawTexturePro(
        *getTileTexture(keys),
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
