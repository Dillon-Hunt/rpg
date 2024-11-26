#ifndef PALLET_H
#define PALLET_H

#include "raylib.h"

#include <map>
#include <memory>
#include <string>
#include <iostream>

// Tiles

#define GRASS_DIRT 0
#define GRASS_WATER 1
#define GRASS_GARDEN 2
#define DIRT_WATER 3
#define GRASS_ROAD 4

// Objects

#define FENCE 5

// Entities

#define PLAYER 6
#define NPC_1 7

enum PalletType {
    TILE,
    OBJECT,
    ENTITY
};

struct PalletEntry {
    int id;
    std::string name;
    PalletType type;
    Texture2D texture;
    bool collidable;
    Rectangle collider;

    PalletEntry(int id, std::string name, PalletType type, Texture2D texture, bool collidable, Rectangle collider)
        : id(id), name(name), type(type), texture(texture), collidable(collidable), collider(collider) {
        std::cout << "Loading Texture: " << name << std::endl;
    }

    ~PalletEntry() {
        std::cout << "Unloading texture: " << name << std::endl;
        UnloadTexture(texture);
    }
};

class Pallet {
    private:
        std::map<int, std::shared_ptr<PalletEntry>> entries;

        Pallet() = default;

        ~Pallet() = default;


    public:
        static Pallet& get() {
            static Pallet instance;
            return instance;
        }

        void load();

        void add(int id, std::shared_ptr<PalletEntry> entry);

        Texture2D& getTexture(int id);

        std::vector<std::shared_ptr<PalletEntry>> getTextures(PalletType type);

        Rectangle& getColider(int id);
};

#endif // PALLET_H
