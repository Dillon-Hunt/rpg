#include "Pallet.h"

#include "utils/config.h"

void Pallet::load() {
    add(
        GRASS_DIRT,
        std::make_shared<PalletEntry>(
            GRASS_DIRT,
            "resources/grass-dirt.png",
            TILE,
            LoadTexture("resources/grass-dirt.png"),
            false,
            Rectangle { }
        )
    );

    add(
        GRASS_WATER,
        std::make_shared<PalletEntry>(
            GRASS_WATER,
            "resources/grass-water.png",
            TILE,
            LoadTexture("resources/grass-water.png"),
            false,
            Rectangle { }
        )
    );

    add(
        GRASS_GARDEN,
        std::make_shared<PalletEntry>(
            GRASS_GARDEN,
            "resources/grass-garden.png",
            TILE,
            LoadTexture("resources/grass-garden.png"),
            false,
            Rectangle { }
        )
    );

    add(
        GRASS_ROAD,
        std::make_shared<PalletEntry>(
            GRASS_ROAD,
            "resources/grass-road.png",
            TILE,
            LoadTexture("resources/grass-road.png"),
            false,
            Rectangle { }
        )
    );

    add(
        DIRT_WATER,
        std::make_shared<PalletEntry>(
            DIRT_WATER,
            "resources/dirt-water.png",
            TILE,
            LoadTexture("resources/dirt-water.png"),
            false,
            Rectangle { }
        )
    );

    add(
        FENCE,
        std::make_shared<PalletEntry>(
            FENCE,
            "resources/fence.png",
            OBJECT,
            LoadTexture("resources/fence.png"),
            true,
            Rectangle { 0, 0, TILE_SIZE, TILE_SIZE }
        )
    );

    add(
        PLAYER,
        std::make_shared<PalletEntry>(
            PLAYER,
            "resources/player.png",
            ENTITY,
            LoadTexture("resources/player.png"),
            true,
            Rectangle { 0, 0, TILE_SIZE, TILE_SIZE * 2 }
        )
    );

    add(
        NPC_1,
        std::make_shared<PalletEntry>(
            NPC_1,
            "resources/npc1.png",
            ENTITY,
            LoadTexture("resources/npc1.png"),
            true,
            Rectangle { 0, 0, TILE_SIZE, TILE_SIZE * 2 }
        )
    );
}

void Pallet::add(int id, std::shared_ptr<PalletEntry> entry) {
    entries.emplace(id, entry);
}

Texture2D& Pallet::getTexture(int id) {
    return entries.at(id)->texture;
}

std::vector<std::shared_ptr<PalletEntry>> Pallet::getTextures(PalletType type) {
    std::vector<std::shared_ptr<PalletEntry>> textures;

    for (std::pair<const int, std::shared_ptr<PalletEntry>>& entry : entries) {
        if (entry.second->type == type) {
            textures.push_back(entry.second);
        }
    }

    return textures;
}

Rectangle& Pallet::getColider(int id) {
    return entries.at(id)->collider;
}
