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

        Texture2D getTileTexture(const std::pair<Tile, Tile>& limits) const;

        Rectangle getTileSource(const std::array<int, 4>& key) const;

    public:
        Chunk(int chunk_id, Point position, Scene& scene) : chunk_id(chunk_id), position(position), scene(scene) {
            std::memset(tiles, GRASS, sizeof(tiles));
        }

        void load() {
            auto self = shared_from_this();

            std::thread loadTiles([self]() {
                std::vector<TileDB> tileData = Database::get().getTiles(self->chunk_id);

                for (TileDB& tile : tileData) {
                    self->setTileLocal(tile.x, tile.y, tile.type);
                }
            });

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

            loadTiles.detach();
            loadObjects.detach();
        }

        Tile getTile(int x, int y) const;

        std::shared_ptr<Object> getObject(Point p);

        void setTileLocal(int x, int y, Tile id);

        void setTile(int x, int y, Tile id);

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

        template <typename T>
        void placeObject(int x, int y, Tile id) {
            Database::get().createObject(chunk_id, x, y, id);

            placeObjectLocal<T>(x, y, id);
        }

        std::map<Point, std::shared_ptr<Object>> getObjects();

        void drawTile(int x, int y) const;

        void drawTiles() const;

        void drawObjects() const;

        void update();

        ~Chunk() {}
};

#endif // CHUNK_H
