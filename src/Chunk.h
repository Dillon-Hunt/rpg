#ifndef CHUNK_H
#define CHUNK_H

#include "Config.h"

#include "Pallet.h"
#include "Entity.h"

#include <map>

struct Collidable {
    Texture texture;
    Rectangle collider;
};

class Chunk {
    private:
        int x;
        int y;

        std::vector<Collidable> availibleGameObjects;

        int tileTexture[CHUNK_SIZE][CHUNK_SIZE];
        int gameObjects[CHUNK_SIZE][CHUNK_SIZE];

        std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks;
        Pallet& pallet;

    public:
        Chunk(int x, int y, std::map<std::pair<int, int>, std::unique_ptr<Chunk>>& chunks, Pallet& pallet) : x(x), y(y), chunks(chunks), pallet(pallet) {
            std::memset(tileTexture, GRASS_DIRT, sizeof(tileTexture));
            std::memset(gameObjects, NONE, sizeof(gameObjects));

            availibleGameObjects.push_back({
                LoadTexture(FENCE_TEXTURE_PATH),
                { 6, 8, 12, 12 }
            });
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

        bool checkCollision(const Entity& entity) const {
            for (int col = 0; col < CHUNK_SIZE; col++) {
                for (int row = 0; row < CHUNK_SIZE; row++) {
                    if (gameObjects[col][row] == NONE) continue;

                    Collidable gameObject = availibleGameObjects.at(gameObjects[col][row]);

                    if (CheckCollisionRecs(
                        {
                            ((col + x * CHUNK_SIZE) * CELL_SIZE + gameObject.collider.x) * SCALE,
                            ((row + y * CHUNK_SIZE) * CELL_SIZE + gameObject.collider.y) * SCALE,
                            gameObject.collider.width * SCALE,
                            gameObject.collider.height * SCALE
                        },
                        entity.getCollisionShape())
                    ) {
                        return true;
                    }
                }
            }

            return false;
        };

        void unloadTextures();
};

#endif // CHUNK_H
