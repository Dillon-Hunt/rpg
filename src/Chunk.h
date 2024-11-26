#ifndef CHUNK_H
#define CHUNK_H

#include "utils/grid.h"
#include "utils/config.h"
#include "game-objects/Object.h"

#include <map>
#include <memory>
#include <utility>
#include <optional>

class Chunk {
    private:
        Point position;
        int tiles[CHUNK_SIZE * CHUNK_SIZE];
        std::shared_ptr<std::map<std::pair<int, int>, std::shared_ptr<Chunk>>> chunks;
        std::map<std::pair<int, int>, std::shared_ptr<Object>> objects;

        Texture2D getTileTexture(const std::pair<int, int>& limits) const;

        Rectangle getTileSource(const std::array<int, 4>& key) const;

    public:
        Chunk(Point position, std::shared_ptr<std::map<std::pair<int, int>, std::shared_ptr<Chunk>>> chunks) : position(position), chunks(chunks) {
            std::memset(tiles, GRASS, sizeof(tiles));
        }

        int getTile(int x, int y) const;

        std::optional<std::shared_ptr<Object>> getObject(int x, int y);

        void setTile(int x, int y, int id);

        void placeObject(int x, int y, int id);

        void drawTile(int x, int y) const;

        void drawTiles() const;

        void drawObjects() const;

        void update();

        ~Chunk() {}
};

#endif // CHUNK_H
