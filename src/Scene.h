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

/**
 * Stores data regarding a scene such as entities, chunks and state
 */
class Scene {
    private:
        int id;
        bool night;
        bool active;
        std::shared_ptr<Player> player;
        std::map<std::pair<int, int>, std::shared_ptr<Chunk>> chunks;

    public:
        /**
         * Creates a new scene
         */
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

        /**
         * Retrives the scene's id
         */
        int getID() const;

        /**
         * Sets the scene to active
         */
        void activate();

        /**
         * Deactivates the scene
         */
        void deactivate();

        /**
         * Handle's clicks
         *
         * @param gridPosition the position of the tile clicked
         * @returns true iff the click was handled
         */
        bool clickHandler(const Point& gridPosition);

        /**
         * Sets a tile
         *
         * @param p the position of the tile to update
         * @param tile to update it to
         */
        void setTile(const Point& p, Tile tile);

        /**
         * Places an object in the scene
         *
         * @param p the position of the object
         * @param object the object to add
         */
        template <typename T>
        void placeObject(Point p, Tile object) {
            Point position = GridPositionToChunkPosition(p); 
            getChunk(position)->placeObject<T>(p.x - position.x * CHUNK_SIZE, p.y - position.y * CHUNK_SIZE, object);
        }

        /**
         * Retives a particular chunk
         *
         * @param position of the chunk
         * @returns the chunk
         */
        std::shared_ptr<Chunk> getChunk(Point& position);

        /**
         * Loads or creates a chunk at a given position
         *
         * @param
         */
        void loadChunk(std::pair<int, int>& position);

        /**
         * Loads chunks around a point
         *
         * @param origin the centre chunk to load outwards from
         */
        void loadChunks(Point origin);

        /**
         * Updates scene
         */
        void update();

        /**
         * Checks for collisions
         */
        void checkCollisions();

        /**
         * Draws the scene
         */
        void draw();

        /**
         * Deconstructs the scene
         */
        ~Scene() {}
};

#endif // SCENE_H
