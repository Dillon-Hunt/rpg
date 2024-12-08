#include "Pallet.h"

#include "utils/config.h"

void Pallet::load() {
    add(
        EMPTY_TEXTURE,
        std::make_shared<PalletEntry>(
            "resources/empty.png.png",
            TILE,
            LoadTexture("resources/empty.png"),
            false,
            Rectangle { }
        )
    );

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
}

Asset Pallet::getAssetFromTile(Tile id) {
    static const std::map<Tile, Asset> mapping = {
        { FENCE, FENCE_TEXTURE },
        { CHEST, CHEST_TEXTURE },
        { CAMPFIRE, CAMPFIRE_TEXTURE },
        { PLAYER, PLAYER_TEXTURE },
        { NPC_1, NPC_1_TEXTURE }
    };

    auto it = mapping.find(id);

    if (it != mapping.end()) {
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
