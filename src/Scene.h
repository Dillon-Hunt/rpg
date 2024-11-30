#ifndef SCENE_H
#define SCENE_H

#include "game-objects/objects/TiledObject.h"
#include "game-objects/entities/Player.h"
#include "EventManager.h"
#include "Pallet.h"
#include "Chunk.h"

#include <map>
#include <utility>
#include <memory>

class Scene {
    private:
        int id;
        bool night;
        bool active;
        std::shared_ptr<Player> player;
        std::map<std::pair<int, int>, std::shared_ptr<Chunk>> chunks;

    public:
        Scene(int id, std::shared_ptr<Player> player) : id(id), night(false), active(false), player(player) {
            EventManager::get().addListener<Scene, std::pair<Point, Tile>>(
                PLACE_TILE,
                this,
                [this](std::pair<Point, Tile> data) {
                    if (active) {
                        setTile(data.first, data.second);
                    }
                }
            );

            EventManager::get().addListener<Scene, std::pair<Point, Tile>>(
                PLACE_OBJECT,
                this,
                [this](std::pair<Point, Tile> data) {
                    if (active) {
                        placeObject<Object>(data.first, data.second);
                    }
                }
            );

            EventManager::get().addListener<Scene, std::pair<Point, Tile>>(
                PLACE_TILED_OBJECT,
                this,
                [this](std::pair<Point, Tile> data) {
                    if (active) {
                        placeObject<TiledObject>(data.first, data.second);
                    }
                }
            );
        }

        int getID() const;

        void activate();

        void deactivate();

        void setTile(Point p, Tile tile);

        template <typename T>
        void placeObject(Point p, Tile object) {
            Point position = GridPositionToChunkPosition(p); 
           
            getChunk({ position.x, position.y })->placeObject<T>(p.x - position.x * CHUNK_SIZE, p.y - position.y * CHUNK_SIZE, object);
        }

        std::shared_ptr<Chunk> getChunk(Point position);

        void loadChunk(std::pair<int, int>& position);

        void loadChunks(Point origin);

        void update();

        void draw();

        ~Scene() {}
};

#endif // SCENE_H
