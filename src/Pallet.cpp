#include "Pallet.h"

#include "utils/config.h"

#include <iostream>

void Pallet::load() {

    // Default
    tiles.insert_or_assign(NONE, EMPTY_TEXTURE);
    add(
        EMPTY_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/empty.png",
            SINGLE_TILE,
            LoadTexture("resources/empty.png"),
            false,
            Rectangle { }
        )
    );

    // GRASS
    tiles.insert_or_assign(GRASS, GRASS_TEXTURE);
    add(
        GRASS_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/grass.png",
            SINGLE_TILE,
            LoadTexture("resources/grass.png"),
            false,
            Rectangle { }
        )
    );

    // DIRT
    tiles.insert_or_assign(DIRT, GRASS_DIRT_TEXTURE);
    add(
        GRASS_DIRT_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/grass-dirt.png",
            TILE,
            LoadTexture("resources/grass-dirt.png"),
            false,
            Rectangle { }
        )
    );

    // Water
    tiles.insert_or_assign(WATER, GRASS_WATER_TEXTURE);
    add(
        GRASS_WATER_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/grass-water.png",
            TILE,
            LoadTexture("resources/grass-water.png"),
            false,
            Rectangle { }
        )
    );

    // Garden
    tiles.insert_or_assign(GARDEN, GRASS_GARDEN_TEXTURE);
    add(
        GRASS_GARDEN_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/grass-garden.png",
            TILE,
            LoadTexture("resources/grass-garden.png"),
            false,
            Rectangle { }
        )
    );

    // Road
    tiles.insert_or_assign(ROAD, GRASS_ROAD_TEXTURE);
    add(
        GRASS_ROAD_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/grass-road.png",
            TILE,
            LoadTexture("resources/grass-road.png"),
            false,
            Rectangle { }
        )
    );

    add(
        DIRT_WATER_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/dirt-water.png",
            TILE,
            LoadTexture("resources/dirt-water.png"),
            false,
            Rectangle { }
        )
    );

    // Fence
    tiles.insert_or_assign(FENCE, FENCE_TEXTURE);
    add(
        FENCE_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/fence.png",
            TILED_OBJECT,
            LoadTexture("resources/fence.png"),
            true,
            Rectangle { 8, 3, 8, 17 }
        )
    );

    // Chest
    tiles.insert_or_assign(CHEST, CHEST_TEXTURE);
    add(
        CHEST_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/chest.png",
            OBJECT,
            LoadTexture("resources/chest.png"),
            true,
            Rectangle { 1, 14, TILE_SIZE - 2, 10 }
        )
    );

    // Campfire
    tiles.insert_or_assign(CAMPFIRE, CAMPFIRE_TEXTURE);
    add(
        CAMPFIRE_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/campfire.png",
            OBJECT,
            LoadTexture("resources/campfire.png"),
            true,
            Rectangle { 0, 12, TILE_SIZE, 12 }
        )
    );

    // Player
    tiles.insert_or_assign(PLAYER, PLAYER_TEXTURE);
    add(
        PLAYER_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/player.png",
            ENTITY,
            LoadTexture("resources/player.png"),
            true,
            Rectangle { 3, -8, 18, 10 }
        )
    );

    // NPC 1
    tiles.insert_or_assign(NPC_1, NPC_1_TEXTURE);
    add(
        NPC_1_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/npc1.png",
            ENTITY,
            LoadTexture("resources/npc1.png"),
            true,
            Rectangle { 0, 0, TILE_SIZE, TILE_SIZE * 2 }
        )
    );
}

void Pallet::add(Asset id, std::shared_ptr<PalletEntry> entry) {
    entries.emplace(id, entry);

    auto it = counts.find(entry->type);

    if (it != counts.end()) {
        it->second++;
    }

    counts.emplace(entry->type, 1);
}

Asset Pallet::getAssetFromTile(Tile id) {
    auto it = tiles.find(id);

    if (it != tiles.end()) {
        return it->second;
    }

    return FENCE_TEXTURE;
}

const Texture2D* Pallet::getTexture(Asset id) const {
    return &entries.at(id)->texture;
}

const std::vector<std::shared_ptr<PalletEntry>> Pallet::getTextures(PalletType type) const {
    std::vector<std::shared_ptr<PalletEntry>> textures;

    for (const std::pair<const Asset, std::shared_ptr<PalletEntry>>& entry : entries) {
        if (entry.second->type == type) {
            textures.push_back(entry.second);
        }
    }

    return textures;
}

bool Pallet::isCollidable(Asset id) const {
    return entries.at(id)->collidable;
}

const Rectangle& Pallet::getColider(Asset id) const {
    return entries.at(id)->collider;
}

bool Pallet::clickHandler(Vector2& mousePosition) {
    if (
        mousePosition.x > WINDOW_PADDING &&
        mousePosition.x < WINDOW_PADDING + (counts.at(TILE) - 1) * TILE_SIZE * SCALE &&
        mousePosition.y > WINDOW_PADDING &&
        mousePosition.y < WINDOW_PADDING + TILE_SIZE * SCALE
    ) {
        std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
        return true;
    }

    return false;
}

void Pallet::draw() const {

    int i = 0;

    DrawRectangle(
        WINDOW_PADDING - 5,
        WINDOW_PADDING - 5,
        (counts.at(TILE) + counts.at(SINGLE_TILE) - 1) * TILE_SIZE * SCALE + 10,
        TILE_SIZE * SCALE + 10,
        WHITE
    );

    for (const auto& it : tiles) {
        std::shared_ptr<PalletEntry> entry = entries.at(it.second);

        if (entry->type == TILE || entry->type == SINGLE_TILE) {
            DrawTexturePro(
                entry->texture,
                {
                    0,
                    (float) (entry->type == TILE ? 3 * TILE_SIZE : 0),
                    TILE_SIZE,
                    TILE_SIZE
                },
                {
                    WINDOW_PADDING + i * TILE_SIZE * SCALE,
                    WINDOW_PADDING,
                    TILE_SIZE * SCALE,
                    TILE_SIZE * SCALE
                },
                {
                    0,
                    0
                },
                0.0f,
                WHITE
            );
        }

        i++;
    }
}
