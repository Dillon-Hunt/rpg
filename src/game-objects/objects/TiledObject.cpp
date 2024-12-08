#include "TiledObject.h"

#include "../../utils/config.h"
#include "../../Chunk.h"

void TiledObject::update() {
    Object::draw();
}

Point TiledObject::getObjectSource() const {
    Point gridPosition = Vector2ToGridPosition(position);
    Point chunkPosition = GridPositionToChunkPosition(gridPosition);
    Point relativePosition = { gridPosition.x - chunkPosition.x * CHUNK_SIZE, gridPosition.y - chunkPosition.y * CHUNK_SIZE };

    static const std::map<std::array<int, 4>, Point> mapping = {
        // NORTH, EAST, SOUTH, WEST
        {{ 0, 0, 0, 0 }, { 0, 0 }},
        {{ 0, 0, 0, 1 }, { 3, 0 }},
        {{ 0, 0, 1, 0 }, { 0, 1 }},
        {{ 0, 0, 1, 1 }, { 3, 1 }},
        {{ 0, 1, 0, 0 }, { 1, 0 }},
        {{ 0, 1, 0, 1 }, { 2, 0 }},
        {{ 0, 1, 1, 0 }, { 1, 1 }},
        {{ 0, 1, 1, 1 }, { 2, 1 }},
        {{ 1, 0, 0, 0 }, { 0, 3 }},
        {{ 1, 0, 0, 1 }, { 3, 3 }},
        {{ 1, 0, 1, 0 }, { 0, 2 }},
        {{ 1, 0, 1, 1 }, { 3, 2 }},
        {{ 1, 1, 0, 0 }, { 1, 3 }},
        {{ 1, 1, 0, 1 }, { 2, 3 }},
        {{ 1, 1, 1, 0 }, { 1, 2 }},
        {{ 1, 1, 1, 1 }, { 2, 2 }},
    };

    std::array<int, 4> key = { 0, 0, 0, 0 };

    std::shared_ptr<Chunk> chunk = parent.lock();

    if (std::shared_ptr<Object> obj = chunk->getObject({relativePosition.x, relativePosition.y - 1}); obj != nullptr && obj->getID() == id) key[0] = 1;
    if (std::shared_ptr<Object> obj = chunk->getObject({relativePosition.x + 1, relativePosition.y}); obj != nullptr && obj->getID() == id) key[1] = 1;
    if (std::shared_ptr<Object> obj = chunk->getObject({relativePosition.x, relativePosition.y + 1}); obj != nullptr && obj->getID() == id) key[2] = 1;
    if (std::shared_ptr<Object> obj = chunk->getObject({relativePosition.x - 1, relativePosition.y}); obj != nullptr && obj->getID() == id) key[3] = 1;

    return mapping.find(key)->second;    
}

void TiledObject::draw() const {
    Point sourcePosition = getObjectSource();

    DrawTexturePro(
        *texture,
        {
            (float) sourcePosition.x * TILE_SIZE,
            (float) sourcePosition.y * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE
        },
        {
            position.x,
            position.y,
            TILE_SIZE,
            TILE_SIZE
        },
        {
            TILE_SIZE / 2.0f,
            TILE_SIZE /2.0f
        },
        0.0f,
        WHITE
    );

    GameObject::draw();
}
