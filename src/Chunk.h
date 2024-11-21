#ifndef CHUNK_H
#define CHUNK_H

#include "Pallet.h"
#include "Tile.h"

#include "Config.h"

#include <map>

class Chunk {
    private:
        int x;
        int y;
        Tile tiles[CHUNK_SIZE][CHUNK_SIZE];
        int keys[CHUNK_SIZE][CHUNK_SIZE];
        int textures[CHUNK_SIZE][CHUNK_SIZE];

    public:
        Chunk(int x, int y) : x(x), y(y) {
            std::memset(keys, GRASS_DIRT, sizeof(keys));
            std::memset(textures, GRASS_DIRT, sizeof(textures));
        };

        void renderPallet() const;

        int getTextureFromPallet() const;

        // void load(const char* path);

        void unset(int x, int y);

        void setTexture(int col, int row, int key);

        int getKey(int col, int row, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks) const;

        int getTexture(int col, int row, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks) const;

        void set(int x, int y, int key, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks);

        void draw(const Pallet& pallet, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks) const;

        void unloadTextures();
};

#endif // CHUNK_H
