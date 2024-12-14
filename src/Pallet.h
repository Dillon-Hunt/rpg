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

/**
 * Structure fore a pallet entry
 */
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

/**
 * Stores a tile pallet
 */
class Pallet {
    private:
        std::map<Tile, Asset> tiles;
        std::map<PalletType, int> counts;
        std::map<Asset, std::shared_ptr<PalletEntry>> entries;

        /**
         * Constructs a pallet instance
         */
        Pallet() = default;

        /**
         * Deconstructs a pallet instance
         */
        ~Pallet() = default;


    public:
        /**
         * Retrives a static pallet instance
         */
        static Pallet& get() {
            static Pallet instance;
            return instance;
        }

        /**
         * Loads pallet textures
         */
        void load();

        /**
         * Adds a pallet entry
         *
         * @param id of the texture
         * @param entry for the texture
         */
        void add(Asset id, std::shared_ptr<PalletEntry> entry);

        /**
         * Retrives an asset from a tile
         *
         * @param id of the asset
         * @returns the asset
         */
        Asset getAssetFromTile(Tile id);

        /**
         * Retrives an assets texture
         *
         * @param id of the asset
         * @returns the asset's texture
         */
        const Texture2D* getTexture(Asset id) const;

        /**
         * Retrives all pallet entries
         *
         * @param type of asset
         * @returns a vector of pallet entries
         */
        const std::vector<std::shared_ptr<PalletEntry>> getTextures(PalletType type) const;

        /**
         * Determines if a asset has a collider
         * 
         * @param id of the asset
         * @returns true iff the asset has a colider
         */
        bool isCollidable(Asset id) const;

        /**
         * Retrives the assets collider
         *
         * @param id of the asset
         * @returns the asset's colider
         */
        const Rectangle& getColider(Asset id) const;

        /**
         * Handles clicks on the pallet
         *
         * @param mousePosition the position of the mouse cursor
         * @return true iff the click was handled
         */
        bool clickHandler(Vector2& mousePosition);

        /**
         * Draw the pallet
         */
        void draw() const;
};

#endif // PALLET_H
