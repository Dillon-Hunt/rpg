#ifndef CHUNK_H
#define CHUNK_H

#include "Config.h"

#include "Pallet.h"

#include <map>

class Chunk {
    private:
        int x;
        int y;

        std::vector<Texture2D> gameObjectTextures;

        int tileTexture[CHUNK_SIZE][CHUNK_SIZE];
        int gameObjectTexture[CHUNK_SIZE][CHUNK_SIZE];

        std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks;
        Pallet& pallet;

    public:
        Chunk(int x, int y, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks, Pallet& pallet) : x(x), y(y), chunks(chunks), pallet(pallet) {
            std::memset(tileTexture, GRASS_DIRT, sizeof(tileTexture));
            std::memset(gameObjectTexture, NONE, sizeof(gameObjectTexture));

            gameObjectTextures.push_back(LoadTexture(FENCE_TEXTURE_PATH));
        };

        void renderPallet() const;

        int getTextureFromPallet() const;

        // void load(const char* path);

        void unset(int x, int y);

        int getTileTexture(int col, int row) const;

        int getGameObjectTexture(int col, int row) const;

        void set(int x, int y, int key);

        void place(int x, int y, int key);

        void drawTiles() const;

        Vector2 getGameObjectSourcePosition(const std::array<int, 4>& keys, int key) const;

        void drawGameObjects() const;

        void draw() const;

        void unloadTextures();
};

#endif // CHUNK_H
