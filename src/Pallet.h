#ifndef PALLET_H
#define PALLET_H

#include "raylib.h"

#include <map>
#include <memory>
#include <string>
#include <iostream>

enum Tile {
    NONE,

    GRASS,
    DIRT,
    WATER,
    GARDEN,
    ROAD,

    FENCE,
    CHEST,
    CAMPFIRE,

    PLAYER,
    NPC_1
};

enum Asset {
    EMPTY_TEXTURE,
    GRASS_TEXTURE,

    GRASS_DIRT_TEXTURE,
    GRASS_WATER_TEXTURE,
    GRASS_GARDEN_TEXTURE,
    DIRT_WATER_TEXTURE,
    GRASS_ROAD_TEXTURE,

    FENCE_TEXTURE,
    CHEST_TEXTURE,
    CAMPFIRE_TEXTURE,

    PLAYER_TEXTURE,
    NPC_1_TEXTURE
};

enum PalletType {
    SINGLE_TILE,
    TILE,
    OBJECT,
    TILED_OBJECT,
    ENTITY
};

struct PalletEntry {
    std::string name;
    PalletType type;
    Texture2D texture;
    bool collidable;
    Rectangle collider;

    PalletEntry(std::string name, PalletType type, Texture2D texture, bool collidable, Rectangle collider)
        : name(name), type(type), texture(texture), collidable(collidable), collider(collider) {
        std::cout << "Loading Texture: " << name << std::endl;
    }

    ~PalletEntry() {
        std::cout << "Unloading texture: " << name << std::endl;
        UnloadTexture(texture);
    }
};

class Pallet {
    private:
        std::map<Tile, Asset> tiles;
        std::map<PalletType, int> counts;
        std::map<Asset, std::shared_ptr<PalletEntry>> entries;

        Pallet() = default;

        ~Pallet() = default;


    public:
        static Pallet& get() {
            static Pallet instance;
            return instance;
        }

        void load();

        void add(Asset id, std::shared_ptr<PalletEntry> entry);

        Asset getAssetFromTile(Tile id);

        const Texture2D* getTexture(Asset id) const;

        const std::vector<std::shared_ptr<PalletEntry>> getTextures(PalletType type) const;

        bool isCollidable(Asset id) const;

        const Rectangle& getColider(Asset id) const;

        bool clickHandler(Vector2 mousePosition);

        void draw() const;
};

#endif // PALLET_H
