#include "Chunk.h"

#include "Database.h"
#include "Pallet.h"
#include "Scene.h"

#include <array>

Tile Chunk::getTile(int x, int y) const {
    if (x == -1) return scene.getChunk({ position.x - 1, position.y })->getTile(CHUNK_SIZE - 1, y);
    if (x == CHUNK_SIZE) return scene.getChunk({ position.x + 1, position.y })->getTile(0, y);
    if (y == -1) return scene.getChunk({ position.x, position.y - 1 })->getTile(x, CHUNK_SIZE - 1);
    if (y == CHUNK_SIZE) return scene.getChunk({ position.x, position.y + 1 })->getTile(x, 0);
    return tiles[x + y * CHUNK_SIZE];
}

std::shared_ptr<Object> Chunk::getObject(Point p) {
    if (p.x == -1) return scene.getChunk({ position.x - 1, position.y })->getObject({ CHUNK_SIZE - 1, p.y });
    if (p.x == CHUNK_SIZE) return scene.getChunk({ position.x + 1, position.y })->getObject({ 0, p.y });
    if (p.y == -1) return scene.getChunk({ position.x, position.y - 1 })->getObject({ p.x, CHUNK_SIZE - 1 });
    if (p.y == CHUNK_SIZE) return scene.getChunk({ position.x, position.y + 1 })->getObject({ p.x, 0 });

    auto it = objects.find(p);

    if (it == objects.end()) {
        return nullptr;
    }

    return it->second;
}

void Chunk::setTileLocal(int x, int y, Tile id) {
    tiles[x + y * CHUNK_SIZE] = id;
}

void Chunk::setTile(int x, int y, Tile id) {
    Database::get().createTile(chunk_id, x, y, id);
    setTileLocal(x, y, id);
}

std::map<Point, std::shared_ptr<Object>> Chunk::getObjects() {
    return objects;
}


Texture2D Chunk::getTileTexture(const std::pair<Tile, Tile>& limits) const {
    static const std::map<std::pair<Tile, Tile>, Asset> mapping = {
        {{ GRASS, GRASS }, GRASS_DIRT_TEXTURE },
        {{ GRASS, DIRT }, GRASS_DIRT_TEXTURE },
        {{ GRASS, WATER }, GRASS_WATER_TEXTURE },
        {{ GRASS, GARDEN }, GRASS_GARDEN_TEXTURE },
        {{ GRASS, ROAD }, GRASS_ROAD_TEXTURE },
        {{ DIRT, WATER }, DIRT_WATER_TEXTURE }
    };

    auto it = mapping.find(limits);

    if (it == mapping.end()) {
        return Pallet::get().getTexture(GRASS_DIRT_TEXTURE);
    }

    return Pallet::get().getTexture(it->second);
}

Rectangle Chunk::getTileSource(const std::array<int, 4>& key) const {
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

    Vector2 offset = mapping.at(key);

    return { offset.x * TILE_SIZE, offset.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

}

void Chunk::drawTile(int x, int y) const {
    std::array<Tile, 4> values = {
        getTile(x - 1, y - 1),
        getTile(x, y - 1),
        getTile(x, y),
        getTile(x - 1, y),
    };

    std::pair<Tile, Tile> limits = { GRASS, GRASS };

    limits.first = *std::min_element(values.begin(), values.end());
    limits.second = *std::max_element(values.begin(), values.end());

    if (limits.first == limits.second) {
        limits.first = GRASS;
    }

    std::array<int, 4> key = { 0, 0, 0, 0 };

    bool invalid = false;

    for (int i = 0; i < 4; i++) {
        if (values[i] == limits.first) {
            key[i] = 0;
        } else if (values[i] == limits.second) {
            key[i] = 1;
        } else {
            key[i] = 0;
            invalid = true;
        }
    }

    DrawTexturePro(
        getTileTexture(limits),
        getTileSource(key),
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
