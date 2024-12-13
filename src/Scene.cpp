#include "Scene.h"

#include "utils/grid.h"
#include "Database.h"

int Scene::getID() const {
    return id;
}

void Scene::activate() {
    active = true;
}

void Scene::deactivate() {
    active = false;
}

bool Scene::clickHandler(const Point& gridPosition) {
    setTile(gridPosition, NONE);

    return true;
}

void Scene::setTile(Point p, Tile tile) {
    Point position = GridPositionToChunkPosition(p); 
    getChunk(position)->setTile(p.x - position.x * CHUNK_SIZE, p.y - position.y * CHUNK_SIZE, tile);
}

std::shared_ptr<Chunk> Scene::getChunk(Point position) {
    auto it = chunks.find({ position.x, position.y });

    if (it == chunks.end()) {
        loadChunks(position);
    }
    
    return chunks.at({ position.x, position.y });
}

void Scene::loadChunk(std::pair<int, int>& position) {
    ChunkDB data = Database::get().getChunk(position.first, position.second);

    if (!data.exists) {
        data.id = Database::get().createChunk(position.first, position.second);
        data.x = position.first;
        data.y = position.second;
    }

    if (data.id != -1) {
        chunks.emplace(
            position,
            std::make_shared<Chunk>(
                data.id,
                Point {
                    data.x,
                    data.y
                },
                *this
            )
        );
        chunks.at(position)->load();
    }
}

void Scene::loadChunks(Point origin) {
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            std::pair<int, int> position = { origin.x + x, origin.y + y };

            auto iterator = chunks.find(position);

            if (iterator == chunks.end()) {
                loadChunk(position);
            }
        }
    }
}

void Scene::update() {
    Point origin = Vector2ToChunkPosition(player->getPosition());

    // Create chunks if necessary
    loadChunks(origin);

    // Update chunks

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            getChunk({ origin.x + x, origin.y + y })->update();
        }
    }
}

void Scene::checkCollisions() {
    Point origin = Vector2ToChunkPosition(player->getPosition());

    std::vector<std::shared_ptr<GameObject>> objects;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            std::shared_ptr<Chunk> chunk = chunks.at({ origin.x + x, origin.y + y });
            
            for (auto& pair : chunk->getObjects()) {
                objects.push_back(pair.second);
            }
        }
    }

    for (std::shared_ptr<GameObject>& object : objects) {
        Rectangle objectCollider = object->getColider();
        Rectangle collision = GetCollisionRec(player->getColider(), objectCollider);

        if (collision.width != 0 || collision.height != 0) {
            Vector2 position = player->getPosition();
            Vector2 lastDirection = player->getLastDirection();

            int dx = 0;
            int dy = 0;

            if (lastDirection.x < 0) dx = 1;
            else if (lastDirection.x > 0) dx = -1;
            if (lastDirection.y < 0) dy = 1;
            else if (lastDirection.y > 0) dy = -1;

            if (collision.width > collision.height) {
                player->move({ position.x, position.y + dy * (collision.height + 1) });

                if (CheckCollisionRecs(player->getColider(), objectCollider)) {
                    player->move({ position.x + dx * (collision.width + 1), position.y });
                }

                if (CheckCollisionRecs(player->getColider(), objectCollider)) {
                    player->move({ position.x + dx * (collision.width + 1), position.y + dy * (collision.height + 1) });
                }
            } else {
                player->move({ position.x + dx * (collision.width + 1), position.y });

                if (CheckCollisionRecs(player->getColider(), objectCollider)) {
                    player->move({ position.x, position.y + dy * (collision.height + 1) });
                }

                if (CheckCollisionRecs(player->getColider(), objectCollider)) {
                    player->move({ position.x + dx * (collision.width + 1), position.y + dy * (collision.height + 1) });
                }
            }
        }
    }
}

void Scene::draw() {
    Point origin = Vector2ToChunkPosition(player->getPosition());

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            getChunk({ origin.x + x, origin.y + y })->drawTiles();
        }
    }

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            getChunk({ origin.x + x, origin.y + y })->drawObjects();
        }
    }

    if (night) {
        DrawRectangle(
            origin.x * CHUNK_SIZE - WIDTH,
            origin.y * CHUNK_SIZE - HEIGHT,
            WIDTH * 2,
            HEIGHT * 2,
            ColorAlpha(
                BLACK,
                0.5
            )
        );
    }
}
