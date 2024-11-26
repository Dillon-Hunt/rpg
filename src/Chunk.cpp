#include "Chunk.h"

#include "game-objects/objects/TiledObject.h"
#include "Pallet.h"

#include <array>

int Chunk::getTile(int x, int y) const {
    if (x == -1) return chunks->at(std::make_pair(position.x - 1, position.y))->getTile(CHUNK_SIZE - 1, y);
    if (x == CHUNK_SIZE) return chunks->at(std::make_pair(position.x + 1, position.y))->getTile(0, y);
    if (y == -1) return chunks->at(std::make_pair(position.x, position.y - 1))->getTile(x, CHUNK_SIZE - 1);
    if (y == CHUNK_SIZE) return chunks->at(std::make_pair(position.x, position.y + 1))->getTile(x, 0);
    return tiles[x + y * CHUNK_SIZE];
}

std::optional<std::shared_ptr<Object>> Chunk::getObject(int x, int y) {
    if (x == -1) return chunks->at(std::make_pair(position.x - 1, position.y))->getObject(CHUNK_SIZE - 1, y);
    if (x == CHUNK_SIZE) return chunks->at(std::make_pair(position.x + 1, position.y))->getObject(0, y);
    if (y == -1) return chunks->at(std::make_pair(position.x, position.y - 1))->getObject(x, CHUNK_SIZE - 1);
    if (y == CHUNK_SIZE) return chunks->at(std::make_pair(position.x, position.y + 1))->getObject(x, 0);
    auto it = objects.find(std::make_pair(x, y));

    if (it == objects.end()) {
        return std::nullopt;
    }

    return it->second;
}

void Chunk::setTile(int x, int y, int id) {
    tiles[x + y * CHUNK_SIZE] = id;
}

void Chunk::placeObject(int x, int y, int id) {
    objects.emplace(std::make_pair(x, y), std::make_shared<TiledObject>(
        id,
        Vector2 {
            (float) (position.x * CHUNK_SIZE + x) * TILE_SIZE,
            (float) (position.y * CHUNK_SIZE + y) * TILE_SIZE
        },
        Pallet::get().getTexture(id),
        chunks->at({ position.x, position.y })
    ));
}


Texture2D Chunk::getTileTexture(const std::pair<int, int>& limits) const {
    static const std::map<std::pair<int, int>, int> mapping = {
        {{ GRASS, GRASS }, GRASS_DIRT },
        {{ GRASS, DIRT }, GRASS_DIRT },
        {{ GRASS, WATER }, GRASS_WATER },
        {{ GRASS, GARDEN }, GRASS_GARDEN },
        {{ GRASS, ROAD }, GRASS_ROAD },
        {{ DIRT, WATER }, DIRT_WATER }
    };

    auto it = mapping.find(limits);

    if (it == mapping.end()) {
        return Pallet::get().getTexture(GRASS_DIRT);
    }

    return Pallet::get().getTexture(it->second);
}

Rectangle Chunk::getTileSource(const std::array<int, 4>& keys) const {
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

    Vector2 offset = mapping.at(keys);

    return { offset.x * TILE_SIZE, offset.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

}

void Chunk::drawTile(int x, int y) const {
    std::array<int, 4> keys = {
        getTile(x - 1, y - 1),
        getTile(x, y - 1),
        getTile(x, y),
        getTile(x - 1, y),
    };

    std::pair<int, int> limits = { 0, 0 };

    limits.first = *std::min_element(keys.begin(), keys.end());
    limits.second = *std::max_element(keys.begin(), keys.end());

    if (limits.first == limits.second) {
        limits.first = GRASS;
    }

    bool invalid = false;

    for (int& key : keys) {
        if (key == limits.first) {
            key = 0;
        } else if (key == limits.second) {
            key = 1;
        } else {
            key = 0;
            invalid = true;
        }
    }

    DrawTexturePro(
        getTileTexture(limits),
        getTileSource(keys),
        {
            (float) (position.x * CHUNK_SIZE + x) * TILE_SIZE,
            (float) (position.y * CHUNK_SIZE + y) * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
        },
        {
            TILE_SIZE,
            TILE_SIZE
        },
        0.0f,
        invalid ? RED : WHITE

    );
}

void Chunk::drawTiles() const {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            drawTile(x, y);
        }
    }
}

void Chunk::drawObjects() const {
    for (auto pair : objects) {
        pair.second->draw();
    }
}

void Chunk::update() {
    for (auto pair : objects) {
        pair.second->update();
    }
}
