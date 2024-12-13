#ifndef CHUNK_H
#define CHUNK_H

#include "utils/grid.h"
#include "utils/config.h"
#include "game-objects/Object.h"
#include "game-objects/objects/Light.h"
#include "game-objects/objects/TiledObject.h"
#include "Database.h"
#include "Pallet.h"

#include <map>
#include <memory>
#include <utility>
#include <thread>

class Scene;

class Chunk : public std::enable_shared_from_this<Chunk> {
    private:
        int chunk_id;
        Point position;
        Scene& scene;
        Tile tiles[CHUNK_SIZE * CHUNK_SIZE];
        std::map<Point, std::shared_ptr<Object>> objects;

        const Texture2D* getTileTexture(const std::pair<Tile, Tile>& limits) const;

        Rectangle getTileSource(const std::array<int, 4>& key) const;

    public:
        /**
         * Constructs a new Chunk instance, defaulting all tiles to NONE
         *
         * @param chunk_id the id specified by the sqlite database
         * @param position the chunk position
         * @param Scene the scene that the chunk is in
         */
        Chunk(int chunk_id, Point position, Scene& scene) : chunk_id(chunk_id), position(position), scene(scene) {
            std::memset(tiles, 0, sizeof(tiles));
        }

        /**
         * Loads chunk data from the sqlite database
         *
         * Retrives tiles and objects from the database and updates chunk state
         */
        void load() {
            auto self = shared_from_this();

            // Loads tiles in a separate thread
            std::thread loadTiles([self]() {
                std::vector<TileDB> tileData = Database::get().getTiles(self->chunk_id);

                for (TileDB& tile : tileData) {
                    self->setTileLocal(tile.x, tile.y, tile.type);
                }
            });

            // Load objects in a separate thread
            std::thread loadObjects([self]() {
                std::vector<ObjectDB> objectData = Database::get().getObjects(self->chunk_id);

                for (ObjectDB& object : objectData) {
                    switch (object.type) {
                        case FENCE:
                            self->placeObjectLocal<TiledObject>(object.x, object.y, object.type);
                            break;
                        case CHEST:
                        case CAMPFIRE:
                            self->placeObjectLocal<Object>(object.x, object.y, object.type);
                            break;
                        default:
                            break;
                    }
                }
            });

            // Detach threads
            loadTiles.detach();
            loadObjects.detach();
        }

        /**
         * Retrives the tile at the given coordinates relative to the chunk
         *
         * @param x the x-coordinates relative to the chunk
         * @param y the y-coordinates relative to the chunk
         * @returns the tile at the given coordinates
         */
        Tile getTile(int x, int y) const;

        /**
         * Retrives the object at the given coordinates relative to the chunk
         *
         * @param x the x-coordinates relative to the chunk
         * @param y the y-coordinates relative to the chunk
         * @returns a shared_ptr to an object at the given coordinates
         */
        std::shared_ptr<Object> getObject(Point p);

        /**
         * Sets the tile at the given position without updating database
         *
         * @param x the x-coordinates relative to the chunk
         * @param y the y-coordinates relative to the chunk
         * @param id the tile to set
         */
        void setTileLocal(int x, int y, Tile id);

        /**
         * Sets the tile at the given position and updates sqlite database
         *
         * @param x the x-coordinates relative to the chunk
         * @param y the y-coordinates relative to the chunk
         * @param id the tile to set
         */
        void setTile(int x, int y, Tile id);

        /**
         * Sets the object at the given position without updating database
         *
         * @param x the x-coordinates relative to the chunk
         * @param y the y-coordinates relative to the chunk
         * @param id the object tile to set
         */
        template <typename T>
        void placeObjectLocal(int x, int y, Tile id) {
            std::shared_ptr<Object> object = std::make_shared<T>(
                Pallet::get().getAssetFromTile(id),
                Vector2 {
                    (float) (position.x * CHUNK_SIZE + x) * TILE_SIZE,
                    (float) (position.y * CHUNK_SIZE + y) * TILE_SIZE
                },
                shared_from_this()
            );

            switch (id) {
                case CAMPFIRE: {
                    std::shared_ptr<GameObject> campfire = std::make_shared<Light>(
                        EMPTY_TEXTURE,
                        Vector2 {
                            (float) (position.x * CHUNK_SIZE + x) * TILE_SIZE,
                            (float) (position.y * CHUNK_SIZE + y) * TILE_SIZE
                        },
                        100,
                        shared_from_this()
                    );

                    object->addChild(campfire);

                    break;
                }
                default:
                    break;
            }

            objects.insert_or_assign(Point { x, y }, object);
        }

        /**
         * Sets the object at the given position and updates sqlite database
         *
         * @param x the x-coordinates relative to the chunk
         * @param y the y-coordinates relative to the chunk
         * @param id the object tile to set
         */
        template <typename T>
        void placeObject(int x, int y, Tile id) {
            Database::get().createObject(chunk_id, x, y, id);

            placeObjectLocal<T>(x, y, id);
        }

        /**
         * Get all objects
         *
         * @returns a map of objects mapping points to an object
         */
        std::map<Point, std::shared_ptr<Object>> getObjects();

        /**
         * Draws the tile at the given relative coordinates
         *
         * @param x the x-coordinates relative to the chunk
         * @param y the y-coordinates relative to the chunk
         */
        void drawTile(int x, int y) const;

        /**
         * Draws all tiles
         */
        void drawTiles() const;

        /**
         * Draws all objects
         */
        void drawObjects() const;

        /**
         * Updates all objects in chunk
         */
        void update();

        /**
         * Deconstructor for Chunk
         */
        ~Chunk() {}
};

#endif // CHUNK_H
