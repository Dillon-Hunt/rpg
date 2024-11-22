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
        std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks;
        Pallet& pallet;

    public:
        Chunk(int x, int y, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks, Pallet& pallet) : x(x), y(y), chunks(chunks), pallet(pallet) {
            std::memset(keys, GRASS_DIRT, sizeof(keys));
        };

        void renderPallet() const;

        int getTextureFromPallet() const;

        // void load(const char* path);

        void unset(int x, int y);

        int getKey(int col, int row) const;

        int getTexture(int col, int row) const;

        void setTexture(int col, int row, int key);

        void set(int x, int y, int key);

        void draw() const;

        void unloadTextures();
};

#endif // CHUNK_H
